;calculate sum and average of an array

section .data
msg1 : db 'Enter length of array : '
l1 : equ $-msg1
msg2 : db 'Enter array element : '
l2 : equ $-msg2
msg_sum : db 'Sum of all elements of the array : '
l_sum : equ $-msg_sum
msg_avg : db 'Average of all elements of the array : '
l_avg : equ $-msg_avg
newline : db 10

section .bss
array : resb 50
sum : resw 1
avg : resb 1
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
    
    mov ebx, array
    mov word[sum], 0
    
    calc_sum:
        movzx cx, byte[ebx]             ;change 1
        add word[sum], cx
        dec byte[temp]
        add ebx, 1
        cmp byte[temp], 0
        ja calc_sum
        
    ;calculate average
    mov ax, word[sum]
    mov bl, byte[n]
    div bl
    mov byte[avg], al
    
    ;print sum
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_sum
    mov edx, l_sum
    int 80h
    
    mov byte[temp], 0
    
    sum_extract:
        cmp word[sum], 0
        je sum_print
        inc byte[temp]
        mov bx, 10
        mov dx, 0
        mov ax, word[sum]
        div bx
        push dx
        mov word[sum], ax
        jmp sum_extract
        
    sum_print:
        pop dx
        mov byte[d1], dl
        add byte[d1], 30h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, d1
        mov edx, 1
        int 80h
        
        dec byte[temp]
        cmp byte[temp], 0
        ja sum_print
        
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ;print average
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_avg
    mov edx, l_avg
    int 80h
    
    mov byte[temp], 0
    
    avg_extract:
        cmp byte[avg], 0
        je avg_print
        inc byte[temp]
        mov bx, 10
        mov dx, 0
        mov ah, 0
        mov al, byte[avg]
        div bx
        push dx
        mov byte[avg], al
        jmp avg_extract
        
    avg_print:
        pop dx
        mov byte[d1], dl
        add byte[d1], 30h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, d1
        mov edx, 1
        int 80h
        
        dec byte[temp]
        cmp byte[temp], 0
        ja avg_print
        
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ;exit
    mov eax, 1
    mov ebx, 1
    int 80h
    
    
    
    
