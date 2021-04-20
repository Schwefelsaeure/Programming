#include "suite_semaphore_helper.h"
#include "../src/semaphore_helper.h"

#include <CUnit/CUnit.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

// ----------------------------------------------------------------------------
// -------------------------- Private Types -----------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Private Data ------------------------------------
// ----------------------------------------------------------------------------

static const key_t semaphore_set_key = 4321;
static int32_t semaphore_set_id = -1;

// ----------------------------------------------------------------------------
// ------------------- Private Methods (Declarations) -------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------- Private Methods (Definitions) -------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------

int32_t suite_semaphore_helper_init()
{
	// Create semaphore set with two semaphores ("CRITICAL_SECTION" and "NEW_LOG_ENTRY").
	if((semaphore_set_id = semget(semaphore_set_key, NUMBER_OF_SEMAPHORES, IPC_CREAT | IPC_EXCL | 0666)) == -1)
	{
		printf("semget(...) failed");
		return -1;
	}
	else
		return 0;
}

int32_t suite_semaphore_helper_cleanup()
{
	if(semctl(semaphore_set_id, 0, IPC_RMID, NULL) == -1)
	{
		printf("semctl(...) failed");
		return -1;
	}
	else
		return 0;
}

void test_semaphore_helper_do_semaphore_operation_lock()
{
	int32_t expected = 0;
	int32_t actual = -1;

	if(semctl(semaphore_set_id, CRITICAL_SECTION, SETVAL, 1) == -1)
	{
		perror(NULL);
		return;
	}
	
	semaphore_helper_do_semaphore_operation(semaphore_set_id, CRITICAL_SECTION, SEMAPHORE_LOCK);
	
	if((actual = semctl(semaphore_set_id, CRITICAL_SECTION, GETVAL, NULL)) == -1)
	{
		perror(NULL);
		return;
	}
	
	CU_ASSERT_EQUAL(actual, expected);	
}

void test_semaphore_helper_do_semaphore_operation_unlock()
{
	int32_t expected = 1;
	int32_t actual = -1;

	if(semctl(semaphore_set_id, CRITICAL_SECTION, SETVAL, 0) == -1)
	{
		perror(NULL);
		return;
	}
	
	semaphore_helper_do_semaphore_operation(semaphore_set_id, CRITICAL_SECTION, SEMAPHORE_UNLOCK);
	
	if((actual = semctl(semaphore_set_id, CRITICAL_SECTION, GETVAL, NULL)) == -1)
	{
		perror(NULL);
		return;
	}
	
	CU_ASSERT_EQUAL(actual, expected);
}

void test_semaphore_helper_create_semaphore_set()
{
	int32_t semaphore_set_id = semaphore_helper_create_semaphore_set();
	
	if(semctl(semaphore_set_id, 0, IPC_RMID, NULL) == -1)
	{
		perror(NULL);
		return;
	}
	
	CU_ASSERT_TRUE(semaphore_set_id != -1);
}

void test_semaphore_helper_create_semaphore_set_initial_values()
{
	uint16_t expected[] = {1, 0};
	uint16_t actual[NUMBER_OF_SEMAPHORES];
	
	int32_t semaphore_set_id = semaphore_helper_create_semaphore_set();
	
	if(semctl(semaphore_set_id, 0, GETALL, actual) == -1)
	{
		perror(NULL);
		return;
	}
	
	if(semctl(semaphore_set_id, 0, IPC_RMID, NULL) == -1)
	{
		perror(NULL);
		return;
	}
	
	int32_t i;
	
	for(i = 0; i < NUMBER_OF_SEMAPHORES; i++)
		CU_ASSERT_EQUAL(actual[i], expected[i]);
}

void test_semaphore_helper_open_semaphore_set()
{
	int32_t semaphore_set_id;
	int32_t expected = 1;
	int32_t actual = -1;
	
	semaphore_helper_create_semaphore_set();
	semaphore_set_id = semaphore_helper_open_semaphore_set();
	
	if((actual = semctl(semaphore_set_id, CRITICAL_SECTION, GETVAL, NULL)) == -1)
	{
		perror(NULL);
		return;
	}
	
	if(semctl(semaphore_set_id, 0, IPC_RMID, NULL) == -1)
	{
		perror(NULL);
		return;
	}
	
	CU_ASSERT_EQUAL(actual, expected);
}

void test_semaphore_helper_signal_new_log_entry()
{
	int32_t expected = 1;
	int32_t actual = -1;

	if(semctl(semaphore_set_id, NEW_LOG_ENTRY, SETVAL, 0) == -1)
	{
		perror(NULL);
		return;
	}
	
	// Two times signalling without consuming entry. I.e. semaphore value should be 1.
	semaphore_helper_signal_new_log_entry(semaphore_set_id);
	semaphore_helper_signal_new_log_entry(semaphore_set_id);
	
	if((actual = semctl(semaphore_set_id, NEW_LOG_ENTRY, GETVAL, NULL)) == -1)
	{
		perror(NULL);
		return;
	}
	
	CU_ASSERT_EQUAL(actual, expected);
}
