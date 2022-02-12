;Read two integers and print whether the first is a multiple of the second

section .data
msg1 : db 'Enter first 2-digit number : '
l1 : equ $-msg1
msg2 : db 'Enter second 2-digit number : '
l2 : equ $-msg2
msg3 : db 'First integer is a multiple of second', 0ah
l3 : equ $-msg3
msg4 : db 'First integer is not a multiple of second', 0ah
l4 : equ $-msg4

section .bss
d1 : resb 1
d2 : resb 1
d3 : resb 1
d4 : resb 1
num1 : resw 1
num2 : resw 1

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
    
    mov eax, 3
    mov ebx, 0
    mov ecx, d2
    mov edx, 2
    int 80h
    
    ;Calculate first number
    sub byte[d1], 30h
    sub byte[d2], 30h
    mov al, byte[d1]
    mov bl, 10
    mul bl
    mov bx, word[d2]
    add ax, bx
    mov word[num1], ax
    
    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, l2
    int 80h
    
    mov eax, 3
    mov ebx, 0
    mov ecx, d3
    mov edx, 1
    int 80h
    
    mov eax, 3
    mov ebx, 0
    mov ecx, d4
    mov edx, 2
    int 80h
    
    ;Calculate second number
    sub byte[d3], 30h
    sub byte[d4], 30h
    mov al, byte[d3]
    mov bl, 10
    mul bl
    mov bx, word[d4]
    add ax, bx
    
    ;Dividing
    mov word[num2], ax
    mov bl, byte[num2]
    mov ax, word[num1]
    mov ah, 0
    div bl
    cmp ah, 0
    je multiple
    
    notmultiple:
        mov eax, 4
        mov ebx, 1
        mov ecx, msg4
        mov edx, l4
        int 80h
        
        jmp end
        
    multiple:
        mov eax, 4
        mov ebx, 1
        mov ecx, msg3
        mov edx, l3
        int 80h
        
    end:
        mov eax, 1
        mov ebx, 0
        int 80h
        
    
