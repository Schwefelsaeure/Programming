#include "log.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>
#include "log_buffer.h"
#include "logd.h"
#include "semaphore_helper.h"
#include "shared_memory_helper.h"

// ----------------------------------------------------------------------------
// -------------------------- Private Types -----------------------------------
// ----------------------------------------------------------------------------

#pragma pack(push, 1)

typedef struct
{
	uint8_t entry_type;
	uint32_t timestamp;
	uint16_t key;
	float value;
} data_entry_t;

typedef struct
{
	uint8_t entry_type;
	uint32_t timestamp;
	int32_t thread_id;
	uint8_t log_level;
} message_entry_without_string_t;

#pragma pack(pop)

// ----------------------------------------------------------------------------
// -------------------------- Private Data ------------------------------------
// ----------------------------------------------------------------------------

// Semaphores:
static int32_t semaphore_set_id = -1;

// Shared memory (log buffer):
static log_buffer_t *log_buffer = NULL;

// ----------------------------------------------------------------------------
// ------------------- Private Methods (Declarations) -------------------------
// ----------------------------------------------------------------------------

static bool init_semaphore_set();
static bool init_shared_memory();

// ----------------------------------------------------------------------------
// -------------------- Private Methods (Definitions) -------------------------
// ----------------------------------------------------------------------------

bool init_semaphore_set()
{
	if((semaphore_set_id = semaphore_helper_open_semaphore_set()) == -1)
	{
		printf("%s [%03d]: semaphore_helper_open_semaphore_set() failed!\n", __FILE__, __LINE__);
		return false;
	}
	else
		return true;
}

bool init_shared_memory()
{
	if((log_buffer = shared_memory_helper_open_shared_memory()) == NULL)
	{
		printf("%s [%03d]: shared_memory_helper_open_shared_memory() failed!\n", __FILE__, __LINE__);
		return false;
	}
	else
		return true;
}

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------

bool log_init()
{
	return init_shared_memory() && init_semaphore_set();
}

bool log_data(uint16_t key, float value)
{
	bool return_value = false;
	
	data_entry_t entry;
	
	entry.entry_type = (uint8_t)DATA_ENTRY;
	entry.timestamp = (int32_t)time(NULL);
	entry.key = key;
	entry.value = value;
	
	return_value = log_buffer_write_to_ring_buffer(semaphore_set_id, log_buffer, (uint8_t *)&entry, sizeof(entry), NULL, 0);

	return return_value;
}

bool log_message(log_level_t log_level, const char *message)
{
	bool return_value = false;
	
	message_entry_without_string_t entry;
	int32_t message_length;
	
	entry.entry_type = (uint8_t)MESSAGE_ENTRY;
	entry.timestamp = (int32_t)time(NULL);
	entry.thread_id = (int)syscall(SYS_gettid);
	entry.log_level = (uint8_t)log_level;

	message_length = strlen(message) + 1;
	
	return_value = log_buffer_write_to_ring_buffer(semaphore_set_id, log_buffer, (uint8_t *)&entry, sizeof(entry), message, message_length);
	
	return return_value;
}
