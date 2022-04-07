;Write a program to remove all the repeated characters of each word in a given string

;Sample Test Case:
;INPUT: programming loop functions
;OUTPUT: progamin lop functions

section .data
msg1 : db 'Enter string : '
l1 : equ $-msg1
msg2 : db 'Modified string is : '
l2 : equ $-msg2
newline : db 10

section .bss
string : resb 100
char : resb 1
word_addr : resd 1

section .text
global _start
_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, l1
	int 80h

read_string:
	mov ebx, string

read_loop:
	push ebx

	mov eax, 3
	mov ebx, 0
	mov ecx, char
	mov edx, 1
	int 80h

	pop ebx

	cmp byte[char], 10
	je end_read
	mov al, byte[char]
	mov byte[ebx], al
	inc ebx
	jmp read_loop

end_read:
	mov byte[ebx], 0

	;print message 2
	mov eax, 4
	mov ebx, 1
	mov ecx, msg2
	mov edx, l2
	int 80h

	mov ebx, string
	dec ebx

next_char:
	inc ebx
	cmp byte[ebx], 32
	je print_char
	cmp byte[ebx], 0
	je exit
	mov al, byte[ebx]
	mov ecx, ebx
	dec ecx

check_loop:
	cmp byte[ecx], 32
	je print_char
	cmp ecx, string
	jb print_char
	cmp al, byte[ecx]
	je next_char
	dec ecx
	jmp check_loop

print_char:
	mov al, byte[ebx]
	mov byte[char], al

	push ebx

	mov eax, 4
	mov ebx, 1
	mov ecx, char
	mov edx, 1
	int 80h

	pop ebx

	jmp next_char

exit:
	mov eax, 4
	mov ebx, 1
	mov ecx, newline
	mov edx, 1
	int 80h

	mov eax, 1
	mov ebx, 0
	int 80h
