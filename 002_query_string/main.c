/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include "webservice.h"

DUDA_REGISTER("Duda I/O Examples", "002 Query String");

void cb_query_string(duda_request_t *dr)
{
    char *fruit;
    char *drink;

    response->http_status(dr, 200);

    /*
     * Query String
     * ------------
     * On this example we are interested into get the number of incoming
     * variables through the Query String, if no one is given, just raise
     * an error message as a response body.
     *
     * Get the number of If we dont have a valid query string just send an error */
    if (qs->count(dr) == 0) {
        response->printf(dr,
                         "Invalid request, on this example we expect you perform\n"
                         "a request with a query string containing the variables\n"
                         "'fruit' and 'drink', try something like:\n\n"
                         "  http://localhost:2001/query_string/?fruit=apple&drink=tequila\n");
        response->end(dr, NULL);
    }


    /*
     * Make sure our query string variables are NOT empty (or not set)
     */
    fruit = qs->get(dr, "fruit");
    drink = qs->get(dr, "drink");

    if (!fruit || !drink) {
        response->printf(dr,
                         "Would you mind to set the apple and drink variables?, use\n"
                         "something like this:\n\n"
                         "  http://localhost:2001/query_string/?fruit=apple&drink=tequila\n");
    }
    else {
        response->printf(dr, "Cool, you did it right :)\n\n");
        response->printf(dr, "Fruit='%s' and Drink='%s'", fruit, drink);
    }

    response->end(dr, NULL);
}

int duda_main()
{
    map->static_add("/", "cb_query_string");

    return 0;
}
