;check palindrome or not

section .data
msg1 : db 'Enter string : '
l1 : equ $-msg1
msg_pal : db 'The string is a palindrome', 10
l_pal : equ $-msg_pal
msg_notpal : db 'The string is not a palindrome', 10
l_notpal : equ $-msg_notpal

section .bss
str_len : resb 1
string : resb 50
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
    
check_palindrome:
    mov cl, byte[ebx + eax]
    mov ch, byte[ebx + edx]
    cmp cl, ch
    jne not_palindrome
    inc eax
    dec edx
    cmp eax, edx
    jnb palindrome
    jmp check_palindrome
    
palindrome:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_pal
    mov edx, l_pal
    int 80h
    
    mov eax, 1
    mov ebx, 0
    int 80h
    
not_palindrome:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_notpal
    mov edx, l_notpal
    int 80h
    
    mov eax, 1
    mov ebx, 0
    int 80h
    
