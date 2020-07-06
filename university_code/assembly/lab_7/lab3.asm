    ;Силенко Денис, ПЗ-18-1
	;Варіант 13
    
	;Описать внешнюю процедуру, упорядочивающую по не убыванию числа
	;массива X (каждый элемент – символьная строка длины n) следующим методом.
	;Все числа из X упорядочить по последней цифре и перенести во
	;вспомогательный массив Y; затем числа из Y упорядочить по предпоследней
	;цифре (при равенстве этих цифр сохранить упорядоченность по последней
	;цифре) и записать их в массив X; и т.д. В конце числа должны оказаться в
	;массиве X. В основной программе предусмотреть ввод n, числовую
	;последовательность и вывод результата.
	
	; Я трохи змінив умову й використав сортуваннябульбашкою, замість сортування за разрядами
	
	
    .386
    .model flat, stdcall
    option casemap :none
	extern BubbleSort@0: near
	

	include ..\include\windows.inc
	include ..\include\masm32.inc
	include ..\include\user32.inc
    include ..\include\kernel32.inc
    includelib ..\lib\kernel32.lib
	includelib ..\lib\masm32.lib
	includelib ..\lib\user32.lib
	
.const
	MsgStart db "Enter array size", 10, 13
	MsgStart2 db "Enter array", 10, 13
	MsgExit db 10, 13, "Press Enter for exit", 10, 13
.data
	hConsoleIn dd ?
	hConsoleOut dd ?
		
	element_length db ?
	NumberOfCharsWritten dd ?
	NumberOfCharsRead dd ?
	
	elements_count dd ? ; Кількість елементів массиву
	separator db " " ; для виводу масиву
	numbers_array dd 250 dup (0) ; масив чисел, в який переведемо введену користувачем строку
	Buffer dd 250 dup (0) ; Сюди будемо читати речення користувача
	TmpBuffer dd 10 dup (0) ; буфер для виведення массиву
.code


initialize proc near 
	invoke AllocConsole

	invoke GetStdHandle, STD_INPUT_HANDLE
	mov hConsoleIn, EAX	

	invoke GetStdHandle, STD_OUTPUT_HANDLE
	mov hConsoleOut, EAX

	ret
initialize endp


; [ebp+8] - кількість елементів масиву
; [ebp+12] - початок речення, яке будемо переводити в масив чисел

stringToNumberArray proc ; процедура, що переводить строку в масив чисел
	; Пролог
	push ebp
	mov ebp, esp
	
	
	push eax
    push ebx
	push ecx
	push edx
	push esi
	
	
	mov edi, 0
	mov ecx, [ebp+8] ; записуємо в ecx кількість елементів масиву
	mov esi, [ebp+12] ; записуємо в esi адрес на початок речення, якке будемо переводити в масив чисел
    xor eax, eax
	
	@LOOP:
    mov ebx, [esi]
    sub bl, '0'
    cmp bl, 10 ; якщо в bl цифра - продовжуємо читати число. Якщо вже ні, то переходмо на наступну ітерацію
    jnb @NEXT
    imul eax, 10
    add al, bl
    inc esi
    jmp @LOOP
 
	@NEXT:
	mov numbers_array[edi], eax ; записуємо прочитане число в масив чисел
    xor eax, eax
	add edi, 4  ; переходимо на наступний елемент в масиві чисел
	dec ecx
	add esi, 1 ;пропускаємо пробіл в строці
	cmp ecx, 0 ; якщо усі числа прочитані - закінчуємо процедуру
	jne @LOOP
	
	pop esi
	pop edx
	pop ecx
	pop ebx
	pop eax
	
	; Епілог
	mov esp, ebp
	pop ebp
    ret
stringToNumberArray endp


; [ebp+8] - кількість елементів масиву

PrintArray proc ; процедура виводить масив чисел на екран
	; Пролог
	push ebp
	mov ebp, esp
	
    push eax
    push ebx
	push ecx
	push edx
	
	mov edi, 0
	mov ecx, [ebp+8] ; записуємо в ecx кількість елементів масиву
	@LOOP:
	push ecx
	mov eax, numbers_array[edi] ; записуємо число з масиву чисел в eax
	invoke dwtoa, eax, ADDR TmpBuffer ; переводимо його в строку та записуємо в тимчасовий буфер
	invoke StdOut, offset TmpBuffer ; виводимо тимчасовий буфер
	invoke WriteConsoleA, hConsoleOut, ADDR separator,1, ADDR NumberOfCharsWritten, 0 ; виводимо пробіл (роздільник)
	add edi, 4 ; переходимо на наступне число в масиві
	pop ecx
	dec ecx
    cmp ecx, 0 ; якщо усі числа виведені - закінчуємо процедуру
	jne @LOOP
 
	pop edx
	pop ecx
	pop ebx
	pop eax
	
	; Епілог
	mov esp, ebp
	pop ebp
    ret
PrintArray endp

start:
	
	call initialize
	invoke WriteConsoleA, hConsoleOut, ADDR MsgStart, SIZEOF MsgStart, ADDR NumberOfCharsWritten, 0 ;Виводимо стартове повідомлення
	invoke ReadConsoleA, hConsoleIn, ADDR element_length, 4, ADDR NumberOfCharsRead, 0 ;Читаемо кількість елементів масиву
	invoke WriteConsoleA, hConsoleOut, ADDR MsgStart2, SIZEOF MsgStart2, ADDR NumberOfCharsWritten, 0 ;Виводимо стартове повідомлення 2
	invoke ReadConsoleA, hConsoleIn, ADDR Buffer, 250, ADDR NumberOfCharsRead, 0 ;Читаемо строку

	;наступний блок коду переводить строку, що відпоівдає кількості елементів, яку ввів користувач, в число; Воно записується в elements_count
	lea eax, element_length
	push eax
	push 1
	invoke stringToNumberArray
	add esp, 8
	mov eax, numbers_array[0]
	mov elements_count, eax
	;-------------------------------------------------------
	
	;наступний блок коду переводить строку, що відпоівдає масиву елементів, яку ввів користувач, в масив чисел; Він записується в numbers_array
	lea eax, Buffer
	push eax
	push elements_count
	invoke stringToNumberArray
	add esp, 8
	;-------------------------------------------------------
	
	;наступний блок коду викликає зовнішню процедуру сортування BubbleSort@0. Після цього масив numbers_array відсортован по зростанню
	lea ebx, numbers_array
	push ebx
	push elements_count
	call BubbleSort@0
	;-------------------------------------------------------
	
	;Виводимо масив на екран
	invoke PrintArray
	add esp, 8
	
	;Завершення програми
	invoke WriteConsoleA, hConsoleOut, ADDR MsgExit, SIZEOF MsgExit, ADDR NumberOfCharsWritten, 0
	invoke ReadConsoleA, hConsoleIn, ADDR Buffer, 1, ADDR NumberOfCharsRead, 0
	invoke ExitProcess, 0
	
end start