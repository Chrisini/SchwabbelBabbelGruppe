// the following application can be used unmodified from within a
// server application
//
// Compile with: gcc -Wall -o demo demo.c
//
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

  int main(void) {

    char buf[80];
    int readlen;

    memset(buf, '\0', sizeof(buf));

    while (strncmp(buf, "42", 2) != 0) {
      sprintf(buf, "What's the answer to god, the universe and everything?\n");
      write(1, buf, strlen(buf));

      readlen = read(0, buf, 5);
      buf[readlen] = '\0';

      if (strncmp(buf, "42", 2) == 0) {
        sprintf(buf, "Yes.\n");
        write(1, buf, strlen(buf));
        break;
      } else {
        sprintf(buf, "No.\n");
        write(1, buf, strlen(buf));
      }
    }
    exit(0);
  }
