
#ifndef ASYNCD_EXT_ROUTER_C
#define ASYNCD_EXT_ROUTER_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <aext/router.h>

// Initializes a new route.
void adext_route_init(adext_route_t *route, const char *uri, handler_cb handle);

// Compile the route's uri.
void adext_compile_route(adext_route_t *route);

// Returns true if the request_url matches the route's uri regex.
bool adext_matches(adext_route_t *route, const char *request_url);

// Frees a list of routes.
void adext_free_routes(adext_route_t *routes);


adext_route_t *adext_route_new(const char *uri, handler_cb handle) {
    adext_route_t *route = (adext_route_t *) malloc(sizeof(adext_route_t));
    adext_route_init(route, uri, handle);
    adext_compile_route(route);
    return route;
}

void adext_route_init(adext_route_t *route, const char *uri, handler_cb handle) {
    route->uri = uri;
    route->handler = handle;
    route->_uri_r = (regex_t *) malloc(sizeof(regex_t));
}

void adext_route_free(adext_route_t *route) {
    free(route->_uri_r);
    free(route);
}

void adext_compile_route(adext_route_t *route) {
    int error = regcomp(route->_uri_r, route->uri, 0 | REG_EXTENDED);

    if (error) {
        printf("Error while compiling %s\n", route->uri);
        exit(EXIT_FAILURE);
    }
}


#endif
