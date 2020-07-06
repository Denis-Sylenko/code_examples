.model flat

.data
	a db 5
	x dw 4
	y dw 6
	r dw 6
.code
main proc
	
	mov cx, x
    imul cx, cx
	mov bx, y
    imul bx, bx
	add cx, bx
	mov bx, r
	imul bx, bx
	cmp cx, bx
	jl less
	je equal
	jg greater

	less:
	mov al, a
	cmp a, 0
	cbw
	mov cl, 2
	cwd
	idiv cl
	cbw
	mov y, ax
	jmp endmark

	invertbx:
	neg bx
	jmp greaternext

	equal:
	mov al, a
	neg al
	cbw
	mov y, ax
	jmp endmark

	greater:
	mov al, a
	cbw
	imul ax, 7
	mov bx, x
	sub bx, y
	cmp bx, 0
	jl invertbx 

	greaternext:
	cwd
	idiv bx
	mov y, dx

 endmark:
  main endp
end main