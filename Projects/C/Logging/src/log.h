/**
 * The log API which should be used by applications.
 * 
 * The methods log into a ring buffer in RAM. "logd" is responsible to write
 * the entries from ring buffer to the filesystem.
 */

#ifndef LOG_H
#define LOG_H

#include <stdbool.h>
#include <stdint.h>

// ----------------------------------------------------------------------------
// --------------------------- Public Types -----------------------------------
// ----------------------------------------------------------------------------

/**
 * Two different entry types are supported at the moment:
 * - DATA_ENTRY: consists of a key-value pair. Key is a string. Value is a
 *   32 bit integer.
 * - MESSAGE_ENTRY: consists of a string.
 */
typedef enum
{
	DATA_ENTRY, /*< A data entry consists of a key-value pair.*/
	MESSAGE_ENTRY /*< A message entry consists of a string.*/
} entry_type_t;

/**
 * Four different log levels are supported at the moment. These log levels only
 * apply to entries with id "MESSAGE_ENTRY".
 */
typedef enum
{
	CRITICAL, /*< An unrecoverable condition occurred. */
	ERROR, /*< An error occurred.*/
	INFO, /*< Informational output. */
	DEBUG /*< Only debug output. */
} log_level_t;

// ----------------------------------------------------------------------------
// --------------------------- Public Data ------------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------

/**
 * Initialize the log environment:
 * - Get address of the ring buffer.
 * - Get semaphores for IPC with "logd".
 * 
 * The log environment has to be initialized. Otherwise the calls
 * "log_data(...)" and "log_message(...)" will fail with segmentation fault.
 * 
 * @return "true" on success. Ohterwise "false".
 */
bool log_init();

/**
 * Log a key-value entry to ring buffer. The entry is written binary to ring
 * buffer in the following form:
 * 
 * [entry_type][timestamp][key][value]
 * 
 * - entry_id: 1 byte
 * - timestamp: 4 byte
 * - key: 2 byte
 * - value: 4 byte
 * 
 * @param[in] key The identifier of the logged value.
 * @param[in] value The value.
 * 
 * @return "true" on success. Otherwise "false".
 */
bool log_data(uint16_t key, float value);

/**
 * Log a message entry to ring buffer. The entry is written binary to ring
 * buffer in the following form:
 * 
 * [entry_type][timestamp][thread_id][log_level][message]
 * 
 * Use "\0"-terminated string for "message" parameter.
 * 
 * - entry_id: 1 byte
 * - timestamp: 4 byte
 * - thread_id: 4 byte
 * - log_level: 1 byte
 * - message: variable length but "\0"-terminated
 * 
 * @param[in] log_level The log level of the entry.
 * @param[in] message The message.
 * 
 * @return "true" on success. Otherwise "false".
 */
bool log_message(log_level_t log_level, const char *message);

#endif
