#include "time.h"

UINT32 get_time() {
    long *timer;
    long old_ssp;
    UINT32 time;
    timer = (long*)0x462;
    old_ssp = Super(0);   /* enter privileged mode */
    time = *timer;
    Super(old_ssp);       /* exit privileged mode */

    return time;
}

void wait_vbl(UINT32 old_time) {
    while (get_time() == old_time) {
        /* busy wait */
    }
}
