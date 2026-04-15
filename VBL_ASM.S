	xdef	_vbl_isr
	xref	_vbl_tick

_vbl_isr:
	movem.l	d0-d7/a0-a6,-(sp)
	jsr	_vbl_tick
	movem.l	(sp)+,d0-d7/a0-a6
	rte
