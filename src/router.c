
#ifndef ASYNCD_EXT_ROUTER_C
#define ASYNCD_EXT_ROUTER_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <asyncdext/router.h>

// Initializes a new route.
void adext_route_init(adext_route_t *route, const char *uri, handler_cb handle);

// Function that compiles the route's regular expression(uri).
void adext_compile_route(adext_route_t *route);

// Returns true if the request_url matches the route's uri regex.
bool adext_route_matches(adext_route_t *route, const char *request_url);

// Creates and initializes a new route.
adext_route_t *adext_route_new(const char *uri, handler_cb handle);

// Frees the route.
void adext_route_free(adext_route_t *route);

// This handler implements the routing for the server.
// Register this handler with ad_server_register_hook.
int adext_http_router_handler(short event, ad_conn_t *conn, void *userdata);

adext_route_t *adext_route_new(const char *uri, handler_cb handle) {
    adext_route_t *route = (adext_route_t *) malloc(sizeof(adext_route_t));
    adext_route_init(route, uri, handle);
    return route;
}

void adext_route_init(adext_route_t *route, const char *uri, handler_cb handle) {
    route->uri = uri;
    route->handler = handle;
    adext_compile_route(route);
}

void adext_route_free(adext_route_t *route) {
    free(route->_uri_r);
    free(route);
}

void adext_compile_route(adext_route_t *route) {

    route->_uri_r = (regex_t *) malloc(sizeof(regex_t));
    int error = regcomp(route->_uri_r, route->uri, 0 | REG_EXTENDED);

    if (error) {
        printf("Error while compiling %s\n", route->uri);
        exit(EXIT_FAILURE);
    }
}

bool adext_route_matches(adext_route_t *route, const char *request_url) {
    return !(regexec(route->_uri_r, request_url, 0, NULL, 0));
}


#endif
