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
 
   struct tray_icon_data buf;

   init_tray_icon_data(&buf, "");

   ssize_t rc=read(STDIN_FILENO, buf.msg, sizeof(buf.msg));
   if (write(soc, &buf, sizeof(buf)) != sizeof(buf)) {
      if (rc > 0) fprintf(stderr,"partial write");
      else {
        perror("write error");
        exit(EXIT_FAILURE);
      }
   }

   close(soc);
}
