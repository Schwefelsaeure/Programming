#include <stdlib.h>
#include "logd.h"

int main()
{
	logd_init();
	
	while(1)
	{
		logd_wait_for_new_log_entry();
		logd_process_new_log_entry();
	}

	return EXIT_SUCCESS;
}