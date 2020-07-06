.model flat

.data
	a dw 15, 6, 5,11, 8, 7, 10, 32, 14, 21, 43,  1, 6, 3, 9, 4, 19, 8, 4, 7
    k db 2,  3, 5, 1, 6, 7,  3,  0, 5,  2,   0, 10, 9, 8, 7, 4,  2, 3, 2, 2
.code
main proc
	
	lea ebx, a
	lea edi, k

	mov ecx, 20

	mark:
	mov ax, [ebx]
	    push cx
		sub ecx, ecx
		mov cl, [edi]
		dec cl
		cmp cl, -1
		je ifzero
		mark2: 
		imul ax, [ebx]
		loop mark2
	
	aftercompare:
	mov [ebx], ax
	add ebx, 2
	inc edi
	pop cx
	loop mark

	ifzero:
	mov ax, 1
	jmp aftercompare

  main endp
end main