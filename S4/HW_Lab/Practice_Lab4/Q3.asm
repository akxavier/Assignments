;concatenate two strings

section .data
msg1 : db 'Enter string 1 : '
l1 : equ $-msg1
msg2 : db 'Enter string 2 : '
l2 : equ $-msg2
msg3 : db 'Concatenated string is : '
l3 : equ $-msg3
newline : db 10

section .bss
string1 : resb 100
string2 : resb 50
temp : resb 1
strlen : resb 1
strlen1 : resb 1
count : resb 1

section .text
global _start:
_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, l1
	int 80h

	mov ebx, string1
	call read_string
	
	;store strlen in strlen1
	mov al, byte[strlen]
	mov byte[strlen1], al

	mov eax, 4
	mov ebx, 1
	mov ecx, msg2
	mov edx, l2
	int 80h

	mov ebx, string2
	call read_string

concat:
	mov ebx, string1
	movzx ecx, byte[strlen1]
	add ebx, ecx
	;ebx now contains address of string1[strlen1] where string2 needs to be inserted

	mov ecx, string2
	;ecx now contains address of string2

	mov edx, 0
	;edx stores the count of iteration

loop_concat:
	mov al, byte[ecx + edx]
	mov byte[ebx + edx], al
	cmp al, 0
	je print
	inc edx
	jmp loop_concat

print:
	mov ebx, string1

print_loop:
	cmp byte[ebx], 0
	je end_print

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


;function to read string
read_string:
	mov byte[strlen], 0

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
	inc byte[strlen]
	mov al, byte[temp]
	mov byte[ebx], al
	inc ebx
	jmp reading

end_reading:
	mov byte[ebx], 0
	ret