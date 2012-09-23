/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include "webservice.h"
#include "packages/websocket/websocket.h"

DUDA_REGISTER("Websockets Service Example", "service");

void cb_on_message(duda_request_t *dr, ws_request_t *wr)
{
    websocket->broadcast(wr, wr->payload, wr->payload_len, WS_OPCODE_TEXT);
}

void cb_on_close(duda_request_t *dr, struct ws_request *wr)
{
    printf("on close!!!!!!!!!!\n");
}

void cb_handshake(duda_request_t *dr)
{
    websocket->handshake(dr);
}

void cb_hola(duda_request_t *dr)
{
    printf("asdasd\n");
}

int duda_main()
{
    duda_interface_t *if_system;
    duda_method_t    *method;

    duda_load_package(websocket, "websocket");
    websocket->set_callback(WS_ON_MESSAGE, cb_on_message);
    websocket->set_callback(WS_ON_CLOSE, cb_on_close);


    map->static_add("/hola", "cb_hola");


    /* archive interface */
    if_system = map->interface_new("example");

    /* URI: /websockets/example/handshake  */
    method = map->method_new("handshake", "cb_handshake", 0);
    map->interface_add_method(method, if_system);

    /* Add interface to map */
    map->add_interface(if_system);
    //duda_service_add_interface(if_system);

    /* Initialize the broadcast interface */
    websocket->broadcaster();

    return 0;
}
