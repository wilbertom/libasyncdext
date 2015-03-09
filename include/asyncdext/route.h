/**
 * route.h
 * A single route. Users shouldn't access this data structure directly,
 * see router.h instead.
 *
 * Wilberto Morales
 * wilbertomorales777@gmail.com
 *
 */

#ifndef ASYNCD_EXT_ROUTE_H
#define ASYNCD_EXT_ROUTE_H

#include <regex.h>

// A handler is a function that is called when a route is matched
typedef int (* handler_cb)(short event, ad_conn_t *conn, void *userdata);

// A route maps a regex to a handler.
// Create a new route with adext_route_new.
typedef struct adext_route_s {
    const char *uri; // a uri regular expression for example: "$/index/^"
    handler_cb handler; // the function we called when the route is matched
    regex_t *_uri_r; // secretly compiled uri to a regular expression
} adext_route_t;


#endif
