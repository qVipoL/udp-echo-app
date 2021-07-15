
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#ifndef UDP
#define UDP
#define BUFFER_LEN 512
#define PORT 8888

typedef struct sockaddr_in saddr_in;
typedef struct sockaddr saddr;

void error(char *s);

int init_udp_socket();

saddr_in init_udp_client(char *address, int port);

void clear_buffer();

void udp_client_listen(int socket_fd, saddr_in si_other);

saddr_in init_udp_server(int socket_fd, int port);

void udp_server_listen(int socket_fd, saddr_in si_me);

char *get_valid_ip();

int get_valid_port();

#pragma region helpers

bool validate_number(char *str);

bool validate_ip(char *ip);

bool validate_port(int port);

#pragma endregion

#endif