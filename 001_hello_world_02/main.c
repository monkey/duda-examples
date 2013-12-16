/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 * Duda I/O Examples: 001 Hello World 02
 * =====================================
 * Based on the example 001_hello_world, this web service adds a few more
 * callbacks to explain how the Routing maps are processed.
 */

#include "webservice.h"

DUDA_REGISTER("Duda I/O Examples", "Hello World");

/*
 * The apples callback returns some built-in HTML content, check how
 * the HTTP headers are changed also.
 */
void cb_apples(duda_request_t *dr)
{
    response->http_status(dr, 200);

    /*
     * There are two ways basically to set a content type on the
     * response, the first one is to add a specific HTTP header in the
     * response using the http_header() method (without breaklines) and
     * using the http_content_type() method. The last one is preferred as
     * it accepts as input a common resource extension, internally it
     * will lookup the right content type. In the following example given
     * the 'html' parameter it will compose:
     *
     *   Content-Type: text/html
     *
     * if 'jpg' were supplied, it will do:
     *
     *   Content-Type: image/jpeg
     */
    response->http_content_type(dr, "html");

    /*
     * Compose some built-in HTML code to send as response
     */
    response->printf(dr,
                     "<html>\n"
                     "    <head>\n"
                     "      <title>001 Hello World 02: Apples</title>\n"
                     "    </head>\n"
                     "    <body>\n"
                     "        <h1>001 Hello World 02: Apples</h1>\n"
                     "        <p>Apples are apples, you can find them in red,\n"
                     "           green and yellow colors\n"
                     "        </p>\n"
                     "    </body>\n"
                     "</html>\n"
                     );

    /* Finalize */
    response->end(dr, NULL);
}

/*
 * The information callback aims to instruct the stack to print out a
 * text message plus dispatch the content of an existent file from the
 * file system.
 */
void cb_information(duda_request_t *dr)
{
    response->http_status(dr, 200);
    response->printf(dr,
                     "This example returns the Linux LSB release information\n"
                     "that is gathered from file /etc/lsb-release\n\n"
                     "The whole content of the response is sent in non-blocking\n"
                     "mode.\n\n");

    /*
     * The sendfile() method enqueue the given file and prepare the buffers
     * to send it content as additional to any other content already
     * enqueued (such as the previous text message). Once it finish it works
     * it take cares to release any used resource.
     */
    response->sendfile(dr, "/etc/lsb-release");

    /* Finalize */
    response->end(dr, NULL);
}

/*
 * The root callback returns a basic text as response describing the
 * interfaces available.
 */
void cb_root(duda_request_t *dr)
{
    response->http_status(dr, 200);
    response->printf(dr,
                     "Welcome to the root callback, on this example you will\n"
                     "see how different callbacks can be triggered, point your \n"
                     "browser to one of the following URLs:\n\n"
                     "   * http://localhost:2001/hello/apples\n"
                     "   * http://localhost:2001/hello/information\n\n");

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
     * Registering callbacks
     * ---------------------
     * Here we will define three callbacks to match three different
     * type of requests, the goal is to understand how the matching
     * rules works.
     */
    map->static_add("/apples", "cb_apples");
    map->static_add("/information", "cb_information");
    map->static_add("/", "cb_root");

    /* Return, everything is OK */
    return 0;
}
