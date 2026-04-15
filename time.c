#include "time.h"
#include "vbl.h"

UINT32 get_time() {
    return vbl_get_ticks();
}

void wait_vbl(UINT32 old_time) {
    while (get_time() == old_time) {
        /*waiting*/
    }
}
