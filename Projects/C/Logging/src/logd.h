/**
 * The log daemon "logd" which transfers entries from ring buffer to the
 * filesystem.
 * 
 * "logd" allocates the ring buffer in RAM for the non-blocking methods of
 * "log.h". "logd" is signalled when the ring buffer contains a new entry and
 * transfers the entry from ring buffer to the filesystem.
 */

#ifndef LOGD_H
#define LOGD_H

// ----------------------------------------------------------------------------
// --------------------------- Public Types -----------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// --------------------------- Public Data ------------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------

/**
 * Initialize the logd:
 * - Create shared memory (for API calls of "log.h").
 * - Create semaphore set.
 * - Open file (to save log entries persistent).
 * 
 * If one of the steps above fails, logd exits with an error code of
 * "EXIT_FAILURE".
 */
void logd_init();

/**
 * Process a new log entry. I.e. transfer it from the ring buffer to the file.
 */
void logd_process_new_log_entry();

/**
 * Wait for a new log entry. Logd process is sleeping while waiting (by using
 * a semaphore).
 */
void logd_wait_for_new_log_entry();

#endif
