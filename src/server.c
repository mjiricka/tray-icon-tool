#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "commons.h"


void run_server(char *socket_path, char *title)
{
   int soc;
   struct sockaddr_un addr;
   prepare_connection(socket_path, &soc, &addr);

   // Remove socket if it already exists.
   unlink(socket_path);

   // Bind socket to address.
   if (bind(soc, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
      perror("Cannot bind socket to given address");
      exit(EXIT_FAILURE);
   }

   // Start listening.
   // 77 is max number of connections, but this number
   // should not be relevant for unix sockets?
   if (listen(soc, 77) == -1) {
      perror("Cannot start listening");
      exit(EXIT_FAILURE);
   }

   // Start reading.

   int cli;
   struct tray_icon_data buf;

   while (1) {
      // Accept connection, do not care about client's socket struct.
      if ((cli = accept(soc, NULL, NULL)) == -1) {
         perror("Cannot accept connection");
         continue;
      }

      ssize_t rc;
      // Read incoming message.
      while (0 < (rc=read(cli,&buf,sizeof(buf)))) {
         printf("read %u bytes: %.*s %f\n", rc, rc, buf.msg, buf.r);
      }
      if (rc == -1) {
         perror("read");
         exit(EXIT_FAILURE);
      }
      else if (rc == 0) {
         printf("EOF\n");
         close(cli);
      }
   }
}
