.model flat

.data
	a db 5
	b db 1
	x dw 4
.code
main proc
   mov cx, x
   mov al, a
   cbw 
   add cx, ax
   mov al, b
   cbw
   imul ax, 3
   inc ax
   mov bx, ax
   mov ax, cx
   cwd
   idiv bx ; ax = (x + a)/(3b+1)
   mov cx, ax
   mov al, a
   cbw
   imul ax, ax
   imul ax, 2
   sub cx, ax ; cx = (x + a)/(3b+1) - 2*a^2
   mov al, b
   cbw
   imul ax, 3
   mov bx, x
   imul bx, bx
   sub bx, 2
   cwd
   idiv bx
   sub cx, ax
   main endp
end main