;sum of prime numbers in an integer array

section .data
msg1 : db 'Enter length of array : '
l1 : equ $-msg1
msg2 : db 'Enter array element : '
l2 : equ $-msg2
msg_sum : db 'Sum of all prime numbers in the array : '
l_sum : equ $-msg_sum
newline : db 10

section .bss
array : resb 50
sum : resb 1
count : resb 1
d1 : resb 1
d2 : resb 1
n : resb 1
junk : resb 1
temp : resb 1
num : resb 1
final : resb 1

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
    ;n contains number of array elements

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
    
    ;store array starting address in ebx
    mov ecx, array
    
    ;initialize sum to zero
    mov byte[sum], 0
    
    loop:
        mov al, byte[ecx]
        mov byte[num], al
        
        ;if num = 2, it is prime, don't bother to check
        cmp byte[num], 2
        je prime
        
        ;if num = 1, continue
        cmp byte[num], 1
        je continue
    
        ;initialize count to two
        mov byte[count], 2
        
        ;store num/2 in dl
        mov al, byte[num]
        mov ah, 0
        mov bl, 2
        div bl
        mov byte[final], al
        mov dl, byte[final]
        
        while:
            mov al, byte[num]
            mov ah, 0
            mov bl, byte[count]
            div bl
            cmp ah, 0
            je continue
            inc byte[count]
            cmp byte[count], dl
            jna while
            
        prime:
        ;code will reach here only if num is prime
        mov al, byte[num]
        add byte[sum], al
        
        continue:
            add ecx, 1
            dec byte[temp]
            cmp byte[temp], 0
            ja loop
            
    mov al, byte[sum]
    mov ah, 0
    mov bl, 10
    div bl
    ;store units digit in d2
    mov byte[d2], ah
    ;store tens digit in d1
    mov byte[d1], al
    
    add byte[d1], 30h
    add byte[d2], 30h
    
    ;print sum 
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_sum
    mov edx, l_sum
    int 80h
    
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
    
    mov eax, 1
    mov ebx, 0
    int 80h
            
        
    
    
