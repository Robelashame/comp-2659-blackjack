    xref _ikbd_handler
    xdef _ikbd_isr

_ikbd_isr:

    movem.l d0-d2/a0,-(sp)

    ; check status register
    move.b  $FFFC00,d0
    andi.b  #1,d0
    beq     exit_isr

    ; read byte
    move.b  $FFFC02,d0

    ; call C handler
    move.b  d0,-(sp)
    jsr     _ikbd_handler
    addq.l  #2,sp

exit_isr:

    ; clear MFP interrupt
    bclr    #6,$FFFA11

    movem.l (sp)+,d0-d2/a0

    rte