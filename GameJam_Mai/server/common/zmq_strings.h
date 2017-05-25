#ifndef __zmq_strings_h_
#define __zmq_strings_h_

/*
 * ZeroMQ connects a variety of different programming languages
 * Those languages have very different means of representing strings
 * Thus, ZeroMQ has mandated that all strings be sent without '\0' as
 * message parts are already length-specified.
 *
 * The helper functions in this file send C-strings to a socket without
 * the terminating zero byte and receive strings without zero byte and
 * append it.
 */

/*
 * msg_recv_string() received a message part, allocates a buffer via
 * malloc() large enough for the contained string Plus the trailing '\0' byte
 * and copies the string to the buffer.
 *
 * If successful, returns a pointer to a string. Returns NULL otherwise
 */
char *msg_recv_string(void *socket, zmq_msg_t *msg);

/*
 * send_string() sends a string without a trailing zero byte.
 */
int send_string(void *socket, char *string, int flags);

#endif /* __zmq_strings_h_ */