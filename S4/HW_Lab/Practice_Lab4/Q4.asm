;compare two strings

section .data
msg1 : db 'Enter string 1 : '
l1 : equ $-msg1
msg2 : db 'Enter string 2 : '
l2 : equ $-msg2
msg_less : db 'String 1 < String 2', 10
l_less : equ $-msg_less
msg_more : db 'String 1 > String 2', 10
l_more : equ $-msg_more
msg_equ : db 'String 1 = String 2', 10
l_equ : equ $-msg_equ

section .bss
string1 : resb 50
string2 : resb 50
temp : resb 1
strlen : resb 1
strlen1 : resb 1
strlen2 : resb 1
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
	
	;store strlen in strlen2
	mov al, byte[strlen]
	mov byte[strlen2], al
	
	mov ebx, string1
	mov ecx, string2

compare:
    ;check for end of string1
    cmp byte[ebx], 0
    je string1_end
    
    ;check for end of string2
    cmp byte[ecx], 0
    je greater_than
    
    inc ebx
    inc ecx
    mov al, byte[ebx - 1]
    cmp al, byte[ecx - 1]
    ;inc ebx
    ;inc ecx
    je compare
    jb less_than
    ja greater_than
    
string1_end:
    cmp byte[ecx], 0
    je equal
    jmp less_than
    
less_than:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_less
    mov edx, l_less
    int 80h
    jmp exit
    
greater_than:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_more
    mov edx, l_more
    int 80h
    jmp exit
    
equal:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_equ
    mov edx, l_equ
    int 80h
    jmp exit
    
exit:
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
	
