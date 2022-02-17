;find max and min elements in an array

section .data
msg1 : db 'Enter length of array : '
l1 : equ $-msg1
msg2 : db 'Enter array element : '
l2 : equ $-msg2
msg_max : db 'Maximum element : '
l_max : equ $-msg_max
msg_min : db 'Minimum element : '
l_min : equ $-msg_min
newline : db 10

section .bss
array : resb 50
max : resb 1
min : resb 1
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
    mov byte[temp], al
    ;temp stores no of iterations left

    mov al, byte[array]
    mov byte[max], al
    mov byte[min], al
    mov ebx, array
    
    passing:
        mov al, byte[ebx]
        
        ;compare with max
        cmp al, byte[max]
        ja max_change
        
        ;compare with min 
        cmp al, byte[min]
        jb min_change
        
    ret_pos:
        dec byte[temp]
        add ebx, 1
        cmp byte[temp], 0
        ja passing
        
    print:
        ;print maximum element
        mov eax, 4
        mov ebx, 1
        mov ecx, msg_max
        mov edx, l_max
        int 80h
        
        mov ax, word[max]
        mov bl, 10
        mov ah, 0
        div bl
        mov byte[d2], ah
        mov byte[d1], al
        
        add byte[d2], 30h
        add byte[d1], 30h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, d1
        mov edx, 1
        int 80h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, d2
        mov edx, 1
        int 80h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, newline
        mov edx, 1
        int 80h
        
        ;print minimum element 
        mov eax, 4
        mov ebx, 1
        mov ecx, msg_min
        mov edx, l_min
        int 80h
        
        mov ax, word[min]
        mov bl, 10
        mov ah, 0
        div bl
        mov byte[d2], ah
        mov byte[d1], al
        
        add byte[d2], 30h
        add byte[d1], 30h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, d1
        mov edx, 1
        int 80h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, d2
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
        
        
    max_change:
        mov byte[max], al
        jmp ret_pos
        
    min_change:
        mov byte[min], al
        jmp ret_pos
    
    
