/**
 * The log buffer for the logging environment.
 * 
 * The buffer contains additional variables to make buffer management easier.
 */

#ifndef LOG_BUFFER_H
#define LOG_BUFFER_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

// ----------------------------------------------------------------------------
// --------------------------- Public Types -----------------------------------
// ----------------------------------------------------------------------------

/**
 * The log buffer. It contains additional variables to manage the buffer. The
 * buffer itself is used as ring buffer.
 */
typedef struct
{
	uint8_t buffer[BUFFER_SIZE]; /**< The actual ring buffer which is shared between log daemon and API calls of "log.h". */
	uint32_t write_position; /**< The write position in the ring buffer. */
	uint32_t read_position; /**< The read position in the ring buffer. */
	bool overflow; /**< An overflow is set if "write_position" exceeds end of array "buffer". It is reset if "read_position" exceeds end of array "buffer".*/
} log_buffer_t;

// ----------------------------------------------------------------------------
// --------------------------- Public Data ------------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------

/**
 * Initialize the additional variables of the log buffer:
 * - write_position
 * - read_position
 * - overflow
 */
void log_buffer_init(log_buffer_t *log_buffer);

/**
 * Transfer data from the ring buffer to the filesystem. The data between
 * "read_position" and "write_position" is transfered.
 * 
 * Notice: this method is thread-safe.
 * 
 * @param[in] semaphore_set_id The id of the semaphore set which holds the semaphore for the critical section.
 * @param[in] log_buffer The log buffer (the source).
 * @param[in] file The file to write to (the destination).
 * 
 * @return "true" on success. Otherwise "false".
 */
bool log_buffer_transfer_from_ring_buffer_to_filesystem(int32_t semaphore_set_id, log_buffer_t *log_buffer, FILE *file);

/**
 * Write data to ring buffer.
 * 
 * Data from two different locations can be written to ring buffer. First,
 * "location1" is written to ring buffer then "location2". This is for
 * convenience. Usually, you want to write a header with a fixed size to
 * ring buffer. Afterwards you want to write a message to ring buffer with
 * variable size. Both parts usually are located at different locations
 * 
 * Notice: this method is thread-safe.
 * 
 * @param[in] semaphore_set_id The id of the semaphore set which holds the semaphore for the critical section.
 * @param[in] log_buffer The log buffer which should be used.
 * @param[in] location1 Pointer to first data.
 * @param[in] location1_size Number of bytes to write from first data.
 * @param[in] location2 Pointer to second data.
 * @param[in] location2_size Number of bytes to write from second data.
 * 
 * @return "true" on success. "false" if the ring buffer is full. I.e. nothing is
 * written to the ring buffer. The ring buffer content has to be transfered to
 * filesystem first.
 */
bool log_buffer_write_to_ring_buffer(int32_t semaphore_set_id, log_buffer_t *log_buffer, uint8_t *location1, uint32_t location1_size, const char *location2, uint32_t location2_size);

#endif