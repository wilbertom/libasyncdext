## libasyncdext

My personal extensions to the [asyncd](https://github.com/wolkykim/libasyncd)
library. With asyncd one can create servers quickly because of it's nice API.
It is a really small library and these extensions add useful functionality that
is missing.

### Router

We add a HTTP router that maps URLs to handlers. See `include/asyncdext/router.h`
for more information.


### Install

```
make
make install

```

### Uninstall

```
make uninstall

```

### Example

```c


#include <asyncd/asyncd.h>

#include <asyncdext/asyncdext.h>
#include <asyncdext/router.h>

int index(short event, ad_conn_t *conn, void *userdata) {
    ad_http_response(conn, 200, "text/html", "Home page", 9);

    return AD_DONE;
}

int about(short event, ad_conn_t *conn, void *userdata) {
    ad_http_response(conn, 200, "text/html", "About page", 10);
    return AD_DONE;
}

int main(int argc, char *argv[]) {
    ad_server_t *server = ad_server_new();

    ad_server_set_option(server, "server.port", "8888");

    adext_router_t *router = adext_router_new(2);
    adext_router_add(router, "^/$", index);
    adext_router_add(router, "^/about/$", about);

    ad_server_register_hook(server, ad_http_handler, NULL);
    adext_router_register_hook(router, server);

    return ad_server_start(server);

}

```
