#ifndef SUITE_SEMAPHORE_HELPER
#define SUITE_SEMAPHORE_HELPER

#include <stdint.h>

// ----------------------------------------------------------------------------
// --------------------------- Public Types -----------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// --------------------------- Public Data ------------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------

int32_t suite_semaphore_helper_init();
int32_t suite_semaphore_helper_cleanup();
void test_semaphore_helper_do_semaphore_operation_lock();
void test_semaphore_helper_do_semaphore_operation_unlock();
void test_semaphore_helper_create_semaphore_set();
void test_semaphore_helper_create_semaphore_set_initial_values();
void test_semaphore_helper_open_semaphore_set();
void test_semaphore_helper_signal_new_log_entry();

#endif
