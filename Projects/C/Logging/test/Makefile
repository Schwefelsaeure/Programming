CC=gcc
CFLAGS=-Wall
LDFLAGS=-lcunit -lpthread

BIN=cunit_main

OBJ=cunit_main.o suite_semaphore_helper.o suite_shared_memory_helper.o suite_log_buffer.o
OBJ_UNDER_TEST=semaphore_helper.o shared_memory_helper.o log_buffer.o
SRC_UNDER_TEST=../src/

$(BIN): $(OBJ) $(OBJ_UNDER_TEST)
	$(CC) -o $@ $(CFLAGS) $(OBJ) $(OBJ_UNDER_TEST) $(LDFLAGS)

semaphore_helper.o: $(SRC_UNDER_TEST)semaphore_helper.c
	$(CC) -c $(CFLAGS) $<

shared_memory_helper.o: $(SRC_UNDER_TEST)shared_memory_helper.c log_buffer.o
	$(CC) -c $(CFLAGS) $<

log_buffer.o: $(SRC_UNDER_TEST)log_buffer.c suite_semaphore_helper.o
	$(CC) -c $(CFLAGS) $<

%.o: %.c
	$(CC) -c $(CFLAGS) $<
clean:
	rm *.o
	rm $(BIN)
	rm *.bin