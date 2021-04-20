#include "CUnit/Basic.h"
#include "suite_semaphore_helper.h"
#include "suite_shared_memory_helper.h"
#include "suite_log_buffer.h"

#include <stdlib.h>

CU_TestInfo suite_semaphore_helper[] =
{
	{ "test_semaphore_helper_do_semaphore_operation_lock", test_semaphore_helper_do_semaphore_operation_lock },
	{ "test_semaphore_helper_do_semaphore_operation_unlock", test_semaphore_helper_do_semaphore_operation_unlock },
	{ "test_semaphore_helper_create_semaphore_set", test_semaphore_helper_create_semaphore_set },
	{ "test_semaphore_helper_create_semaphore_set_initial_values", test_semaphore_helper_create_semaphore_set_initial_values },
	{ "test_semaphore_helper_open_semaphore_set", test_semaphore_helper_open_semaphore_set },
	{ "test_semaphore_helper_signal_new_log_entry", test_semaphore_helper_signal_new_log_entry },
	CU_TEST_INFO_NULL
};

CU_TestInfo suite_shared_memory_helper[] =
{
	{ "test_shared_memory_helper_create_shared_memory", test_shared_memory_helper_create_shared_memory },
	{ "test_shared_memory_helper_create_shared_memory_2nd_call_fails", test_shared_memory_helper_create_shared_memory_2nd_call_fails },
	{ "test_shared_memory_helper_open_shared_memory", test_shared_memory_helper_open_shared_memory },
	{ "test_shared_memory_helper_open_shared_memory_initial_values", test_shared_memory_helper_open_shared_memory_initial_values },
	CU_TEST_INFO_NULL
};

CU_TestInfo suite_log_buffer[] =
{
	{ "test_log_buffer_init", test_log_buffer_init },
	{ "test_log_buffer_transfer_from_ring_buffer_to_filesystem_return_value", test_log_buffer_transfer_from_ring_buffer_to_filesystem_return_value },
	{ "test_log_buffer_transfer_from_ring_buffer_to_filesystem_number_of_written_bytes", test_log_buffer_transfer_from_ring_buffer_to_filesystem_number_of_written_bytes },
	{ "test_log_buffer_transfer_from_ring_buffer_to_filesystem_written_data", test_log_buffer_transfer_from_ring_buffer_to_filesystem_written_data },
	{ "test_log_buffer_transfer_from_ring_buffer_to_filesystem_read_overflow", test_log_buffer_transfer_from_ring_buffer_to_filesystem_read_overflow },
	{ "test_log_buffer_write_to_ring_buffer_return_value", test_log_buffer_write_to_ring_buffer_return_value },
	{ "test_log_buffer_write_to_ring_buffer_written_data", test_log_buffer_write_to_ring_buffer_written_data },
	{ "test_log_buffer_write_to_ring_buffer_write_overflow", test_log_buffer_write_to_ring_buffer_write_overflow },
	{ "test_log_buffer_write_to_ring_buffer_return_value_when_buffer_full", test_log_buffer_write_to_ring_buffer_return_value_when_buffer_full },
	{ "test_log_buffer_write_to_ring_buffer_no_overwrite_when_buffer_full", test_log_buffer_write_to_ring_buffer_no_overwrite_when_buffer_full },
	{ "test_log_buffer_write_to_ring_buffer_thread_safety", test_log_buffer_write_to_ring_buffer_thread_safety },
	CU_TEST_INFO_NULL
};

CU_SuiteInfo suites[] =
{
	{ "suite_semaphore_helper", suite_semaphore_helper_init, suite_semaphore_helper_cleanup, suite_semaphore_helper },
	{ "suite_shared_memory_helper", suite_shared_memory_helper_init, suite_shared_memory_helper_cleanup, suite_shared_memory_helper },
	{ "suite_log_buffer", suite_log_buffer_init, suite_log_buffer_cleanup, suite_log_buffer },
	CU_SUITE_INFO_NULL
};

/**
 * The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main()
{
   // Initialize the CUnit test registry.
   if(CU_initialize_registry() != CUE_SUCCESS)
      return CU_get_error();

   if(CU_register_suites(suites) != CUE_SUCCESS)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // Run all tests using the CUnit Basic interface.
   CU_basic_set_mode(CU_BRM_NORMAL);
   CU_basic_run_tests();
   CU_cleanup_registry();

   return CU_get_error();
}
