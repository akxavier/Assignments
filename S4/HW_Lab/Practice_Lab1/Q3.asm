; print numbers from 0 to n

section .data
msg1 : db "Enter number between 0 to 9", 0ah
l : equ $-msg1

section .bss
dig1 : resb 1
counter : resb 1

section .text

global _start:
_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, l
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, dig1
	mov edx, 1
	int 80h

	sub byte[dig1], 30h
	mov byte[counter], 0

	for:
		add byte[counter], 30h
		
		mov eax, 4
		mov ebx, 1
		mov ecx, counter
		mov edx, 1
		int 80h

		sub byte[counter], 30h
		add byte[counter], 1
		mov al, byte[counter]
		cmp al, byte[dig1]
		jna for

	mov eax, 1
	mov ebx, 0
	int 80h
