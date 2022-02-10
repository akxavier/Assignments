;Minor evaluation 1

section .data
msg1 : db 'Enter first number : '
l1 : equ $-msg1
msg2 : db 'Enter second number : '
l2 : equ $-msg2
msg3 : db 'Sum = '
l3 : equ $-msg3
msg4 : db 'Result = '
l4 : equ $-msg4
newline : db 10

section .bss
d1 : resb 1
d2 : resb 1
sum : resb 1
sum1 : resb 1
sum2 : resb 1
result : resb 1
result1 : resb 1
result2 : resb 1

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
    mov edx, 2
    int 80h
    
    ;mov eax, 3
    ;mov ebx, 0
    ;mov ecx, junk
    ;mov edx, 1
    ;int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, l2
    int 80h
    
    mov eax, 3
    mov ebx, 0
    mov ecx, d2
    mov edx, 2
    int 80h
    
    sub byte[d1], 30h
    sub byte[d2], 30h
    
    summing:
        mov al, byte[d1]
        mov bl, 0
        add al, 1
        
        for:
            add bl, al
            add al, 1
            cmp al, byte[d2]
            jb for
            
        mov byte[sum], bl
        mov ax, word[sum]
        mov bl, 10
        mov ah, 0
        div bl
        mov byte[sum1], al
        mov byte[sum2], ah
        
        add byte[sum1], 30h
        add byte[sum2], 30h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, msg3
        mov edx, l3
        int 80h
    
        mov eax, 4
        mov ebx, 1
        mov ecx, sum1
        mov edx, 1
        int 80h

        mov eax, 4
        mov ebx, 1
        mov ecx, sum2
        mov edx, 1
        int 80h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, newline
        mov edx, 1
        int 80h


        
    division:
        mov ax, word[sum]
        mov ah, 0
        mov bl, 3
        div bl
        mov byte[result], al
        
           
        mov ax, word[result]
        mov bl, 10
        mov ah, 0
        div bl
        mov byte[result1], al
        mov byte[result2], ah
        
        add byte[result1], 30h
        add byte[result2], 30h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, msg4
        mov edx, l4
        int 80h
    
        mov eax, 4
        mov ebx, 1
        mov ecx, result1
        mov edx, 1
        int 80h

        mov eax, 4
        mov ebx, 1
        mov ecx, result2
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
