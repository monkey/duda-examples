/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include "webservice.h"

DUDA_REGISTER("Duda I/O Examples", "Hello World");

void cb_hello(duda_request_t *dr)
{
    response->http_status(dr, 200);
    response->printf(dr, "Hello World!");
    response->end(dr, NULL);
}

int duda_main()
{
    map->static_add("/", "cb_hello");

    return 0;
}
