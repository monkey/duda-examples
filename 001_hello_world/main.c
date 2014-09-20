/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 * Duda I/O Examples: 001 Hello World
 * ==================================
 * This example aim to explain how the most basic web service under
 * Duda I/O should work covering the mandatory duda_main() and a minimum
 * callback to be triggered upon HTTP requests.
 */

#include "webservice.h"

DUDA_REGISTER("Duda I/O Examples", "Hello World");

/*
 * This is our callback defined in duda_main(). All callbacks for HTTP
 * requests receives the 'duda request' context (aka dr) which must
 * be used to compose the response or any other kind of work.
 *
 * The callback functions do not return any value, everything must be
 * done through the Duda API directly.
 */
void cb_foo(duda_request_t *dr)
{
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
     * As a response body, you can send a file or reply with some
     * data, on this example we will use the printf() method that
     * is part of the Response object to instruct the stack to
     * send out a text which contains the 'Hello World!' message.
     */
    response->printf(dr, "Hello World from foo!");


    /*
     * Finalizing
     * ----------
     * As described earlier, a callback do not return any value
     * but per API spec it must instruct the stack that the response
     * is ready to be send so we finalize using the end() method.
     *
     * Note that this call will perform an explicit additional return
     * so every code after this will not be processed.
     */
    response->end(dr, NULL);
}

/*
 * This second callback is also defined inside duda_main(), we just
 * print out a different message in the response.
 */
void cb_bar(duda_request_t *dr)
{
    response->http_status(dr, 200);
    response->printf(dr, "Hello World from bar!");
    response->end(dr, NULL);
}

/* The root callback, only triggered when requesting the root URI */
void cb_root(duda_request_t *dr)
{
    response->http_status(dr, 200);
    response->printf(dr, "Welcome to my world! I'm the root callback!");
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
     * Registering some callbacks
     * --------------------------
     * The Router object expose methods to register callback functions
     * that matches some HTTP URI pattern.
     *
     * Note: When registering multiple callbacks they will be processed
     * in the given order, so the first match will be processed. The
     * first parameter defines the pattern and is compared like "if it
     * starts with...".
     */
    router->map("/foo/", cb_foo);
    router->map("/bar/", cb_bar);

    /*
     * We also can define an unique callback that will be triggered
     * once a HTTP request requires the root address of the service
     */
    router->root(cb_root);

    /*
     * Return value
     * -------------
     * Returning zero means that this service is ready to run.
     */
    return 0;
}
