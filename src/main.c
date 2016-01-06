#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "client.h"
#include "server.h"

// TODO: include header filu,
// chytani signalu,
// zkusit valgrind pred gtk,
// typedef na struct,
// komenty na lokalni/public
// debug vypis pres -v param?
// argparse

// (start|set) <tmpfile> <start string> <color> [<tooltip>] [<script>]

int main (int argc, char **argv)
{
   if (argc != 4) {
      fprintf(stderr, "Bad param.\n");
	  return EXIT_FAILURE;
   }

   char *action_name = argv[1];
   char *socket_path = argv[2];
   char *title = argv[3];

   if (strcmp(argv[1], "client") == 0) {
      printf("Starting client...\n");
      run_client(socket_path, title);
   } else if (strcmp(argv[1], "server") == 0) {
      printf("Starting server...\n");
      run_server(socket_path, title);
   } else {
      fprintf(stderr, "Bad param.\n");
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}

