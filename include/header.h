#ifndef WINYL_HEADER_H
#define WINYL_HEADER_H

#include "winyl.h"
#include "request.h"

struct winyl_header {
    char* name;
    char* value;
};

int winyl_has_header(winyl* host, char* name);
int winyl_add_header(winyl* host, char* name, char* value);
int winyl_remove_header(winyl* host, char* name);
char* winyl_get_header_value(winyl* host, char* name);

int winyl_has_header2(winyl_response* response, char* name);
char* winyl_get_header_value2(winyl_response* response, char* name);

#endif
