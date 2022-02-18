;print no. of even and odd numbers in an array

section .data
msg1 : db 'Enter length of array : '
l1 : equ $-msg1
msg2 : db 'Enter array element : '
l2 : equ $-msg2
msg_even : db 'No. of even numbers in the array : '
l_even : equ $-msg_even
msg_odd : db 'No. of odd numbers in the array : '
l_odd : equ $-msg_odd
newline : db 10

section .bss
array : resb 50
even_count : resb 1
odd_count : resb 1
d1 : resb 1
d2 : resb 1
n : resb 1
junk : resb 1
temp : resb 1

section .text
global _start:
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, l1
    int 80h
    
    ;read array size
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
    
    mov al, byte[d1]
    mov bl, 10
    mul bl
    mov bx, word[d2]
    add ax, bx
    mov byte[n], al

    mov byte[temp], al
    mov ebx, array
        
    reading:
        push ebx    ;push address of array in stack
        
        ;read array element
        mov eax, 4
        mov ebx, 1
        mov ecx, msg2
        mov edx, l2
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
        mov al, byte[d1]
        mov ah, 0
        mov bl, 10
        mul bl
        add al, byte[d2]
        ;al now contains array element
        
        pop ebx
        mov byte[ebx], al
        add ebx, 1
        
        dec byte[temp]
        cmp byte[temp], 0
        jg reading
        
    mov al, byte[n]
    ;temp stores no of iterations left
    mov byte[temp], al
    
    ;initialize odd and even count to zero
    mov byte[even_count], 0
    mov byte[odd_count], 0
    
    ;store array starting address in ebx
    mov ebx, array
        
    counting:
        mov al, byte[ebx]
        mov ah, 0
        mov dl, 2
        div dl
        cmp ah, 0
        je even
        jmp odd
        ret_pos:
        add ebx, 1
        dec byte[temp]
        cmp byte[temp], 0
        ja counting
        
        
    ;print even count
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_even
    mov edx, l_even
    int 80h
    
    add byte[even_count], 30h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, even_count
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ;print odd count
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_odd
    mov edx, l_odd
    int 80h
    
    add byte[odd_count], 30h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, odd_count
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ;exit
    mov eax, 1
    mov ebx, 0
    int 80h
    
    
    ;even count
    even:
        add byte[even_count], 1
        jmp ret_pos
        
    ;odd count
    odd:
        add byte[odd_count], 1
        jmp ret_pos

