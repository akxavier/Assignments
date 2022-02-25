;linear search

section .data
msg1 : db 'Enter array size : '
l1 : equ $-msg1
msg2 : db 'Enter array element : '
l2 : equ $-msg2
msg3 : db 'Enter item to be searched : '
l3 : equ $-msg3
msg_found : db 'Element found at position '
l_found : equ $-msg_found
msg_notfound : db 'Element not found'
l_notfound : equ $-msg_notfound
newline : db 10

section .bss
array : resb 50
d1 : resb 1
d2 : resb 1
n : resb 1
count : resb 1
junk : resb 1
item : resb 1

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
    
    ;calculate array size
    sub byte[d1], 30h
    sub byte[d2], 30h
    mov al, byte[d1]
    mov bl, 10
    mul bl
    add al, byte[d2]
    mov byte[n], al
    ;n stores array size
    
    ;ebx stores array starting address
    mov ebx, array
    
    ;initialize loop variable to zero
    mov byte[count], 0
    
    reading:
        push ebx
        
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
        
        ;calculate array element
        sub byte[d1], 30h
        sub byte[d2], 30h
        mov al, byte[d1]
        mov bl, 10
        mul bl
        add al, byte[d2]
        
        ;store array element
        pop ebx
        mov byte[ebx], al
        add ebx, 1
        inc byte[count]
        mov al, byte[n]
        cmp byte[count], al
        jb reading
        
    ;read item to be searched
    mov eax, 4
    mov ebx, 1
    mov ecx, msg3
    mov edx, l3
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
    
    ;calculate item to be searched
    sub byte[d1], 30h
    sub byte[d2], 30h
    mov al, byte[d1]
    mov bl, 10
    mul bl
    add al, byte[d2]
    mov byte[item], al
    
    ;ebx contains array address
    mov ebx, array
    
    ;count initialized to zero
    mov byte[count], 0
    
    ;cl contains array length
    mov cl, byte[n]
    
    search:
        mov al, byte[ebx]
        cmp al, byte[item]
        je found
        add ebx, 1
        inc byte[count]
        cmp byte[count], cl
        jb search
        
    not_found:
        mov eax, 4
        mov ebx, 1
        mov ecx, msg_notfound
        mov edx, l_notfound
        int 80h
        
        mov eax, 4
        mov ebx, 1
        mov ecx, newline
        mov edx, 1
        int 80h
        
        jmp exit
        
    found:
        mov eax, 4
        mov ebx, 1
        mov ecx, msg_found
        mov edx, l_found
        int 80h
        
        ;count contains the position of item
        mov ah, 0
        mov al, byte[count]
        mov bl, 10
        div bl
        mov byte[d1], al
        mov byte[d2], ah
        
        add byte[d1], 30h
        add byte[d2], 30h
        
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
        
    exit:
        mov eax, 1
        mov ebx, 0
        int 80h
        
    
    
    
