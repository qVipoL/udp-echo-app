#include "../include/udp.h"

void error(char *s)
{
    perror(s);
    exit(1);
}

int init_udp_socket()
{
    int socket_fd;

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        error("failed to create socket\n");

    return socket_fd;
}

saddr_in init_udp_client(char *address, int port)
{
    saddr_in si_other;
    memset((char *)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(port);

    if (inet_aton(address, &si_other.sin_addr) == 0)
        error("failed to assign server address\n");

    return si_other;
}

void clear_buffer()
{
    int c;
    while ((c = getchar()) != EOF && c != '\n')
        ;
}

void udp_client_listen(int socket_fd, saddr_in si_other)
{
    char buffer_in[BUFFER_LEN], buffer_out[BUFFER_LEN];
    int slen = sizeof(si_other);
    clear_buffer();

    while (true)
    {
        printf("enter message ('exit' to stop): ");
        fgets(buffer_out, BUFFER_LEN, stdin);
        buffer_out[strlen(buffer_out) - 1] = '\0';

        if (strcmp(buffer_out, "exit") == 0)
            break;

        if (sendto(socket_fd, buffer_out, strlen(buffer_out), 0, (saddr *)&si_other, slen) == -1)
            error("failed to send data\n");

        memset(buffer_in, '\0', BUFFER_LEN);

        if (recvfrom(socket_fd, buffer_in, BUFFER_LEN, 0, (saddr *)&si_other, (socklen_t *)&slen) == -1)
            error("failed to recieve data\n");

        printf("recieved: %s\n", buffer_in);
    }
}

saddr_in init_udp_server(int socket_fd, int port)
{
    saddr_in si_me;

    memset((char *)&si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(socket_fd, (saddr *)&si_me, sizeof(si_me)) == -1)
        error("bind failed\n");

    return si_me;
}

void udp_server_listen(int socket_fd, saddr_in si_me)
{
    int recv_len, slen = sizeof(si_me);
    saddr_in si_other;
    char buffer_in[BUFFER_LEN];

    while (true)
    {
        printf("waiting for data...\n");

        if ((recv_len = recvfrom(socket_fd, buffer_in, BUFFER_LEN, 0, (saddr *)&si_other, (socklen_t *)&slen)) == -1)
            error("failed recieving data\n");

        buffer_in[recv_len] = '\0';

        printf("received data from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("data: %s\n", buffer_in);

        if (sendto(socket_fd, buffer_in, recv_len, 0, (saddr *)&si_other, slen) == -1)
            error("failed sending data\n");
    }
}

char *get_valid_ip()
{
    char address[256];

    printf("enter ipv4 address: ");
    fgets(address, 256, stdin);
    address[strlen(address) - 1] = '\0';

    while (!validate_ip(address))
    {
        printf("invalid address\n");
        printf("enter ipv4 address: ");

        fgets(address, 256, stdin);
        address[strlen(address) - 1] = '\0';
    }

    return strdup(address);
}

int get_valid_port()
{
    int port;

    printf("enter port: ");
    scanf("%d", &port);

    while (!validate_port(port))
    {
        printf("invalid port\n");
        printf("enter port: ");
        scanf("%d", &port);
    }

    return port;
}

#pragma region helpers

bool validate_number(char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
            return false;
        str++;
    }

    return true;
}

bool validate_ip(char *addr)
{
    int num, dots = 0;
    char *ptr, *ip = strdup(addr);

    if (!ip)
        return false;

    if (strcmp(ip, "localhost") == 0)
        return true;

    ptr = strtok(ip, ".");

    if (!ptr)
    {
        free(ip);
        return false;
    }

    while (ptr)
    {
        if (!validate_number(ptr))
        {
            free(ip);
            return false;
        }

        num = atoi(ptr);

        if (num < 0 && num > 255)
        {
            free(ip);
            return false;
        }

        ptr = strtok(NULL, ".");

        if (ptr != NULL)
            dots++;
    }

    free(ip);

    return dots != 3 ? false : true;
}

bool validate_port(int port)
{
    return port > 0 && port <= 65535;
}

#pragma endregion
