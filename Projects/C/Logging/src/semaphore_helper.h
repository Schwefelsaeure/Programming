/**
 * Semaphore helper methods.
 * 
 * Semaphores are used to synchronize access to critical sections between
 * processes. The critical section is the ring buffer which is accessed by
 * the processes which use the log API.
 */

#ifndef SEMAPHORE_HELPER_H
#define SEMAPHORE_HELPER_H

#include <stdbool.h>
#include <stdint.h>

#define NUMBER_OF_SEMAPHORES 2

// ----------------------------------------------------------------------------
// --------------------------- Public Types -----------------------------------
// ----------------------------------------------------------------------------

/**
 * These semaphores exist in the log environment.
 */
typedef enum
{
	CRITICAL_SECTION = 0, /*< This semaphore is used to synchronize access to the critical section. */
	NEW_LOG_ENTRY = 1 /*< This semaphore is used to signal the log daemon that a new log entry is in ring buffer. */
} semaphore_t;

/**
 * The operations which can be done to semaphores.
 */
typedef enum
{
	SEMAPHORE_LOCK = -1, /*< Decrement the semaphore by 1. I.e. lock access for other processes, if semaphore value is 0.*/
	SEMAPHORE_WAIT_FOR_ZERO = 0, /*< Wait for semaphore value to be 0. See man page SEMOP(3P). */
	SEMAPHORE_UNLOCK = 1 /* Increment the semaphore by one. I.e. unlock access for other processes, if semaphore value is 0.*/
} semaphore_operation_t;

// ----------------------------------------------------------------------------
// --------------------------- Public Data ------------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------

/**
 * Do an operation on a semaphore.
 * 
 * @param[in] semaphore_set_id The set id of the semaphore.
 * @param[in] semaphore Two semaphores are available: "CRITICAL_SECTION" and
 * "NEW_LOG_ENTRY".
 * @param[in] semaphore_operation The operation for the semaphore.
 * 
 * Pay attention: if you try to access the critical section via
 * 
 *   semaphore_helper_do_semaphore_operation(1234, CRITICAL_SECTION, SEMAPHORE_LOCK)
 * 
 * but the critical section is already locked by another process the calling
 * process is blocked until the critical section is unlocked.
 * 
 * @return "true" on success. Otherwise "false".
 */
bool semaphore_helper_do_semaphore_operation(int32_t semaphore_set_id, semaphore_t semaphore, semaphore_operation_t semaphore_operation);

/**
 * Create a semaphore set with two semaphores and set initial values:
 * - CRITICAL_SECTION (initial value: 1)
 * - NEW_LOG_ENTRY (initial value: 0)
 * 
 * @return The id of the semaphore set on success. -1 on error.
 */
int32_t semaphore_helper_create_semaphore_set();

/**
 * Open the semaphore set which was created by
 * "semaphore_helper_create_semaphore_set()" method.
 * 
 * @return The id of the semaphore set. -1 on error.
 */
int32_t semaphore_helper_open_semaphore_set();

/**
 * Signal that a new new log entry has added to the ring buffer.
 * 
 * @param[in] semaphore_set_id The set id of the semaphore.
 * 
 * @return "true" on success. Otherwise "false".
 */
bool semaphore_helper_signal_new_log_entry(int32_t semaphore_set_id);

#endif
