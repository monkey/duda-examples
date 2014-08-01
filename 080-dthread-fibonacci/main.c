#include "webservice.h"

DUDA_REGISTER("Dthread Fibonacci Examples", "dthread fibonacci demo");

struct bundle {
    duda_dthread_channel_t *chan;
    duda_request_t *dr;
};

void consumer(void *data)
{
    struct bundle *bdl = data;
    duda_dthread_channel_t *chan = bdl->chan;
    duda_request_t *dr = bdl->dr;
    response->http_status(dr, 200);
    while (!dthread->chan_done(chan)) {
        int *n = dthread->chan_recv(chan);
        response->printf(dr, "%d\n", *n);
        monkey->mem_free(n);
    }
    response->end(dr, NULL);
}

void productor(void *data)
{
    duda_dthread_channel_t *chan = data;
    int num1 = 1;
    int num2 = 1;
    int i;
    for (i = 0; i < 20; ++i) {
        int *n = monkey->mem_alloc(sizeof(int));
        if (i == 0) {
            *n = num1;
        } else if (i == 1) {
            *n = num2;
        } else {
            *n = num1 + num2;
            num1 = num2;
            num2 = *n;
        }
        dthread->chan_send(chan, n);
    }
    dthread->chan_end(chan);
}

void cb_fibonacci(duda_request_t *dr)
{
    // unbuffered channel
    duda_dthread_channel_t *chan = dthread->chan_create(0, monkey->mem_free);
    struct bundle *bdl = monkey->mem_alloc(sizeof(*bdl));
    bdl->chan = chan;
    bdl->dr = dr;
    int cid = dthread->create(consumer, bdl);
    int pid = dthread->create(productor, chan);
    dthread->chan_set_sender(chan, pid);
    dthread->chan_set_receiver(chan, cid);
    dthread->resume(cid);
    dthread->chan_free(chan);
    monkey->mem_free(bdl);
}

int duda_main()
{
    map->static_add("/", "cb_fibonacci");
    return 0;
}
