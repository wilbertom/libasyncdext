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

#include <stdbool.h>

#include <asyncd/asyncd.h>

#include <regex.h>

// A handler is a function that is called when a route is matched
typedef int (* handler)(short event, ad_conn_t *conn, void *userdata);

// A route maps a regex to a handler.
// Create a new route with adext_route_new.
//
// adext_route_t *home_route = adext_route_new("^/$", index);
// adext_route_t *blog_route = adext_route_new("^/blog/$", blog_index);
typedef struct adext_route_s {
    const char *uri;
    regex_t *uri_r;
    handler handler_cb;
} adext_route_t;

// Creates a new route.
adext_route_t *adext_route_new(const char *uri, handler handle);

// Deletes the route.
adext_route_t *adext_route_free(adext_route_t *route);

// This handler implements the routing for the server.
// Register this handler with ad_server_register_hook.
int adext_http_router_handler(short event, ad_conn_t *conn, void *userdata);

// Returns true if the request_url matches the route's uri regex.
bool adext_matches(adext_route_t *route, const char *request_url);

// With this function we compile all the routes at the same time. You only
// need to call this function once before running the server(ad_server_start).
void adext_compile_routes(adext_route_t *routes);

// Frees a list of routes.
void adext_free_routes(adext_route_t *routes);

#endif
