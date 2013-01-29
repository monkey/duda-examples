/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include "webservice.h"

DUDA_REGISTER("Duda I/O Examples", "002 Query String");

void cb_query_string(duda_request_t *dr)
{
    response->http_status(dr, 200);

    /* If we dont have a valid query string just send an error */
    if (qs->count(dr) == 0) {
        response->printf(dr, "Invalid query string, check the README file");
    }
    else {
        response->printf(dr,
                         "Fruit='%s' and Drink='%s'",
                         qs->get(dr, "fruit"),
                         qs->get(dr, "drink"));
    }

    response->end(dr, NULL);
}

int duda_main()
{
    map->static_add("/", "cb_query_string");

    return 0;
}
