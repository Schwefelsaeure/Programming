#include "log_buffer.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "semaphore_helper.h"

// ----------------------------------------------------------------------------
// -------------------------- Private Types -----------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Private Data ------------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ------------------- Private Methods (Declarations) -------------------------
// ----------------------------------------------------------------------------

static bool ring_buffer_is_full(log_buffer_t *log_buffer, uint32_t length);
static void write_to_ring_buffer(log_buffer_t *log_buffer, const uint8_t *content, uint32_t length);

// ----------------------------------------------------------------------------
// -------------------- Private Methods (Definitions) -------------------------
// ----------------------------------------------------------------------------

bool ring_buffer_is_full(log_buffer_t *log_buffer, uint32_t new_content_length)
{
	bool existing_overflow = log_buffer->overflow;
	bool future_overflow = (log_buffer->write_position + new_content_length >= BUFFER_SIZE);
	bool overflow = existing_overflow || future_overflow;
	
	bool write_position_overtakes_read_position = ((log_buffer->write_position + new_content_length) % BUFFER_SIZE) > log_buffer->read_position;
	
	return overflow && write_position_overtakes_read_position;
}

void write_to_ring_buffer(log_buffer_t *log_buffer, const uint8_t *content, uint32_t length)
{
	if(log_buffer->write_position + length >= BUFFER_SIZE)
	{
		log_buffer->overflow = true;
		printf("%s [%03d]: write overflow.\n", __FILE__, __LINE__);
	}

	int32_t i;
	
	printf("%s [%03d]: writing %d byte to ring buffer...\n", __FILE__, __LINE__, length);
	printf("%s [%03d]: write_position = %d\n", __FILE__, __LINE__, log_buffer->write_position);

	for(i = 0; i < length; i++)
	{
		log_buffer->buffer[log_buffer->write_position] = content[i];
		log_buffer->write_position = (log_buffer->write_position + 1) % BUFFER_SIZE;
	}

	printf("%s [%03d]: write_position = %d\n", __FILE__, __LINE__, log_buffer->write_position);
	printf("%s [%03d]: written %d byte to ring buffer.\n", __FILE__, __LINE__, length);
}

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------

void log_buffer_init(log_buffer_t *log_buffer)
{
	printf("%s [%03d]: initializing log_buffer...\n", __FILE__, __LINE__);
	
	log_buffer->write_position = 0;
	log_buffer->read_position = 0;
	log_buffer->overflow = false;
	
	printf("%s [%03d]: write_position = %d\n", __FILE__, __LINE__, log_buffer->write_position);
	printf("%s [%03d]: read_position = %d\n", __FILE__, __LINE__, log_buffer->read_position);
	printf("%s [%03d]: overflow = %d\n", __FILE__, __LINE__, log_buffer->overflow);
	
	printf("%s [%03d]: initialized log_buffer.\n", __FILE__, __LINE__);
}

bool log_buffer_transfer_from_ring_buffer_to_filesystem(int32_t semaphore_set_id, log_buffer_t *log_buffer, FILE *file)
{
	bool return_value = false;

	if(log_buffer == NULL)
		printf("%s [%03d]: log_buffer == NULL!\n", __FILE__, __LINE__);
	else
	{
		if(log_buffer->overflow)
		{
			// TODO: evaluate return value of "fwrite(...)". If hard disk is full return "false".
			int32_t read_position1 = log_buffer->read_position;
			int32_t bytes_to_read1 = BUFFER_SIZE - read_position1;
			int32_t read_position2 = 0;
			int32_t bytes_to_read2 = log_buffer->write_position;
			
			printf("%s [%03d]: transfering %d byte from ring buffer starting at %d...\n", __FILE__, __LINE__, bytes_to_read1, read_position1);
			fwrite(&log_buffer->buffer[read_position1], 1, bytes_to_read1, file);
			printf("%s [%03d]: transfered from ring buffer.\n", __FILE__, __LINE__);
			
			
			printf("%s [%03d]: transfering %d byte from ring buffer starting at %d...\n", __FILE__, __LINE__, bytes_to_read2, read_position2);
			fwrite(&log_buffer->buffer[read_position2], 1, bytes_to_read2, file);			
			printf("%s [%03d]: transfered from ring buffer.\n", __FILE__, __LINE__);
			
			printf("%s [%03d]: read overflow.\n", __FILE__, __LINE__);
			
			if(semaphore_helper_do_semaphore_operation(semaphore_set_id, CRITICAL_SECTION, SEMAPHORE_LOCK))
			{
				log_buffer->overflow = false;
				semaphore_helper_do_semaphore_operation(semaphore_set_id, CRITICAL_SECTION, SEMAPHORE_UNLOCK);
				
				// "log_buffer->read_position" is just modified by "logd". Therefore, no process synchronisation necessary.
				log_buffer->read_position = (read_position2 + bytes_to_read2) % BUFFER_SIZE;
			}
		}
		else
		{
			int32_t read_position = log_buffer->read_position;
			uint32_t bytes_to_read = log_buffer->write_position - log_buffer->read_position;

			printf("%s [%03d]: transfering %d byte from ring buffer starting at %d...\n", __FILE__, __LINE__, bytes_to_read, read_position);
			fwrite(&log_buffer->buffer[read_position], 1, bytes_to_read, file);
			printf("%s [%03d]: transfered from ring buffer.\n", __FILE__, __LINE__);
			
			// "log_buffer->read_position" is just modified by "logd". Therefore, no process synchronisation necessary.
			log_buffer->read_position = (read_position + bytes_to_read) % BUFFER_SIZE;
		}
		
		return_value = true;
	}

	return return_value;
}


bool log_buffer_write_to_ring_buffer(int32_t semaphore_set_id, log_buffer_t *log_buffer, uint8_t *location1, uint32_t location1_size, const char *location2, uint32_t location2_size)
{
	bool return_value = false;
	uint32_t bytes_to_write = location1_size + location2_size;

	semaphore_helper_do_semaphore_operation(semaphore_set_id, CRITICAL_SECTION, SEMAPHORE_LOCK);
	
	if(log_buffer == NULL)
		printf("%s [%03d]: log_buffer == NULL!\n", __FILE__, __LINE__);
	else if(bytes_to_write > BUFFER_SIZE)
		printf("%s [%03d]: too much data for buffer (%d/%d)!\n", __FILE__, __LINE__, bytes_to_write, BUFFER_SIZE);
	else if(ring_buffer_is_full(log_buffer, bytes_to_write))
		printf("%s [%03d]: buffer is full!\n", __FILE__, __LINE__);
	else
	{
		// TODO: replace loops by "memcpy" (should be more efficient).
		if(location1_size > 0)
			write_to_ring_buffer(log_buffer, location1, location1_size);
		if(location2_size > 0)
			write_to_ring_buffer(log_buffer, (uint8_t *)location2, location2_size);

		semaphore_helper_signal_new_log_entry(semaphore_set_id);
		
		return_value = true;
	}
	
	semaphore_helper_do_semaphore_operation(semaphore_set_id, CRITICAL_SECTION, SEMAPHORE_UNLOCK);
	
	return return_value;
}
