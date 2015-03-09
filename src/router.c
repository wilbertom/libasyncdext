
#ifndef ASYNCD_EXT_ROUTER_C
#define ASYNCD_EXT_ROUTER_C

#include <asyncdext/router.h>

int adext_http_router_handler(short event, ad_conn_t *conn, void *userdata) {
    
}

adext_router_t *adext_router_new(int capacity) {

}

void adext_router_free(adext_router_t *router) {

}

void adext_router_add(const char *uri, handler_cb handle) {

}

void adext_router_register_hook(adext_router_t *router, ad_server_t *server) {

}

#endif
