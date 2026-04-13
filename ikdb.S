    xref _input_ikbd_handler
    xdef _input_ikbd_isr

_input_ikbd_isr:
        movem.l d0-d7/a0-a6,-(sp)
        jsr _input_ikbd_handler
        movem.l (sp)+,d0-d7/a0-a6
        rte