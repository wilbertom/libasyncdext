/**
 * router.h
 * Interface for http application routing.
 *
 * Wilberto Morales
 * wilbertomorales777@gmail.com
 *
 */

#ifndef ASYNCD_EXT_ROUTER_H
#define ASYNCD_EXT_ROUTER_H

#include <asyncd/asyncd.h>
#include <onigposix.h>

// A handler is a function that is called when a route is matched
typedef int (* handler_cb)(short event, ad_conn_t *conn, void *userdata);

// A route maps a regex to a handler.
// Create a new route with adext_route_new.
//
// adext_route_t *home_route = adext_route_new("^/$", index);
// adext_route_t *blog_route = adext_route_new("^/blog/$", blog_index);
typedef struct adext_route_s {
    const char *uri;
    handler_cb handler;
    regex_t *_uri_r;
} adext_route_t;

// Creates and initializes a new route.
adext_route_t *adext_route_new(const char *uri, handler_cb handle);

// Frees the route.
void adext_route_free(adext_route_t *route);

// This handler implements the routing for the server.
// Register this handler with ad_server_register_hook.
int adext_http_router_handler(short event, ad_conn_t *conn, void *userdata);

#endif
