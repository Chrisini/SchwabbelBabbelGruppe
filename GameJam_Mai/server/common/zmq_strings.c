#include <zmq.h>
#include <string.h>
#include <stdlib.h>

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
char *msg_recv_string(zmq_msg_t *msg,void *socket) {

    if (zmq_msg_recv(msg,socket,0) == -1) {
        fprintf(stderr,"zmq_getsockopt() failed: %s.\n", zmq_strerror(zmq_errno()));
        return NULL;
    }
    
    size_t msg_data_size = zmq_msg_size(msg);
    char *pdata  = zmq_msg_data(msg);
    char *string = malloc(msg_data_size+1); // +1 for '\0'
    
    if (string == NULL) {
        fprintf(stderr,"Could not allocate memory.\n");
        return NULL;
    }
    
    string[msg_data_size] = '\0';
    return memcpy(string,pdata,msg_data_size);
    
}

/*
 * send_string() sends a string without a trailing zero byte.
 */
int send_string(void *socket, char *string, int flags) {
    return zmq_send(socket,string,strlen(string),flags);
}