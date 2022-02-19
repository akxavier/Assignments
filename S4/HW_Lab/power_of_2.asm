;find how many times a 2-digit number is divisible by 2

section .data
msg1 : db 'Enter a 2-digit number : '
l1 : equ $-msg1
msg2 : db 'Power of 2 in the given number is : '
l2 : equ $-msg2
newline : db 10

section .bss
d1 : resb 1
d2 : resb 1
num : resb 1
count : resb 1
junk : resb 1

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
    mov edx, 1
    int 80h
    
    mov eax, 3
    mov ebx, 0
    mov ecx, junk
    mov edx, 1
    int 80h
    
    sub byte[d1], 30h
    sub byte[d2], 30h
    
    ;calculate 2-digit number
    mov ah, 0
    mov al, byte[d1]
    mov bl, 10
    mul bl
    add al, byte[d2]
    mov byte[num], al
    
    ;initialize count to zero
    mov byte[count], 0
    
    
    while:
        cmp byte[num], 0
        je print
        mov al, byte[num]
        mov ah, 0
        mov bl, 2
        div bl
        cmp ah, 0
        jne print
        inc byte[count]
        mov byte[num], al
        jmp while
        
    print:
        add byte[count], 30h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, msg2
        mov edx, l2
        int 80h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, count
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
        
