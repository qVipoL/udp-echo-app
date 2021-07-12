#include "udp.h"

int main()
{
    int port, socket_fd;
    saddr_in si_me;

    printf("enter port: ");
    scanf("%d", &port);

    socket_fd = init_udp_socket();
    printf("socket initialized\n");
    si_me = init_udp_server(socket_fd, port);
    printf("server started on port:%d\n", port);

    udp_server_listen(socket_fd, si_me);

    close(socket_fd);

    return 0;
}