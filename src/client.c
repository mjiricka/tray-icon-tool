#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "commons.h"


void run_client(char *socket_path, char *title)
{
   int soc;
   struct sockaddr_un addr;
   prepare_connection(socket_path, &soc, &addr);

   // Connect to server.
   if (connect(soc, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
      perror("Cannot connect to given address");
      exit(EXIT_FAILURE);
   }

   // Start sending.
 
   ssize_t rc;
   char buf[BUFFER_SIZE];

   while (0 < (rc=read(STDIN_FILENO, buf, sizeof(buf)))) {
      if (write(soc, buf, rc) != rc) {
         if (rc > 0) fprintf(stderr,"partial write");
         else {
           perror("write error");
           exit(EXIT_FAILURE);
         }
      }
   }

   close(soc);
}
