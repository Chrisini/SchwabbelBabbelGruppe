#include <zmq.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/types.h>
#include <signal.h>

#include "../common/messages.h"
#include "../common/zmq_strings.h"

/*
 * The chat server application listens on one port for incoming requests
 * (Request: Post a message) and relays the message to all connected
 * Subscribers along with channel, nickname and time information.
 */

struct _resources {
    char *rqportspec;
    char *pubportspec;
    void *zmq_ctx;
    void *reply_socket;
    void *publisher_socket;
    zmq_msg_t *msg;
} resources = {.rqportspec = NULL, .pubportspec = NULL, .zmq_ctx = NULL,
               .reply_socket = NULL, .publisher_socket = NULL, .msg = NULL};


int strfnow(char *s, size_t max, const char *format)
{
    time_t t;
    struct tm *tmp;

    t = time(NULL);
    tmp = localtime(&t);
    if (tmp == NULL) {
        perror("localtime");
        exit(EXIT_FAILURE);
    }

    return strftime(s, max, format, tmp);
}

void cleanup_and_exit(int rv)
{

    free(resources.rqportspec);
    free(resources.pubportspec);
    
    if (resources.msg != NULL && zmq_msg_close(resources.msg) != 0)
        fprintf(stderr, "Closing message failed: %s\n", zmq_strerror(zmq_errno()));

    if (resources.publisher_socket != NULL && zmq_close(resources.publisher_socket) != 0)
        fprintf(stderr, "Closing publisher socket failed: %s\n", zmq_strerror(zmq_errno()));

    if (resources.reply_socket != NULL && zmq_close(resources.reply_socket) != 0)
        fprintf(stderr, "Closing request socket failed: %s\n", zmq_strerror(zmq_errno()));

    if (resources.zmq_ctx != NULL && zmq_ctx_destroy(resources.zmq_ctx) != 0)
        fprintf(stderr, "Destroying context failed: %s\n", zmq_strerror(zmq_errno()));

    exit(rv);
}


int send_reply(void *socket, reply_type_t rep, char *string)
{
    int rv = -1;

    rv = zmq_send(socket,&rep,sizeof(rep),ZMQ_SNDMORE);

    if (rv == -1) {
        fprintf(stderr,"Sending reply type failed: %s.\n", zmq_strerror(zmq_errno()));
        return -1;
    }

    rv = send_string(socket,string,0);

    if (rv == -1) {
        fprintf(stderr,"Sending reply content failed: %s.\n", zmq_strerror(zmq_errno()));
        return -1;
    }

    return 0;
}

void usage(char *prog, FILE *fp, int rv) {
    
    fprintf(fp,"Usage: %s [OPTIONS]\n\n" \
               "-h      Prints this message\n" \
               "-r      Port for request socket (0 - 65535)\n" \
               "-p      Port for publish socket (0 - 65535)\n",prog);
    
    exit(rv);
}


void aborthandler(int ign) {
    (void) ign;
    printf("\rClosing.\n");
    cleanup_and_exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{

    zmq_msg_t msg;
    
    resources.msg = &msg;

    char *rqport = NULL;
    char *pubport = NULL;
    char opt;

    while ((opt = getopt(argc, argv, "p:r:h")) != -1) {
        switch(opt) {
        case 'p':
            pubport = optarg;
            break;
        case 'r':
            rqport = optarg;
            break;
        case 'h':
            usage(argv[0],stdout,EXIT_SUCCESS);
        }
    }

    if (rqport == NULL || pubport == NULL) {
        usage(argv[0],stderr,EXIT_FAILURE);
    }
    
    resources.rqportspec = malloc(strlen("tcp://*:")+strlen(rqport)+1);
    
    if (resources.rqportspec == NULL) {
        fprintf(stderr,"Could not allocate memory");
    }
    
    resources.pubportspec = malloc(strlen("tcp://*:")+strlen(pubport)+1);
    
    if (resources.pubportspec == NULL) {
        fprintf(stderr,"Could not allocate memory");
        cleanup_and_exit(EXIT_FAILURE);
    }
    
    strcpy(resources.rqportspec,"tcp://*:");
    strcat(resources.rqportspec,rqport);
    strcpy(resources.pubportspec,"tcp://*:");
    strcat(resources.pubportspec,pubport);

#ifdef DEBUG
    printf("Binding request port to %s\n", resources.rqportspec);
    printf("Binding publisher port to %s\n", resources.pubportspec);
#endif

    struct sigaction sa;

    memset(&sa,0,sizeof(sa));
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = aborthandler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        cleanup_and_exit(EXIT_FAILURE);

    resources.zmq_ctx = zmq_ctx_new();

    if (resources.zmq_ctx == NULL) {
        fprintf(stderr,"Getting zmq context failed: %s.\n", zmq_strerror(zmq_errno()));
        cleanup_and_exit(EXIT_FAILURE);
    }

    /* Creating and binding both server sockets
     * One for request/reply traffic
     * One for publishing the posts
     */

    resources.reply_socket   = zmq_socket (resources.zmq_ctx, ZMQ_REP);

    if (resources.reply_socket == NULL) {
        fprintf(stderr,"Getting zmq reply socket failed: %s.\n", zmq_strerror(zmq_errno()));
        cleanup_and_exit(EXIT_FAILURE);
    }

    if (zmq_bind(resources.reply_socket,resources.rqportspec) == -1) {
        fprintf(stderr,"Binding zmq reply socket failed: %s.\n", zmq_strerror(zmq_errno()));
        cleanup_and_exit(EXIT_FAILURE);
    }

    resources.publisher_socket = zmq_socket (resources.zmq_ctx, ZMQ_PUB);

    if (resources.publisher_socket == NULL) {
        fprintf(stderr,"Getting zmq publisher socket failed: %s.\n", zmq_strerror(zmq_errno()));
        cleanup_and_exit(EXIT_FAILURE);
    }

    if (zmq_bind(resources.publisher_socket,resources.pubportspec) == -1) {
        fprintf(stderr,"Binding zmq publisher socket failed: %s.\n", zmq_strerror(zmq_errno()));
        cleanup_and_exit(EXIT_FAILURE);
    }

    /*
     * Initializing the needed messages:
     * Message with channel name
     * Message with nick name
     * Message with post content
     */

    if (zmq_msg_init (resources.msg) == -1) {
        fprintf(stderr,"Initializing message failed: %s.\n", zmq_strerror(zmq_errno()));
        cleanup_and_exit(EXIT_FAILURE);
    }

#ifdef DEBUG
    printf("Ready for incoming connections.\n");
#endif 
    
    for(;;) {
        char *post = NULL;
        char *message;
        char *channel;
        char *nick;

        /*
         * Receive the channel message part
         */

        if ((channel = msg_recv_string(resources.msg,resources.reply_socket)) == NULL) {
            fprintf(stderr,"receiving channel failed: %s.\n", zmq_strerror(zmq_errno()));
            goto ABORT;
        }
        
#ifdef DEBUG
        printf("Channel received.\n");
#endif 

        if (!zmq_msg_more(resources.msg)) {
            fprintf(stderr,"Request failed (part missing).\n");
            goto ABORT;
        }

        /*
         * Receive the nick message part
         */

        if ((nick = msg_recv_string(resources.msg,resources.reply_socket)) == NULL) {
            fprintf(stderr,"receiving nick failed: %s.\n", zmq_strerror(zmq_errno()));
            goto ABORT;
        }
        
#ifdef DEBUG
        printf("Nickname received.\n");
#endif 

        if (!zmq_msg_more(resources.msg)) {
            fprintf(stderr,"Request failed (part missing).\n");
            goto ABORT;
        }
        
        /*
         * Receive the post content message part
         */

        if ((message = msg_recv_string(resources.msg,resources.reply_socket)) == NULL) {
            fprintf(stderr,"receiving message failed: %s.\n", zmq_strerror(zmq_errno()));
            goto ABORT;
        }
        
#ifdef DEBUG
        printf("Message received.\n");
#endif 

        /* Make broadcast message */

        post = malloc(strlen(channel) +
                      strlen(nick)    +
                      8                            + //HH:MM:SS
                      3                            + // "|||"
                      strlen(message)              +
                      1);

        if (post == NULL) {
            fprintf(stderr,"Could not allocate memory");
            goto ABORT;
        }

        char time[9];
        (void) strfnow(time,9,"%H:%M:%S");

        /*
         * Generate the post to be distributed
         */

        sprintf(post,"%s%c%s%c%s%c%s",channel,SEP,time,SEP,nick,SEP,message);

        
#ifdef DEBUG
        printf("Publishing message: %s\n",post);
#endif 
        /* Publish Message, acknowledge client*/

        if(send_string(resources.publisher_socket,post,0) == -1) {
            char *msg = "Publishing message failed.\n";
            fprintf(stderr,"%s: %s", msg, zmq_strerror(zmq_errno()));
            if (send_reply(resources.reply_socket, REPLY_TYPE_NOK, msg) == -1) {
                fprintf(stderr,"Reply failed: %s.\n", zmq_strerror(zmq_errno()));
            }
        } else {
            char *msg = "Success.\n";
            if (send_reply(resources.reply_socket, REPLY_TYPE_OK, msg) == -1) {
                fprintf(stderr,"Reply failed: %s", zmq_strerror(zmq_errno()));
            }
        }
ABORT:
        free(channel);
        channel = NULL;
        free(nick);
        nick = NULL;
        free(message);
        message = NULL;
        free(post);
        post = NULL;
    }

    return 0;
}












