#ifndef WINYL_H
#define WINYL_H

#ifdef __DEVKITPPC__
#include <network.h>
#else
#include <netdb.h>
#endif

#define WINYL_INTLEN(x) ({int r = 1; int v = x; while(v > 9) { r++; v /= 10; }; r;})

struct winyl_header;

typedef struct winyl {
    int error;

    char* hostname;
    int port;
    struct winyl_header* headers;

    int _hostname_len;
    int _port_len;
    int _headers_count;

    int _http_version;
    char* _method;
    struct hostent* _dns;
    int _dns_hosts;
    struct sockaddr_in _addr;
} winyl;

#define WINYL_ERROR_DNS 1
#define WINYL_ERROR_NX 4
#define WINYL_ERROR_PORT 7
#define WINYL_ERROR_MALLOC 8

winyl winyl_open(char* hostname, int port);
void winyl_close(winyl* host);

int winyl_change_http(winyl* host, int version);

#endif
