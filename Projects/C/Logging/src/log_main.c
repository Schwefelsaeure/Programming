#include <stdio.h>
#include <stdlib.h>
#include "log.h"

int main()
{
	if(log_init() == false)
		return EXIT_FAILURE;

	while(1)
	{
		if(getchar() == 'q')
			break;
		else
		{
			if(log_data(1, 1.0) == false)
				perror(NULL);
			if(log_message(DEBUG, "A log message with log level \"DEBUG\".") == false)
				perror(NULL);
		}
	}

	return EXIT_SUCCESS;
}
