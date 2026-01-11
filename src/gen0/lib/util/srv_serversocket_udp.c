#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int srv_serversocket_udp
  (uint32_t ip, uint16_t port)
{
  int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  struct sockaddr_in sin = {
    .sin_family = AF_INET,
    .sin_port = htons(port),
    .sin_addr.s_addr = htonl(ip)
  };

  if (fd < 0) {
    fprintf(stderr, "Could not create socket.\n");
    return -1;
  } else if (bind(fd, (struct sockaddr*)&sin, sizeof(sin))) {
    fprintf(stderr, "Could not bind socket.\n");
    close(fd);
    return -1;
/*
  } else if (listen(fd, 1)) {
    fprintf(stderr, "Could not call listen() on socket.\n");
    close(fd);
    return -1;
*/
  }
  return fd;
}
