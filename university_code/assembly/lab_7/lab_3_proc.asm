
  .386
.model flat, stdcall
public BubbleSort
  option casemap :none
	include ..\include\windows.inc
	include ..\include\masm32.inc
	include ..\include\user32.inc
    include ..\include\kernel32.inc
    includelib ..\lib\kernel32.lib
	includelib ..\lib\masm32.lib
	includelib ..\lib\user32.lib

.code

; [ebp+8] - кількість елементів масиву
; [ebp+12] - початок масиву чисел, який потрібно відсортувати
BubbleSort proc
	; Пролог
	push ebp
	mov ebp, esp
	
	
	push eax
    push ebx
	push ecx
	push edx
	push esi
	
	mov eax, [ebp+8] ; зберігаємо кількість елементів масиву в eax
	
	@LOOP:
		cmp eax, 1 ; якщо всі елементи відсортовані - виходимо з циклу
		je break
		dec eax
		mov ecx, eax
		mov esi, [ebp+12] ; зберігаємо початок масиву чисел в esi

		inner_loop: ; проходимо по масиву  (з кожною ітерацією не доходимо до елементів в кінці, які вже відсортовані)
			mov ebx, [esi]
			mov edx, [esi+4]
			cmp ebx, edx ;порівнюємо сусідні елементи
			jng already_sorted ; якщо вони не відсортовані - змінюємо їх місцями
			mov [esi+4], ebx
			mov [esi], edx
			already_sorted:
			add esi, 4
		loop inner_loop
		
	jmp @LOOP

	break:

	pop esi
	pop edx
	pop ecx
	pop ebx
	pop eax
	
	; Епілог
	mov esp, ebp
	pop ebp
ret
BubbleSort endp

end