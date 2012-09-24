/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include "webservice.h"
#include "packages/websocket/websocket.h"

DUDA_REGISTER("Duda I/O Examples", "WebSocket Chat");

void cb_on_message(duda_request_t *dr, ws_request_t *wr)
{
    websocket->broadcast(wr, wr->payload, wr->payload_len, WS_OPCODE_TEXT);
}

void cb_handshake(duda_request_t *dr)
{
    websocket->handshake(dr);
}

int duda_main()
{
    /* Load the websocket package */
    duda_load_package(websocket, "websocket");

    /*
     * Define a callback, on every websocket message received,
     * trigger cb_on_message.
     */
    websocket->set_callback(WS_ON_MESSAGE, cb_on_message);

    /* Associate a static URL with a callback */
    map->static_add("/handshake/", "cb_handshake");

    /* Initialize the broadcaster interface */
    websocket->broadcaster();

    return 0;
}
