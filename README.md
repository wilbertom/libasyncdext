## libasyncdext

My personal extensions to the [asyncd](https://github.com/wolkykim/libasyncd)
library. With asyncd one can create servers quickly because of it's nice API.
It is a really small library and these extensions add useful functionality that
is missing.

### Router

We add a HTTP router that maps URLs to handlers. See `include/asyncdext/router.h`
for more information.
