;print sum of even numbers from 0 to a given 2-digit number

section .data
msg1 : db 'Enter a 2-digit number : '
l1 : equ $-msg1
newline : db 10

section .bss
d1 : resb 1
d2 : resb 1
junk : resb 1
num1 : resb 1
count : resb 1
temp : resb 1
sum : resw 1

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
    
    ;calculate number
    sub byte[d1], 30h
    sub byte[d2], 30h
    mov al, byte[d1]
    mov bl, 10
    mul bl
    mov bh, 0
    mov bl, byte[d2]
    add ax, bx
    mov byte[num1], al
    
    mov bx, 2
    mov ax, 0
    
    while:
        cmp bx, word[num1]
        ja print
        add ax, bx
        add bx, 2
        jmp while
       
print:
    mov word[sum], ax
    mov byte[count],0
    extract_no:
        cmp word[sum],0
        je print_no
        inc byte[count]
        mov dx,0
        mov ax,word[sum]
        mov bx,10
        div bx 
        push dx 
        mov word[sum],ax 
        jmp extract_no

    print_no:
        cmp byte[count],0
        je end_print
        dec byte[count]
        pop dx 
        mov byte[temp],dl 
        add byte[temp],30h

        mov eax,4
        mov ebx,1
        mov ecx,temp
        mov edx,1
        int 80h
        jmp print_no

    end_print:
        mov eax,4
        mov ebx,1
        mov ecx,newline
        mov edx,1
        int 80h 
        
    mov eax, 1
    mov ebx, 0
    int 80h
 
    

        
