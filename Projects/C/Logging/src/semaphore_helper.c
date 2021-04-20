#include "semaphore_helper.h"

#include <stdint.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/types.h>

#define ERROR -1

// ----------------------------------------------------------------------------
// -------------------------- Private Types -----------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Private Data ------------------------------------
// ----------------------------------------------------------------------------

static uint16_t initial_semaphore_values[NUMBER_OF_SEMAPHORES] = {1, 0};
static const key_t semaphore_set_key = 1234;

// ----------------------------------------------------------------------------
// ------------------- Private Methods (Declarations) -------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------- Private Methods (Definitions) -------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------

bool semaphore_helper_do_semaphore_operation(int32_t semaphore_set_id, semaphore_t semaphore, semaphore_operation_t semaphore_operation)
{
	struct sembuf semaphore_description;

	semaphore_description.sem_num = semaphore;
	semaphore_description.sem_op = semaphore_operation;
	semaphore_description.sem_flg = 0;

	printf("%s [%03d]: doing semaphore operation...\n", __FILE__, __LINE__);
	printf("%s [%03d]: semaphore_set_id = %d\n", __FILE__, __LINE__, semaphore_set_id);
	printf("%s [%03d]: semaphore = %d\n", __FILE__, __LINE__, semaphore);
	printf("%s [%03d]: semaphore_operation = %d\n", __FILE__, __LINE__, semaphore_operation);

	if(semop(semaphore_set_id, &semaphore_description, 1) == -1)
	{
		perror("semop(...) failed");
		return false;
	}
	
	printf("%s [%03d]: semaphore operation done.\n", __FILE__, __LINE__);

	return true;
}

int32_t semaphore_helper_create_semaphore_set()
{
	int32_t semaphore_set_id = -1;
	
	printf("%s [%03d]: creating semaphore set...\n", __FILE__, __LINE__);
	printf("%s [%03d]: key = %d\n", __FILE__, __LINE__, semaphore_set_key);

	if((semaphore_set_id = semget(semaphore_set_key, NUMBER_OF_SEMAPHORES, IPC_CREAT | IPC_EXCL | 0666)) == -1)
	{
		perror("semget(...) failed");
		return ERROR;
	}

	printf("%s [%03d]: id = %d\n", __FILE__, __LINE__, semaphore_set_id);

	if(semctl(semaphore_set_id, 0, SETALL, initial_semaphore_values) == -1)
	{
		perror("semctl(...) failed");
		return ERROR;
	}

	printf("%s [%03d]: initalized semaphore set.\n", __FILE__, __LINE__);
	
	return semaphore_set_id;
}

int32_t semaphore_helper_open_semaphore_set()
{
	int32_t semaphore_set_id = -1;
	
	printf("%s [%03d]: opening semaphore set...\n", __FILE__, __LINE__);
	printf("%s [%03d]: key = %d\n", __FILE__, __LINE__, semaphore_set_key);

	if((semaphore_set_id = semget(semaphore_set_key, 0, IPC_PRIVATE)) == -1)
	{
		perror("semget(...) failed");
		return ERROR;
	}

	printf("%s [%03d]: id = %d\n", __FILE__, __LINE__, semaphore_set_id);

	printf("%s [%03d]: opened semaphore set.\n", __FILE__, __LINE__);

	return semaphore_set_id;
}

bool semaphore_helper_signal_new_log_entry(int32_t semaphore_set_id)
{
	int32_t semaphore_value;
	
	printf("%s [%03d]: signalling new log entry...\n", __FILE__, __LINE__);
	
	if((semaphore_value = semctl(semaphore_set_id, NEW_LOG_ENTRY, GETVAL, NULL)) == -1)
	{
		perror("semctl(...) failed");
		return false;
	}
	
	// If semaphore_value > 0 => there is still a pending signal.
	if(semaphore_value == 0)
		semaphore_helper_do_semaphore_operation(semaphore_set_id, NEW_LOG_ENTRY, SEMAPHORE_UNLOCK);
	
	printf("%s [%03d]: signalled new log entry.\n", __FILE__, __LINE__);
	
	return true;
}