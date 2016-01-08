#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "commons.h"



// ******************************************************************
//  PUBLIC FUNCTIONS IMPLEMENTATION
// ******************************************************************

void client_run(char *socket_path, char *title)
{
   int soc;
   struct sockaddr_un addr;
   prepare_connection(socket_path, &soc, &addr);

   // Connect to server.
   if (connect(soc, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
      perror("Cannot connect to given address");
      exit(EXIT_FAILURE);
   }

   // Prepare structure to send.
   struct tray_icon_data buf;
   init_tray_icon_data(&buf, title);

   // Send it.
   ssize_t ret = write(soc, &buf, sizeof(buf));
   close(soc);

   // Check result.
   if (ret != sizeof(buf)) {
      perror("Write error");
      exit(EXIT_FAILURE);
   }
}

