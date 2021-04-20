#ifndef SUITE_LOG_BUFFER
#define SUITE_LOG_BUFFER

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

int32_t suite_log_buffer_init();
int32_t suite_log_buffer_cleanup();
void test_log_buffer_init();
void test_log_buffer_transfer_from_ring_buffer_to_filesystem_return_value();
void test_log_buffer_transfer_from_ring_buffer_to_filesystem_number_of_written_bytes();
void test_log_buffer_transfer_from_ring_buffer_to_filesystem_written_data();
void test_log_buffer_transfer_from_ring_buffer_to_filesystem_read_overflow();
void test_log_buffer_write_to_ring_buffer_return_value();
void test_log_buffer_write_to_ring_buffer_written_data();
void test_log_buffer_write_to_ring_buffer_write_overflow();
void test_log_buffer_write_to_ring_buffer_return_value_when_buffer_full();
void test_log_buffer_write_to_ring_buffer_no_overwrite_when_buffer_full();
void test_log_buffer_write_to_ring_buffer_thread_safety();

#endif
