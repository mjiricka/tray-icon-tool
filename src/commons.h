#ifndef COMMONS_H
#define COMMONS_H

struct tray_icon_data {
   char msg[8]; // 8 characters must be enough for anyone!
   float r, g, b;
};

void init_tray_icon_data(struct tray_icon_data *tid, char *msg);

void prepare_connection(const char *socket_path, int *soc, struct sockaddr_un *addr);


#endif /* COMMONS_H */
