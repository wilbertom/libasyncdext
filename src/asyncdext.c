
#include <asyncdext.h>

int adext_404_handler(short event, ad_conn_t *conn, void *userdata) {
    if (ad_http_get_status(conn) == AD_HTTP_REQ_DONE) {

        ad_http_response(
            conn, 404, "text/html",
            "<title>404 Not Found</title><h1>Not Found</h1><p>The requested URL was not found on the server. If you entered the URL manually please check your spelling and try again.</p>",
            173
        );

        return AD_CLOSE;
    }

    return AD_OK;
}

ad_server_t *adext_server_new(const char *address, const char *port) {
    ad_server_t *server = ad_server_new();
    ad_set_option(server, "server.addr", address);
    ad_set_option(server, "server.port", port)
    return server;
}
