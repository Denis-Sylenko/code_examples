.model flat

.data
	p1 db 1 
	p2 dw ?

.code
main proc
   MOV AL, 'a'
   MOV p1, 'h'
   MOV BX, DS
   LEA EBX, p1
   MOV AH, [EBX]
   MOV CX, p2
   ;MOV ES, p1
   main endp
end main