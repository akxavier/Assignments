;Read a char and print whether uppercase or lowercase

section .data
msg1 : db 'Enter a character : '
l1 : equ $-msg1
msg2 : db 'UPPERCASE', 10
l2 : equ $-msg2
msg3 : db 'lowercase', 0ah
l3 : equ $-msg3
msg4 : db 'Error', 0ah
l4 : equ $-msg4

section .bss
ch1 : resb 1

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
     mov ecx, ch1
     mov edx, 2
     int 80h
     
     mov al, byte[ch1]
     cmp al, 'A'
     setnc bl
     cmp al, 'Z'+1
     setc bh
     and bl, bh
     cmp bl, 1
     je if
     
     else:
        cmp al, 'a'
        setnc bl
        cmp al, 'z' + 1
        setc bh
        and bl, bh
        cmp bl, 1
        jne error
        
        mov eax, 4
        mov ebx, 1
        mov ecx, msg3
        mov edx, l3
        int 80h
        
        jmp ending
        
    if: 
        mov eax, 4
        mov ebx, 1
        mov ecx, msg2
        mov edx, l2
        int 80h
        
        jmp ending
        
    error:
        mov eax, 4
        mov ebx, 1
        mov ecx, msg4
        mov edx, l4
        int 80h
        
    ending:
        mov eax, 1
        mov ebx, 0
        int 80h
    
