CFLAGS=-Wall -Wextra -pedantic -std=gnu99 -g
LDFLAGS=-lzmq

.PHONY: clean

all: zmq_chat_printer zmq_chat_poster zmq_chat_server

strings.o : common/zmq_strings.c
	$(CC) $(CFLAGS) -c $(LDFLAGS) common/zmq_strings.c -o strings.o

zmq_chat_printer: strings.o printer/printer.c common/messages.h
	$(CC) $(CFLAGS) strings.o printer/printer.c $(LDFLAGS) -o zmq_chat_printer

zmq_chat_poster: strings.o poster/poster.c common/messages.h
	$(CC) $(CFLAGS) strings.o poster/poster.c $(LDFLAGS) -o zmq_chat_poster

zmq_chat_server: strings.o server/server.c common/messages.h
	$(CC) $(CFLAGS) strings.o server/server.c $(LDFLAGS) -o zmq_chat_server

clean:
	rm -f zmq_chat_printer zmq_chat_poster zmq_chat_server strings.o
