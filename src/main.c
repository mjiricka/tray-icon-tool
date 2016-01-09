#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "client.h"
#include "server.h"

// TODO: 
// chytani signalu,
// zkusit valgrind pred gtk,
// debug vypis pres -v param?
// argparse

// (client|server) <tmpfile> <start string> <color> [<tooltip>] [<script>]

int main (int argc, char **argv)
{
   // TODO: define upper bound.
   if (argc < 4) {
      fprintf(stderr, "Bad param.\n");
	  return EXIT_FAILURE;
   }

   char *action_name = argv[1];
   char *socket_path = argv[2];
   char *title = argv[3];
   struct rgb_color color;

   if (5 <= argc) {
      if (parse_color(argv[4], &color)) {
         fprintf(stderr, "Bad color format (e.g. FF0099).\n");
         return EXIT_FAILURE;
      }
   } else {
      // White is default.
      parse_color("FFFFFF", &color);
   }

   if (strcmp(argv[1], "client") == 0) {
      printf("Starting client...\n");
      client_run(socket_path, title);
   } else if (strcmp(argv[1], "server") == 0) {
      printf("Starting server...\n");
      server_run(socket_path, title);
   } else {
      fprintf(stderr, "Bad param.\n");
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}

