/**
 * Shared memory helper methods.
 * 
 * The shared memory contains the log buffer which is shared between the "logd"
 * process and the processes where the log API calls take place.
 */

#ifndef SHARED_MEMORY_HELPER
#define SHARED_MEMORY_HELPER

#include "log_buffer.h"

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
 * Create and initialize the shared memory.
 * 
 * @return Pointer to a "log_buffer_t" on success. NULL on error.
 */
log_buffer_t* shared_memory_helper_create_shared_memory();

/**
 * Open the shared memory.
 * 
 * @return Pointer to a "log_buffer_t" on success. NULL on error.
 */
log_buffer_t* shared_memory_helper_open_shared_memory();

#endif
