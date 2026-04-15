	xdef	_set_video_base



; set_video_base, replaces set screen

BASE	equ	8

_set_video_base:
	link	a6,#0
	movem.l	d0-d2/a0-a2,-(sp)
	move.l	BASE(a6),d0
	lsr.l #8,d0
	lea	$FF8201,a0
	movep.w d0,0(a0)
	movem.l	(sp)+,d0-d2/a0-a2
	unlk	a6
	
	rts