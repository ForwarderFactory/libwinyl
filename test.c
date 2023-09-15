#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <winyl/winyl.h>
#include <winyl/request.h>
#include <winyl/header.h>

#include <yuarel.h>

int main(int argc, char* argv[]) {
    char* url = malloc(argc <= 1 ? 28 : strlen(argv[argc - 1] + 1));
    strcpy(url, argc <= 1 ? "http://postman-echo.com/get" : argv[argc - 1]);

    printf("Requesting %s\n", url);
    
    struct yuarel url_info;
    if (yuarel_parse(&url_info, url) == -1) {
        printf("Failed parsing URL\n");
        exit(1);
    }

    winyl host = winyl_open(url_info.host, url_info.port == 0 ? 80 : url_info.port);
    if (host.error != 0) {
        if (host.error == WINYL_ERROR_DNS) printf("DNS failed :/\n");
        else printf("Unknown error %d\n", host.error);
        winyl_close(&host);
        exit(1);
    }

    printf("\n");
    winyl_response res = winyl_request(&host, url_info.path, WINYL_REQUEST_SLASH);

    printf("HTTP/%d.%d %d %s\n", res.http_version / 10, res.http_version % 10, res.status, res.status_text);
    if (winyl_has_header2(&res, "Content-Type") != -1) {
        printf("Content-Type: %s\n", winyl_get_header_value2(&res, "Content-Type"));
    }
    printf("%s\n", res.body);

    winyl_response_close(&res);
    winyl_close(&host);
    free(url);
}
