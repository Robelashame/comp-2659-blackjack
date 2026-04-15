#ifndef VBL_H
#define VBL_H

#include "TYPES.H"

/* Installs the custom VBL ISR and resets its state. */
void vbl_init(void);

/* Restores the previous VBL ISR. */
void vbl_shutdown(void);

/* Called by ISR wrapper once per VBL. */
void vbl_tick(void);

/* Returns 1 if a render was requested since last consume; clears the request. */
int vbl_consume_render_request(void);

/* Returns number of VBL ticks seen since vbl_init(). */
UINT32 vbl_get_ticks(void);

#endif
