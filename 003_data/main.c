/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include "webservice.h"

DUDA_REGISTER("Duda I/O Examples", "Data directory");

/*
 * This callback prints back to the browser the content of the example.dat
 * file located in DataDir
 */
void cb_data_example(duda_request_t *dr)
{
    /* define some local variables */
    const char *datadir_path;
    char *example_path;

    /* set the response HTTP status */
    response->http_status(dr, 200);

    /* do buffering of the current web service data directory */
    datadir_path = data->get_path();

    /* lookup the absolute path for file example.dat */
    example_path = data->locate("example.dat");

    /* do some string buffering */
    response->printf(dr, "The web service data dir is '%s'\n\n", datadir_path);
    response->printf(dr, "example.dat is located at '%s'", example_path);

    /* finalize */
    response->end(dr, NULL);
}

int duda_main()
{
    map->static_add("/", "cb_data_example");

    return 0;
}
