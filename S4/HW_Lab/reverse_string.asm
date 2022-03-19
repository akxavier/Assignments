;reverse a string

section .data
msg1 : db 'Enter string : '
l1 : equ $-msg1
msg2 : db 'Reversed string is : '
l2 : equ $-msg2
newline : db 10

section .bss
string : resb 50
str_len : resb 1
temp : resb 1

section .text
global _start:
_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, l1
	int 80h

	mov ebx, string
	mov byte[str_len], 0

reading:
	push ebx

	mov eax, 3
	mov ebx, 0
	mov ecx, temp
	mov edx, 1
	int 80h

	pop ebx

	cmp byte[temp], 10
	je end_reading
	inc byte[str_len]
	mov al, byte[temp]
	mov byte[ebx], al
	inc ebx
	jmp reading

end_reading:
	mov byte[ebx], 0
	mov ebx, string

	mov eax, 0
	movzx edx, byte[str_len]
	dec edx

reverse:
	mov ch, byte[ebx + eax]
	mov cl, byte[ebx + edx]
	mov byte[ebx + eax], cl
	mov byte[ebx + edx], ch

	cmp eax, edx
	jnb print
	inc eax
	dec edx
	jmp reverse

print:
	mov ebx, string

print_loop:
	cmp byte[ebx], 0
	je end_print

	;assign temp the char in ebx
	mov al, byte[ebx]
	mov byte[temp], al

	push ebx

	mov eax, 4
	mov ebx, 1
	mov ecx, temp
	mov edx, 1
	int 80h

	pop ebx
	inc ebx
	jmp print_loop

end_print:
	mov eax, 4
	mov ebx, 1
	mov ecx, newline
	mov edx, 1
	int 80h

	mov eax, 1
	mov ebx, 0
	int 80h




