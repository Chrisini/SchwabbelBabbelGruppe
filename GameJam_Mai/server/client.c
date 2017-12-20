/*
    C ECHO client example using sockets
 * anlehnung an: http://www.binarytides.com/server-client-example-c-sockets-linux/
*/
  #include <stdio.h> //printf
  #include<string.h> //strlen
  #include<sys/socket.h> //socket
  #include<arpa/inet.h> //inet_addr
  #include<stdlib.h>

  int main(int argc, char * argv[]) {
    int sock;
    struct sockaddr_in servaddr;
    char message[1000], server_reply[2000];

    //Create socket
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
      printf("Could not create socket");
    }
    puts("Socket created");

    servaddr.sin_addr.s_addr = inet_addr("192.168.1.55");
    servaddr.sin_family = PF_INET; // we use ipv4
    servaddr.sin_port = htons(6778);

    //Connect to remote server
    if (connect(sock, (struct sockaddr * ) & servaddr, sizeof(servaddr)) < 0) {
      perror("connect failed. Error");
      return 1;
    }

    puts("Connected\n");

    //keep communicating with server
    while (1) {
      memset( & server_reply, 0, sizeof(server_reply));
      //Receive a reply from the server
      if (recv(sock, server_reply, 2000, 0) < 0) {
        puts("recv failed");
        break;
      }
      puts("Server reply :");
      puts(server_reply);
      if (strncmp(server_reply, "Yes.", 4) == 0) {
        exit(EXIT_SUCCESS);
      }

      memset( & message, 0, sizeof(message));
      printf("Enter message : ");
      scanf("%s", message);

      //Send some data
      if (send(sock, message, strlen(message), 0) < 0) {
        puts("Send failed");
        return 1;
      }

    }

    // close(sock);
    return 0;
  }
