/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 * Duda I/O Examples: 004 Post 01
 * ==================================
 * Simple web service to validate and print out a POST request
 */

#include "webservice.h"

DUDA_REGISTER("Duda I/O Examples", "Post");

/*
 * This is our callback defined in duda_main(). All callbacks for HTTP
 * requests receives the 'duda request' context (aka dr) which must
 * be used to compose the response or any other kind of work.
 *
 * The callback functions do not return any value, everything must be
 * done through the Duda API directly.
 */
void cb_main(duda_request_t *dr)
{
    char *data;
    unsigned long len;

    /*
     * We only want a POST request 
     * ---------------------------
     * For the example context, we only want to deal with POST
     * request types.
     *
     * On this example we are using the method is_post(), but
     * you can also use is_data() which also verify for POST 
     * and PUT.
     */
    if (request->is_post(dr) == MK_FALSE) {
        response->http_status(dr, 400);
        response->printf(dr, "We expect a POST request\n");
        response->end(dr, NULL);
    }

    /*
     * Setting HTTP status
     * -------------------
     * A direct response must contain a HTTP status, on this case
     * we are setting 200, which means 'OK', the request was valid
     * and will be processed.
     */
    response->http_status(dr, 200);

    /*
     * Response body content
     * ---------------------
     * As a response body, we will print a normal message, plus
     * the content that we received.
     *
     * Note that we are using the Garbage Collector object to instruct
     * Duda that the 'data' buffer needs to be released once this response
     * finish.
     */
    data = request->get_data(dr, &len);
    gc->add(dr, data);

    /* ready to flush and finalize */
    response->printf(dr, data);
    response->end(dr, NULL);
}


/*
 * This is the principal function loaded by Duda stack to initialize
 * the web service, it's called just one time and if it returns
 * zero it will be registered, otherwise skipped.
 */
int duda_main()
{
    /*
     * Registering a callback
     * ----------------------
     * The Map object expose methods to register callback functions
     * that matches some HTTP URI pattern.
     *
     * Note: When registering multiple callbacks they will be processed
     * in the given order, so the first match will be processed. The
     * first parameter defines the pattern and is compared like "if it
     * starts with...". No wildcards are supported at the moment.
     */
    map->static_add("/", "cb_main");

    /*
     * Return value
     * -------------
     * Returning zero means that this service is ready to run.
     */
    return 0;
}
