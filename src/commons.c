#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "commons.h"


// ******************************************************************
//  PUBLIC FUNCTIONS IMPLEMENTATION
// ******************************************************************

void init_tray_icon_data(struct tray_icon_data *tid, char *msg)
{
   strncpy(tid->msg, msg, 7);
   tid->msg[7] = '\0';

   tid->r = 1.0;
   tid->g = 1.0;
   tid->b = 1.0;
}


void prepare_connection(const char *socket_path, int *soc, struct sockaddr_un *addr)
{
   // Prepare socket.
   if ((*soc = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
      perror("Cannot create socket");
      exit(EXIT_FAILURE);
   }

   // Prepare address.
   memset(addr, 0, sizeof(*addr));
   addr->sun_family = AF_UNIX;
   strncpy(addr->sun_path, socket_path, sizeof(addr->sun_path)-1);
}
