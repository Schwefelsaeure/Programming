#ifndef SUITE_SHARED_MEMORY_HELPER
#define SUITE_SHARED_MEMORY_HELPER

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

int32_t suite_shared_memory_helper_init();
int32_t suite_shared_memory_helper_cleanup();
void test_shared_memory_helper_create_shared_memory();
void test_shared_memory_helper_create_shared_memory_2nd_call_fails();
void test_shared_memory_helper_open_shared_memory();
void test_shared_memory_helper_open_shared_memory_initial_values();

#endif
