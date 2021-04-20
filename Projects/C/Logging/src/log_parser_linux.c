#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "log.h"

#pragma pack(push, 1)

typedef struct
{
	uint32_t timestamp;
	uint16_t key;
	float value;
} data_entry_t;

typedef struct
{
	uint32_t timestamp;
	int32_t thread_id;
	uint8_t log_level;
} message_entry_t;

#pragma pack(pop)

FILE *file = NULL;

void handle_data_entry();
void handle_message_entry();
void print_usage();

int main(int argc, const char* argv[])
{
	char default_filename[] = "log_linux.bin";
	const char *filename;
	
	if(argc == 1)
		filename = default_filename;
	else if(argc == 2)
		filename = argv[1];
	else
	{
		print_usage();
		return EXIT_FAILURE;
	}
	
	if((file = fopen(filename, "rb")) == NULL)
	{
		perror("Cannot open file");
		return EXIT_FAILURE;
	}
	
	uint8_t entry_type;
	
	while(fread(&entry_type, sizeof(entry_type), 1, file) > 0)
	{
		if(entry_type == (uint8_t)DATA_ENTRY)
			handle_data_entry();
		else if(entry_type == (uint8_t)MESSAGE_ENTRY)
			handle_message_entry();
		else
		{
			printf("Unsupported entry type!\n");
			return EXIT_FAILURE;
		}
	}
	
	if(fclose(file) != 0)
	{
		perror("Cannot close file");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

void handle_data_entry()
{
	data_entry_t data_entry;
	
	if(fread(&data_entry, sizeof(data_entry), 1, file) <= 0)
	{
		perror("Parse error (DATA_ENTRY incomplete)");
		exit(EXIT_FAILURE);
	}
	
	printf("%u, ", DATA_ENTRY);
	printf("%u, ", data_entry.timestamp);
	printf("%u, ", data_entry.key);
	printf("%f", data_entry.value);
	printf("\n");
}

void handle_message_entry()
{
	message_entry_t message_entry;
	char current_char;
	
	if(fread(&message_entry, sizeof(message_entry), 1, file) <= 0)
	{
		perror("Parse error (MESSAGE_ENTRY incomplete)");
		exit(EXIT_FAILURE);
	}
	
	printf("%u, ", MESSAGE_ENTRY);
	printf("%u, ", message_entry.timestamp);
	printf("%d, ", message_entry.thread_id);
	printf("%u, ", message_entry.log_level);
	
	while(1)
	{
		if(fread(&current_char, sizeof(current_char), 1, file) <=  0)
		{
			perror("Parse error (string cannot be read)");
			exit(EXIT_FAILURE);
		}
		
		if(current_char != '\0')
			printf("%c", current_char);
		else
		{
			printf("\n");
			break;
		}
	}
}

void print_usage()
{
	printf("Usage: log_parser_linux [file]\n");
	printf("\n");
	printf("Note: log_parser_linux uses the default file \"log_linux.bin\".\n");
}
