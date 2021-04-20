#include "suite_log_buffer.h"
#include "../src/log_buffer.h"

#include <CUnit/CUnit.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include "../src/semaphore_helper.h"

#define NUMBER_OF_FILESYSTEM_TESTS 4
#define NUMBER_OF_THREADS 5

// ----------------------------------------------------------------------------
// -------------------------- Private Types -----------------------------------
// ----------------------------------------------------------------------------

typedef struct
{
	int32_t semaphore_set_id;
	log_buffer_t *log_buffer;
	uint8_t *location1;
	uint32_t location1_size;
	const char *location2;
	uint32_t location2_size;
} thread_data_t;

// ----------------------------------------------------------------------------
// -------------------------- Private Data ------------------------------------
// ----------------------------------------------------------------------------

// File:
FILE *file[NUMBER_OF_FILESYSTEM_TESTS];

// Semaphore set:
static uint16_t initial_semaphore_values[NUMBER_OF_SEMAPHORES] = {1, 0};
static const key_t semaphore_set_key = 4321;
static int32_t semaphore_set_id = -1;

// Threads:
pthread_t thread[NUMBER_OF_THREADS];

// ----------------------------------------------------------------------------
// ------------------- Private Methods (Declarations) -------------------------
// ----------------------------------------------------------------------------

static void *thread_method(void *data);

// ----------------------------------------------------------------------------
// -------------------- Private Methods (Definitions) -------------------------
// ----------------------------------------------------------------------------

void *thread_method(void *data)
{
	thread_data_t *thread_data = (thread_data_t *)data;
	
	log_buffer_write_to_ring_buffer(thread_data->semaphore_set_id, thread_data->log_buffer, thread_data->location1, thread_data->location1_size, thread_data->location2, thread_data->location2_size);
	
	pthread_exit(0);
}

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------

int32_t suite_log_buffer_init()
{
	int32_t return_value = 0;
	int32_t i;
	
	// Create semaphore set with two semaphores ("CRITICAL_SECTION" and "NEW_LOG_ENTRY").
	if((semaphore_set_id = semget(semaphore_set_key, NUMBER_OF_SEMAPHORES, IPC_CREAT | IPC_EXCL | 0666)) == -1)
	{
		perror("semget(...) failed");
		return_value = -1;
	}
	else
	{
		if(semctl(semaphore_set_id, 0, SETALL, initial_semaphore_values) == -1)
		{
			perror("semctl(...) failed");
			return_value = -1;
		}
	}
	
	// Create test files.
	for(i = 0; i < NUMBER_OF_FILESYSTEM_TESTS; i++)
	{
		char filename_pattern[] = "-test.bin";
		char *filename = (char *)malloc(strlen(filename_pattern) + 3); // 3 -> Two digit prefix and \0-terminator.
		sprintf(filename, "%02d%s", i + 1, filename_pattern);
		
		if((file[i] = fopen(filename, "w+b")) == NULL)
		{
			perror("fopen(...) failed");
			return_value = -1;
		}
	}
	
	return return_value;
}

int32_t suite_log_buffer_cleanup()
{
	int32_t return_value = 0;
	int32_t i;
	
	if(semctl(semaphore_set_id, 0, IPC_RMID, NULL) == -1)
	{
		perror("semctl(...) failed");
		return_value = -1;
	}
	
	for(i = 0; i < NUMBER_OF_FILESYSTEM_TESTS; i++)
	{
		if(fclose(file[i]) != 0)
		{
			perror("fopen(...) failed");
			return_value = -1;
		}
	}
	
	return return_value;
}

void test_log_buffer_init()
{
	int32_t expected = 0;
	
	log_buffer_t log_buffer;
	log_buffer_init(&log_buffer);
	
	CU_ASSERT_EQUAL(log_buffer.write_position, expected);
	CU_ASSERT_EQUAL(log_buffer.read_position, expected);
	CU_ASSERT_EQUAL(log_buffer.overflow, expected);
}

void test_log_buffer_transfer_from_ring_buffer_to_filesystem_return_value()
{
	bool actual = false;
	
	log_buffer_t log_buffer;
	log_buffer_init(&log_buffer);
	
	log_buffer.buffer[0] = 1;
	log_buffer.write_position = 1;
	
	actual = log_buffer_transfer_from_ring_buffer_to_filesystem(semaphore_set_id, &log_buffer, file[0]);
	
	CU_ASSERT_TRUE(actual);
}

void test_log_buffer_transfer_from_ring_buffer_to_filesystem_number_of_written_bytes()
{
	int32_t expected_bytes_written = 5;
	long actual_bytes_written = -1;
	int32_t i;
	
	log_buffer_t log_buffer;
	log_buffer_init(&log_buffer);
	
	for(i = 0; i < expected_bytes_written; i++)
	{
		log_buffer.buffer[i] = 1;
		log_buffer.write_position += 1;
	}
	
	log_buffer_transfer_from_ring_buffer_to_filesystem(semaphore_set_id, &log_buffer, file[1]);
	actual_bytes_written = ftell(file[1]);
	
	CU_ASSERT_EQUAL(actual_bytes_written, expected_bytes_written);
}

void test_log_buffer_transfer_from_ring_buffer_to_filesystem_written_data()
{
	int32_t bytes_to_write = 5;
	uint8_t actual[bytes_to_write];
	bool actual_and_expected_differs = false;
	int32_t i;
	
	log_buffer_t log_buffer;
	log_buffer_init(&log_buffer);
	
	for(i = 0; i < bytes_to_write; i++)
	{
		log_buffer.buffer[i] = (uint8_t)i;
		log_buffer.write_position += 1;
	}
	
	log_buffer_transfer_from_ring_buffer_to_filesystem(semaphore_set_id, &log_buffer, file[2]);
	rewind(file[2]);
	fread(actual, 1, bytes_to_write, file[2]);
	
	for(i = 0; i < bytes_to_write; i++)
	{
		if(actual[i] != (uint8_t)i)
			actual_and_expected_differs = true;
	}
	
	CU_ASSERT_FALSE(actual_and_expected_differs);
}

void test_log_buffer_transfer_from_ring_buffer_to_filesystem_read_overflow()
{
	uint8_t expected[] = { 0, 1 };
	int32_t bytes_to_write = sizeof(expected) / sizeof(expected[0]);
	uint8_t actual[bytes_to_write];
	bool actual_and_expected_differs = false;
	int32_t i;
	
	log_buffer_t log_buffer;
	log_buffer_init(&log_buffer);
	
	log_buffer.buffer[BUFFER_SIZE - 1] = expected[0];
	log_buffer.buffer[0] = expected[1];
	
	log_buffer.write_position = 1;
	log_buffer.read_position = BUFFER_SIZE - 1;
	log_buffer.overflow = 1;
	
	log_buffer_transfer_from_ring_buffer_to_filesystem(semaphore_set_id, &log_buffer, file[3]);
	rewind(file[3]);
	fread(actual, 1, bytes_to_write, file[3]);
	
	for(i = 0; i < bytes_to_write; i++)
	{
		if(actual[i] != expected[i])
			actual_and_expected_differs = true;
	}
	
	CU_ASSERT_FALSE(actual_and_expected_differs);
}

void test_log_buffer_write_to_ring_buffer_return_value()
{
	bool actual = false;
	uint8_t byte_to_write = 1;
	
	log_buffer_t log_buffer;
	log_buffer_init(&log_buffer);
	
	actual = log_buffer_write_to_ring_buffer(semaphore_set_id, &log_buffer, &byte_to_write, 1, NULL, 0);
	
	CU_ASSERT_TRUE(actual);
}

void test_log_buffer_write_to_ring_buffer_written_data()
{
	uint8_t expected[] = { 0, 1, 2, 3, 4 };
	int32_t bytes_to_write = sizeof(expected) / sizeof(expected[0]);
	bool actual_and_expected_differs = false;
	int32_t i;
	
	log_buffer_t log_buffer;
	log_buffer_init(&log_buffer);
	
	log_buffer_write_to_ring_buffer(semaphore_set_id, &log_buffer, expected, bytes_to_write, NULL, 0);
	
	for(i = 0; i < bytes_to_write; i++)
	{
		if(log_buffer.buffer[i] != expected[i])
			actual_and_expected_differs = true;
	}
	
	CU_ASSERT_FALSE(actual_and_expected_differs);
}

void test_log_buffer_write_to_ring_buffer_write_overflow()
{
	uint8_t data[] = { 0, 1 };
	int32_t bytes_to_write = sizeof(data) / sizeof(data[0]);
	
	log_buffer_t log_buffer;
	log_buffer_init(&log_buffer);
	
	log_buffer.write_position = BUFFER_SIZE - 1;
	log_buffer.read_position = log_buffer.write_position;
	log_buffer.overflow = 0;
	
	log_buffer_write_to_ring_buffer(semaphore_set_id, &log_buffer, data, bytes_to_write, NULL, 0);
	
	CU_ASSERT_TRUE(log_buffer.overflow);
}

void test_log_buffer_write_to_ring_buffer_return_value_when_buffer_full()
{
	uint8_t data[] = { 1, 1 };
	int32_t bytes_to_write = sizeof(data) / sizeof(data[0]);
	bool actual = false;
	int32_t i;
	
	log_buffer_t log_buffer;
	log_buffer_init(&log_buffer);
	
	log_buffer.overflow = 1;
	
	for(i = 0; i < bytes_to_write; i++)
		log_buffer.buffer[i] = 2;
	
	actual = log_buffer_write_to_ring_buffer(semaphore_set_id, &log_buffer, data, bytes_to_write, NULL, 0);
	
	CU_ASSERT_FALSE(actual);
}

void test_log_buffer_write_to_ring_buffer_no_overwrite_when_buffer_full()
{
	uint8_t data[] = { 1, 1 };
	int32_t bytes_to_write = sizeof(data) / sizeof(data[0]);
	bool content_is_overwritten = false;
	uint8_t expected = 2;
	int32_t i;
	
	log_buffer_t log_buffer;
	log_buffer_init(&log_buffer);
	
	log_buffer.overflow = 1;
	
	for(i = 0; i < bytes_to_write; i++)
		log_buffer.buffer[i] = expected;
	
	log_buffer_write_to_ring_buffer(semaphore_set_id, &log_buffer, data, bytes_to_write, NULL, 0);
	
	for(i = 0; i < bytes_to_write; i++)
	{
		if(log_buffer.buffer[i] != expected)
			content_is_overwritten = true;
	}
	
	CU_ASSERT_FALSE(content_is_overwritten);
}

void test_log_buffer_write_to_ring_buffer_thread_safety()
{

	uint8_t data[] = { 0, 1, 2, 3, 4 };
	int32_t bytes_to_write = sizeof(data) / sizeof(data[0]);
	
	log_buffer_t log_buffer;
	thread_data_t thread_data = { semaphore_set_id, &log_buffer, data, bytes_to_write, NULL, 0 };
	
	int32_t i;
	bool data_is_mixed = false;
	
	log_buffer_init(&log_buffer);
	
	for(i = 0; i < NUMBER_OF_THREADS; i++)
	{
		if(pthread_create(&thread[i], NULL, thread_method, (void *)&thread_data) != 0)
		{
			perror("pthread_create(...) failed");
			return;
		}
		
	}
	
	for(i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(thread[i], NULL);
	
	for(i = 0; i < NUMBER_OF_THREADS * bytes_to_write; i++)
	{
		uint8_t expected_data = data[i % bytes_to_write];
		uint8_t actual_data = log_buffer.buffer[i];
		
		if(actual_data != expected_data)
			data_is_mixed = true;
	}
	
	CU_ASSERT_FALSE(data_is_mixed);
}
