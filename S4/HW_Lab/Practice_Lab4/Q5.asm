;count number of spaces in a string

section .data
msg1 : db 'Enter string : '
l1 : equ $-msg1
msg2 : db 'Number of spaces in the string is '
l2 : equ $-msg2
newline : db 10

section .bss
string : resb 50
temp : resb 1
strlen : resb 1
space_count : resb 1

section .text
global _start:     
_start:
	mov eax, 4
	mov ebx, 1 
	mov ecx, msg1
	mov edx, l1 
	int 80h

	mov ebx, string
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
	mov ebx, string

	;initialize space_count to zero
	mov byte[space_count], 0

count_space:
	cmp byte[ebx], 0
	je print
	cmp byte[ebx], 32
	je inc_count
return_pos:
	inc ebx
	jmp count_space

print:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg2 
	mov edx, l2
	int 80h

	add byte[space_count], 30h
	mov eax, 4
	mov ebx, 1
	mov ecx, space_count
	mov edx, 1
	int 80h

	mov eax, 4
	mov ebx, 1
	mov ecx, newline
	mov edx, 1
	int 80h

exit:
	mov eax, 1
	mov ebx, 0
	int 80h

inc_count:
	inc byte[space_count]
	jmp return_pos
	
