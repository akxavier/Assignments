;return length of largest "block" in a string

section .data
msg1 : db 'Enter string : '
l1 : equ $-msg1
msg2 : db 'Length of largest block is : '
l2 : equ $-msg2
newline : db 10

section .bss
string : resb 100
strlen : resb 1
temp : resb 1
max : resb 1
count : resb 1
current : resb 1

section .text
global _start
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, l1
    int 80h
    
    mov ebx, string
    call read_string
    
    mov ebx, string
    
    ;initialize max to zero
    mov byte[max], 0
    
;logic begins here
next_block:
    cmp byte[ebx], 0
    je print_result
    mov byte[count], 1
    mov al, byte[ebx]
    mov byte[current], al
    ;al contains current character
next_element:
    inc ebx
    cmp byte[ebx], al
    jne cmp_max
    inc byte[count]
    jmp next_element
cmp_max:
    mov ah, byte[max]
    ;ah contains max count
    cmp byte[count], ah
    ja change_max
    jmp next_block
change_max:
    mov ah, byte[count]
    mov byte[max], ah
    jmp next_block
    
print_result:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, l2
    int 80h
    
    add byte[max], 30h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, max
    mov edx, 1
    int 80h
    
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
