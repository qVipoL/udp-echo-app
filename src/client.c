#include "../include/udp.h"

int main()
{
    int socket_fd, port;
    char *address;
    saddr_in si_other;

    address = get_valid_ip();
    port = get_valid_port();

    socket_fd = init_udp_socket();
    printf("socket initialized\n");

    si_other = init_udp_client(address, port);
    printf("udp connection with %s:%d is established\n", address, port);

    udp_client_listen(socket_fd, si_other);

    free(address);
    close(socket_fd);

    return 0;
}