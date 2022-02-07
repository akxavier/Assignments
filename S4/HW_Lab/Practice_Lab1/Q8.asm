;print whether a number is odd or even

section .data
msg1 : db 'Enter number : '
l1 : equ $-msg1
ans1 : db 'Odd', 10
l2 : equ $-ans1
ans2 : db 'Even', 10
l3 : equ $-ans2

section .bss
d1 : resb 1

section .text
global _start:
_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, l1
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, d1
	mov edx, 1
	int 80h

	sub byte[d1], 30h
	mov ax, word[d1]
	;mov ah, 0
	mov bl, 2
	div bl

	cmp ah, 0
	je if

	else:
		mov eax, 4
		mov ebx, 1
		mov ecx, ans1
		mov edx, l2
		int 80h

		mov eax, 1
		mov ebx, 0
		int 80h

	if:
		mov eax, 4
		mov ebx, 1
		mov ecx, ans2
		mov edx, l3
		int 80h

		mov eax, 1
		mov ebx, 0
		int 80h
