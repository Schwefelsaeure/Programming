#include "logd.h"

#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "log_buffer.h"
#include "semaphore_helper.h"
#include "shared_memory_helper.h"

// ----------------------------------------------------------------------------
// -------------------------- Private Types -----------------------------------
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// -------------------------- Private Data ------------------------------------
// ----------------------------------------------------------------------------

// File:
static char filename[] = "log_linux.bin";
static FILE *file = NULL;

// Semaphore set:
static int32_t semaphore_set_id = -1;

// Shared memory (log buffer):
static log_buffer_t *log_buffer = NULL;

// ----------------------------------------------------------------------------
// ------------------- Private Methods (Declarations) -------------------------
// ----------------------------------------------------------------------------

static void cleanup_daemon(int32_t signal);
static void init_semaphore_set();
static void init_shared_memory();
static void install_signal_handler();
static void kill_log_daemon(const char *error_message);
static void open_file();
static void start_daemon();

// ----------------------------------------------------------------------------
// -------------------- Private Methods (Definitions) -------------------------
// ----------------------------------------------------------------------------

static void cleanup_daemon(int32_t signal)
{
	printf("%s [%03d]: cleaning up log daemon...\n", __FILE__, __LINE__);
	
	// Do not destroy shared memory and semaphore set here.
	// Otherwise running applications would fail.
	// Shared memory and semaphore set should be destroyed by hand.
	
	if(fclose(file) == EOF)
		perror("fclose(...) failed");
	
	printf("%s [%03d]: cleaned up log daemon.\n", __FILE__, __LINE__);
	
	exit(EXIT_SUCCESS);
}

void init_semaphore_set()
{
	if((semaphore_set_id = semaphore_helper_create_semaphore_set()) == -1)
		kill_log_daemon("semaphore_helper_create_semaphore_set() failed");
}

void init_shared_memory()
{
	if((log_buffer = shared_memory_helper_create_shared_memory()) == NULL)
		kill_log_daemon("shared_memory_helper_create_shared_memory() failed");
}

void install_signal_handler()
{
	printf("%s [%03d]: installing signal handler for SIGTERM\n", __FILE__, __LINE__);
	
	sigset_t blocked_signals;
		
	if(sigfillset(&blocked_signals) == -1)
		kill_log_daemon("sigfillset(...) failed");
	
	struct sigaction signal_action;
	
	signal_action.sa_handler = cleanup_daemon;
	signal_action.sa_mask = blocked_signals;
	
	if(sigaction(SIGTERM, &signal_action, NULL) == -1)
		kill_log_daemon("sigaction(...) failed");
	
	printf("%s [%03d]: installed signal handler for SIGTERM.\n", __FILE__, __LINE__);
}

void kill_log_daemon(const char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}

void open_file()
{
	printf("%s [%03d]: opening file %s...\n", __FILE__, __LINE__, filename);
	
	if((file = fopen(filename, "wb")) == NULL)
		kill_log_daemon("fopen(...) failed");
	
	printf("%s [%03d]: opened file.\n", __FILE__, __LINE__);
}

void start_daemon()
{
	printf("%s [%03d]: starting daemon...\n", __FILE__, __LINE__);
	
	// TODO: start daemon the Linux way (i.e. fork and kill parent process).
	install_signal_handler();
	
	printf("%s [%03d]: started daemon.\n", __FILE__, __LINE__);
}

// ----------------------------------------------------------------------------
// -------------------------- Public Methods ----------------------------------
// ----------------------------------------------------------------------------

void logd_init()
{
	init_shared_memory();
	init_semaphore_set();
	open_file();
	start_daemon();
}

void logd_process_new_log_entry()
{
	// TODO: evaluate return value.
	log_buffer_transfer_from_ring_buffer_to_filesystem(semaphore_set_id, log_buffer, file);
	
	if(fflush(file) == -1)
		perror("fflush(...) failed");
}

void logd_wait_for_new_log_entry()
{
	printf("%s [%03d]: waiting for new log entry...\n", __FILE__, __LINE__);

	if(!semaphore_helper_do_semaphore_operation(semaphore_set_id, NEW_LOG_ENTRY, SEMAPHORE_LOCK))
		kill_log_daemon("semaphore_helper_do_semaphore_operation(...) failed");
	else
		printf("%s [%03d]: new log entry.\n", __FILE__, __LINE__);
}
