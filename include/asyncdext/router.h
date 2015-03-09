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
#include <regex.h>

// This part of the library implements a small routing interface to libasyncd.
// It has a simple API based on regular expressions and callback functions.
// To get started we create a new application router:
//
// adext_router_t *router = adext_router_new();
//
// Once the router has been created we are going to add routes to it.
//
// adext_router_add("$^", index);
// adext_router_add("$/blog/^", blog_index);
//
// The we want to add the router handler to the asyncd server. If you
// don't register the hook, the router will not work.
//
// ad_server_register_hook(server, ad_http_handler, NULL);
// adext_router_register_hook(router, server);
//
// Whenever a new request url is matched to a route it's handler_cb will
// be executed.
//
// int index(short event, ad_conn_t *conn, void *userdata) {
//    ...
// }
//
// int blog_index(short event, ad_conn_t *conn, void *userdata) {
//    ...
// }

// A handler is a function that is called when a route is matched
typedef int (* handler_cb)(short event, ad_conn_t *conn, void *userdata);

// A route maps a regex to a handler.
// Create a new route with adext_route_new.
typedef struct adext_route_s {
    const char *uri;
    handler_cb handler;
    regex_t *_uri_r;
} adext_route_t;

// A router collects a bunch of routes.
typedef struct adext_router_s {
    adext_route_t *_routes;
    int _count;
} adext_router_t;

// Creates and initializes a new route.
adext_router_t *adext_router_new();

// Frees the router.
void adext_router_free(adext_router_t *router);

// Adds a new route to the router that maps the uri regex to the handler.
void adext_router_add(const char *uri, handler_cb handle);

// Call this once after initializing your ad_server_t and registering the
// ad_http_handler.
void adext_router_register_hook(adext_router_t *router, ad_server_t *server);

#endif
