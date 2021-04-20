#include "shared_memory_helper.h"

#include <stdint.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "log_buffer.h"

// ----------------------------------------------------------------------------
// -------------------------- Private Types -----------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Private Data ------------------------------------
// ----------------------------------------------------------------------------

static const key_t shm_key = 1234;
static const uint32_t shm_size = sizeof(log_buffer_t);

// ----------------------------------------------------------------------------
// ------------------- Private Methods (Declarations) -------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------- Private Methods (Definitions) -------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------

log_buffer_t* shared_memory_helper_create_shared_memory()
{
	int32_t shm_id = -1;
	int8_t *shm = NULL;
	log_buffer_t *log_buffer = NULL;

	printf("%s [%03d]: creating shared memory...\n", __FILE__, __LINE__);
	printf("%s [%03d]: key = %d\n", __FILE__, __LINE__, shm_key);
	printf("%s [%03d]: size = %d\n", __FILE__, __LINE__, shm_size);

	if((shm_id = shmget(shm_key, shm_size, IPC_CREAT | IPC_EXCL | 0666)) == -1)
	{
		perror("shmget(...) failed");
		return NULL;
	}

	printf("%s [%03d]: id = %d\n", __FILE__, __LINE__, shm_id);

	if((shm = shmat(shm_id, NULL, 0)) == (int8_t *)-1)
	{
		perror("shmat(...) failed");
		return NULL;
	}

	log_buffer = (log_buffer_t *)shm;
	log_buffer_init(log_buffer);

	printf("%s [%03d]: shm = %p\n", __FILE__, __LINE__, shm);
	printf("%s [%03d]: log_buffer = %p\n", __FILE__, __LINE__, log_buffer);

	printf("%s [%03d]: initialized shared memory.\n", __FILE__, __LINE__);
	
	return log_buffer;
}

log_buffer_t* shared_memory_helper_open_shared_memory()
{
	int32_t shm_id = -1;
	int8_t *shm = NULL;
	log_buffer_t *log_buffer = NULL;

	printf("%s [%03d]: opening shared memory...\n", __FILE__, __LINE__);
	printf("%s [%03d]: key = %d\n", __FILE__, __LINE__, shm_key);
	printf("%s [%03d]: size = %d\n", __FILE__, __LINE__, shm_size);

	if((shm_id = shmget(shm_key, shm_size, 0666)) == -1)
	{
		perror("shmget(...) failed");
		return NULL;
	}

	if((shm = shmat(shm_id, NULL, 0)) == (int8_t *)-1)
	{
		perror("shmat(...) failed!");
		return NULL;
	}

	log_buffer = (log_buffer_t *)shm;

	printf("%s [%03d]: shm = %p\n", __FILE__, __LINE__, shm);
	printf("%s [%03d]: log_buffer = %p\n", __FILE__, __LINE__, log_buffer);

	printf("%s [%03d]: opened shared memory.\n", __FILE__, __LINE__);

	return log_buffer;
}
