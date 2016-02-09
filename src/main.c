#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "commons.h"
#include "client.h"
#include "server.h"

// TODO: 
// chytani signalu,
// zkusit valgrind pred gtk,
// debug vypis pres -v param?
// argparse


void print_usage(char *prog_name)
{
   printf("USAGE: %s <server|client> <temp file> <label> <color> [<tooltip>] [<script>]\n", prog_name);
   printf("where:\n");
   printf("   Server displays tray icon. Client can change the icon.\n");
   printf("   temp file:\n");
   printf("      Path where program opens communication socket between server and client.\n");
   printf("   label: \n");
   printf("      Text to display in icon tray. Text should be max 3 characters long.\n");
   printf("   color:\n");
   printf("      Color of text. Format is RRGGBB, for example: FF0000 for red text.\n");
   printf("   tooltip:\n");
   printf("      Tooltip to display on icon.\n");
   printf("   script:\n");
   printf("      Script to run when user clicks on icon. Consider to use \"&\".\n");
   printf("\n");
}


int main (int argc, char **argv)
{
   // TODO: define upper bound.
   if (argc < 4) {
      fprintf(stderr, "Not enough parameters.\n\n");
      print_usage(argv[0]);
	  return EXIT_FAILURE;
   }

   char *action_name = argv[1];
   char *socket_path = argv[2];
   char *title = argv[3];
   char *tooltip = "";
   char *on_click_command = "";
   struct rgb_color color;

   if (5 <= argc) {
      if (parse_color(argv[4], &color)) {
         fprintf(stderr, "Bad color format (e.g. FF0099).\n\n");
         print_usage(argv[0]);
         return EXIT_FAILURE;
      }

      if (6 <= argc) {
         tooltip = argv[5];

         if (7 <= argc) {
            on_click_command = argv[6];
         }
      }
   } else {
      // White is default.
      parse_color("FFFFFF", &color);
   }

   struct tray_icon_data tid;
   init_tray_icon_data(&tid, title, &color, tooltip, on_click_command);

   if (strcmp(action_name, "client") == 0) {
      printf("Starting client...\n");
      client_run(socket_path, &tid);
   } else if (strcmp(argv[1], "server") == 0) {
      printf("Starting server...\n");
      server_run(socket_path, &tid);
   } else {
      fprintf(stderr, "Bad param %s, must be client or socket.\n\n", argv[1]);
      print_usage(argv[0]);
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}

