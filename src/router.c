
#ifndef ASYNCD_EXT_ROUTER_C
#define ASYNCD_EXT_ROUTER_C

#include <asyncdext/router.h>

// This is the function that ties the routing together, it is added
// to asyncd with adext_router_register_hook. From this function we
// get our router from userdata and match the request url to one of it's
// routes.
int adext_http_router_handler(short event, ad_conn_t *conn, void *userdata) {

    if (ad_http_get_status(conn) == AD_HTTP_REQ_DONE) {

        adext_router_t *router = (adext_router_t *) userdata;
        struct ad_http_s *extra = (struct ad_http_s*) ad_conn_get_extra(conn);
        char *request_uri = extra->request.uri;

        for (int i = 0; i < router->_size; i++) {
            adext_route_t *r = router->_routes[i];

            if (adext_route_matches(r, request_uri)) {

                return r->handler(event, conn, userdata);
            }
        }

    }

    return AD_OK;

}

adext_router_t *adext_router_new(int capacity) {

    int router_size = sizeof(adext_router_t) + (sizeof(adext_route_t) * capacity);
    adext_router_t *router = (adext_router_t *) malloc(router_size);
    router->_capacity = capacity;
    router->_size = 0;

    return router;
}

void adext_router_free(adext_router_t *router) {

    for (int i = 0; i < router->_size; i++)
        adext_route_free(router->_routes[i]);

    free(router);
}

void adext_router_add(adext_router_t *router, const char *uri, handler_cb handle) {

    router->_size++;

    if (router->_size > router->_capacity) {
        // TODO: Implement resize
        printf("Router resizing is not implemented, reached capacity.\n");
        exit(EXIT_FAILURE);
    }

    router->_routes[router->_size - 1] = adext_route_new(uri, handle);

}

// In this function we register our adext_http_router_handler. We
// wrap ad_server_register_hook because we want to make sure that userdata
// passed in is a router.
void adext_router_register_hook(adext_router_t *router, ad_server_t *server) {
    ad_server_register_hook(server, adext_http_router_handler, router);
}

#endif
