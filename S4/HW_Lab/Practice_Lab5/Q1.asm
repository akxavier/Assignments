;interchange 1st and nth words, 2nd and n-1th words and so on

section .data
msg1 : db 'Enter string : '
l1 : equ $-msg1
msg2 : db 'Modified string is : '
l2 : equ $-msg2
newline : db 10

section .bss
string1 : resb 100
string2 : resb 100
strlen : resb 1
strlen1 : resb 1
temp : resb 1
temp_addr : resd 1

section .text
global _start
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
	
	;modifying the string begins here
	mov ebx, string1
	movzx edx, byte[strlen1]
	add ebx, edx
	sub ebx, 1
	
	mov ecx, string2
	
find_space:
    cmp ebx, string1
    jb store_addr
    cmp byte[ebx], 32
    je store_addr
    dec ebx
    jmp find_space
    
store_addr:
    mov dword[temp_addr], ebx
    jmp insert_word
    
insert_word:
    inc ebx
    cmp byte[ebx], 0
    je insert_space
    cmp byte[ebx], 32
    je insert_space
    mov al, byte[ebx]
    mov byte[ecx], al
    inc ecx
    jmp insert_word
    
insert_space:
    cmp dword[temp_addr], string1
    jb end_write
    mov byte[ecx], 32
    inc ecx
    mov ebx, dword[temp_addr]
    dec ebx
    jmp find_space
    
end_write:
    mov byte[ecx], 0
    
    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, l2
    int 80h
    
print:
    mov ecx, string2
    
print_loop:
    cmp byte[ecx], 0
    je end_print
    
    mov al, byte[ecx]
    mov byte[temp], al
    
    push ecx
    
    mov eax, 4
    mov ebx, 1
    mov ecx, temp
    mov edx, 1
    int 80h
    
    pop ecx
    inc ecx
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
