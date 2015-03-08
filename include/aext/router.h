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
#include <regex.h>

// Routes map methods and regexes to handlers.
// Create a new route with aext_route_new.
//
// aext_route_t *home_route = aext_route_new("^/$", HTTP_GET, index);
// aext_route_t *blog_route = aext_route_new("^/blog/$", HTTP_GET, blog_index);
// ...
// aext_route_delete(r);
//
typedef aext_route_s {
    const char *uri,
    const char *mehtod,
    regex_t *_uri_r,
    route_cb handler
} aext_route_t;

// Creates a new route.
route_t *aext_route_new(const char *uri, http_method method, route_cb handler);

// Deletes the route.
route_t *aext_route_delete(route_t *route);

// This handler implements the routing for the server.
// Register this handler with ad_server_register_hook.
int aext_http_router_handler(short event, ad_conn_t *conn, void *userdata);

// Returns true if the request_url matches the route's uri regex.
bool aext_match(route_t *route, const char *request_url);

// With this function we compile all the routes at the same time. You only
// need to call this function once before running the server(ad_server_start).
void compile_routes(aext_route_t[] routes);

#endif
