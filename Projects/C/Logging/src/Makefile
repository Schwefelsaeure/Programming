CC=gcc
CFLAGS=-Wall
LDFLAGS=

BIN_LOGD=logd
BIN_LOG=log
BIN_LOG_PARSER_LINUX=log_parser_linux
BIN_LOG_PARSER_MQX=log_parser_mqx

OBJ_LOGD=logd_main.o logd.o shared_memory_helper.o log_buffer.o semaphore_helper.o
OBJ_LOG=log_main.o log.o shared_memory_helper.o log_buffer.o semaphore_helper.o
OBJ_LOG_PARSER_LINUX=log_parser_linux.o
OBJ_LOG_PARSER_MQX=log_parser_mqx.o

all: $(BIN_LOGD) $(BIN_LOG) $(BIN_LOG_PARSER_LINUX) $(BIN_LOG_PARSER_MQX)

$(BIN_LOGD): $(OBJ_LOGD)
	$(CC) -o $@ $(CFLAGS) $(OBJ_LOGD) $(LDFLAGS)

$(BIN_LOG): $(OBJ_LOG)
	$(CC) -o $@ $(CFLAGS) $(OBJ_LOG) $(LDFLAGS)

$(BIN_LOG_PARSER_LINUX): $(OBJ_LOG_PARSER_LINUX)
	$(CC) -o $@ $(CFLAGS) $(OBJ_LOG_PARSER_LINUX) $(LDFLAGS)

$(BIN_LOG_PARSER_MQX): $(OBJ_LOG_PARSER_MQX)
	$(CC) -o $@ $(CFLAGS) $(OBJ_LOG_PARSER_MQX) $(LDFLAGS)
	
%.o: %.c
	$(CC) -c $(CFLAGS) $<
clean:
	rm *.o
	rm $(BIN_LOGD)
	rm $(BIN_LOG)
	rm $(BIN_LOG_PARSER_LINUX)
	rm $(BIN_LOG_PARSER_MQX)
