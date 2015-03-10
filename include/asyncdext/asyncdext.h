/**
 * asyncdext.h
 * libasyncd extensions.
 *
 * Wilberto Morales
 * wilbertomorales777@gmail.com
 *
 */

#ifndef ASYNCD_EXT_H
#define ASYNCD_EXT_H

#define ASYNCD_EXT_VERSION "0.0.2"

// A handler that returns a 404 response,
// make sure to register this handler last.
int adext_404_handler(short event, ad_conn_t *conn, void *userdata);

// A function that works just like ad_server_new but sets the address
// and port using ad_server_set_option.
ad_server_t *adext_server_new(const char *address, const char *port);

#endif
