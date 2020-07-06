    .386
    .model flat, stdcall
    option casemap :none

	include ..\include\windows.inc
    include ..\include\kernel32.inc
    includelib ..\lib\kernel32.lib

.const
	MsgStart db "Enter your sentense", 10, 13
	MsgExit db 10, 13, "Press Enter for exit", 10, 13
	VOWELS db "aeuioy"
	VOWELS_SIZE dd 6
	SPACE db " ", 10, 13
.data
	hConsoleIn dd ?
	hConsoleOut dd ?
	
	NumberOfCharsRead dd ?		
	NumberOfCharsWritten dd ?

	Buffer db 250 dup (0)
	Result db 250 dup (0)
	ResultLen dd 0
	LastPosition dd 0

	OneWord db 8 dup (?)
	OneWordLen dd ?
	
	MaxVoewls dd 0
	
	SymbolsLeft dd 0
.code

initialize proc near 
	invoke AllocConsole

	invoke GetStdHandle, STD_INPUT_HANDLE
	mov hConsoleIn, EAX	

	invoke GetStdHandle, STD_OUTPUT_HANDLE
	mov hConsoleOut, EAX

	ret
initialize endp

preparations proc near 
	MOV EBX, LastPosition ; Позиция, на которой мы остановились
	MOV ECX, NumberOfCharsRead ; Длина строки
	SUB ECX, EBX 

	MOV OneWordLen, ECX 

	lea EDI, [Buffer + EBX] ; Будем читать с этого места
	MOV AL, ' ' ; Заносим символ, для команд repne SCASB/repe SCASB
	ret
preparations endp

findWordLenAndChangePosition proc near
	SUB OneWordLen, ECX
	DEC OneWordLen
	MOV ECX, OneWordLen ; Находим длину одного слова и кладем ее в ECX
	ADD LastPosition, ECX ; Смещаем текущую позицию
	ret
findWordLenAndChangePosition endp

findWord proc near
	PUSH ECX
	PUSH EBX
	
	call preparations
	repne SCASB ;Повторяется, пока не найдет символ из AL(пробел мы туда положили ранее). Каждый раз уменьшает ECX на 1
	MOV SymbolsLeft, ECX 
	call findWordLenAndChangePosition
	INC LastPosition

	lea ESI, [Buffer + EBX]
	lea EDI, OneWord

	MOV ECX, OneWordLen
	rep MOVSB ; Копируем слово посимвольно, согласно кол-ву символов в ECX. Декрементирует ECX
	PUSH OneWordLen

	call preparations
	repe SCASB ; Находим и обрезаем лишние пробелы между найденым словом и новым словом. Идет, пока не найдет первый символ, не такой как в AL
	call findWordLenAndChangePosition

	POP OneWordLen
	POP EBX
	POP ECX
	; Таким образом, после этой команды у нас слово записано в OneWord, а текущая позиция - на первом символе нового слова.
	ret
findWord endp

checkLetter proc near ; Проверяет, находится ли в константной строке с гласными тот символ, который мы сейчас рассматриваем
	PUSH ECX

	MOV ECX, VOWELS_SIZE
	lea EDI, VOWELS
	repne SCASB   ;Ищет в строке гласных то, что в AL
	
	POP ECX
	ret
checkLetter endp

clearResult proc near
	PUSH EAX
	PUSH ECX
	
	lea EDI, Result
	MOV ECX, ResultLen
	MOV AL, ' '
	rep STOSB
	MOV ResultLen, 0
	
	POP ECX
	POP EAX
	ret
clearResult endp

addToResult proc near ; Посимвольно добвляет слово в результирующую строку
	PUSH EBX
	PUSH ECX

	MOV ECX, OneWordLen
	lea ESI, OneWord
	MOV EBX, ResultLen
	lea EDI, [Result + EBX]
	ADD ResultLen, ECX
	rep MOVSB 
	MOV ECX, ResultLen
	MOV [Result + ECX], ' '
	INC ResultLen
	
	POP ECX
	POP EBX
	ret
addToResult endp

checkWord proc near
	PUSH ECX 
	PUSH EBX
	PUSH EAX

	XOR EBX, EBX
	XOR ESI, ESI
	MOV ECX, OneWordLen

	@LOOP: ; Проходим по слову и считаем гласные
	MOV AL, OneWord[ESI] ;При каждом проходе смотрим на 1 символ
	call checkLetter ;Подробнее возле нее
	jne @next_letter ; Проверяет, если мы не нашли символ в строке с гласными
	inc EBX ; Если нашли - увеличиваем счетчик гласных
	@next_letter:
	inc ESI ; Переходим на след. букву
	LOOP @LOOP
	
	CMP EBX, MaxVoewls  ; Сравниваем с максимальным колличеством гласных, найденным ранее
	jl @smaller ;Если меньше - пропускаем это слово
	je @equal ;Если равно - дописываем в результирующую строку
	call clearResult ;Если больше - чистим результирующую строку, потом запишем его в нее
	MOV MaxVoewls, EBX
	@equal:
	call addToResult ;Пишем слово в результирующую строку
	@smaller:
	
	POP EAX
	POP EBX
	POP ECX
	ret
checkWord endp

addSpace proc near 
	lea ESI, SPACE
	MOV EAX, NumberOfCharsRead
	DEC NumberOfCharsRead
	SUB EAX, 2
	lea EDI, [Buffer + EAX]
	MOV ECX, 3
	rep MOVSB
	ret
addSpace endp

start:
	
	call initialize
	
	invoke WriteConsoleA, hConsoleOut, ADDR MsgStart, SIZEOF MsgStart, ADDR NumberOfCharsWritten, 0 ;Выводим стартовое сообщение
	
	invoke ReadConsoleA, hConsoleIn, ADDR Buffer, 250, ADDR NumberOfCharsRead, 0 ;Читаем строку
	
	call addSpace ; Добавляем к концу строки один пробел, чтоб было удобно по нему найти последнее слово
	
	MOV ECX, NumberOfCharsRead ;Запоминаем длину строки
	dec ECX ;Убираем Энтер в конце
	
	@mainLoop:
	call findWord ; Функция находит слово и помещает его в переменную OneWord. Детальнее в комментариях возле нее
	call checkWord ; Проверяем слово на кол-во гласных. Детальнее в комментариях возле нее
	CMP ECX, LastPosition ; Не конец ли строки. Если да - закончим основной цикл
	jg @mainLoop
	

	;Выводим результат
	invoke WriteConsoleA, hConsoleOut, ADDR Result, SIZEOF Result, ADDR NumberOfCharsWritten, 0
	;Exit
	invoke WriteConsoleA, hConsoleOut, ADDR MsgExit, SIZEOF MsgExit, ADDR NumberOfCharsWritten, 0
	invoke ReadConsoleA, hConsoleIn, ADDR Buffer, 1, ADDR NumberOfCharsRead, 0
	invoke ExitProcess, 0
	
end start