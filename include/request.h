#ifndef WINYL_REQUEST_H
#define WINYL_REQUEST_H

#include "winyl.h"

typedef struct winyl_response {
    int error;
    int socket;

    int http_version;
    int status;
    char* status_text;

    struct winyl_header* headers;
    int headers_count;
    winyl _headers;

    char* body;
    int _body_len;
} winyl_response;

#define WINYL_REQUEST_GET_SOCKET 1
#define WINYL_REQUEST_NO_HEADERS 2
#define WINYL_REQUEST_NO_NUL 4
#define WINYL_REQUEST_SLASH 8

#define WINYL_ERROR_SOCKET 2
#define WINYL_ERROR_CONNECT 3
#define WINYL_ERROR_SEND 5
#define WINYL_ERROR_RECV 6
#define WINYL_ERROR_CLOSE 9

winyl_response winyl_request(winyl* host, char* path, int flags);
void winyl_response_close(winyl_response* response);

#endif
