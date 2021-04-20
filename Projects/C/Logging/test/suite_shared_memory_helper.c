#include "suite_shared_memory_helper.h"
#include "../src/shared_memory_helper.h"

#include <CUnit/CUnit.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "../src/log_buffer.h"

// ----------------------------------------------------------------------------
// -------------------------- Private Types -----------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Private Data ------------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ------------------- Private Methods (Declarations) -------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------- Private Methods (Definitions) -------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------


int32_t suite_shared_memory_helper_init()
{
	return 0;
}

int32_t suite_shared_memory_helper_cleanup()
{
	if(system("ipcrm -M 1234") < 0)
	{
		printf("system(\"ipcrm -M 1234\") failed!");
		return -1;
	}
	else
		return 0;
}

void test_shared_memory_helper_create_shared_memory()
{
	log_buffer_t *log_buffer = shared_memory_helper_create_shared_memory();
	
	CU_ASSERT_PTR_NOT_NULL(log_buffer);
}

void test_shared_memory_helper_create_shared_memory_2nd_call_fails()
{
	log_buffer_t *log_buffer = shared_memory_helper_create_shared_memory();
	
	CU_ASSERT_PTR_NULL(log_buffer);
}

void test_shared_memory_helper_open_shared_memory()
{
	log_buffer_t *log_buffer = shared_memory_helper_open_shared_memory();
	
	CU_ASSERT_PTR_NOT_NULL(log_buffer);
}

void test_shared_memory_helper_open_shared_memory_initial_values()
{
	log_buffer_t *log_buffer = shared_memory_helper_open_shared_memory();
	
	CU_ASSERT_EQUAL(log_buffer->write_position, 0);
	CU_ASSERT_EQUAL(log_buffer->read_position, 0);
	CU_ASSERT_EQUAL(log_buffer->overflow, false);
}