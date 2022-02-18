;add two 2-digit numbers

section .data
msg1 : db 'Enter first 2-digit number : '
l1 : equ $-msg1
msg2 : db 'Enter second 2-digit number : '
l2 : equ $-msg2
msg3 : db ' ', 10
l3 : equ $-msg3

section .bss
d1 : resb 1
d2 : resb 1
d3 : resb 1
d4 : resb 1
junk : resb 1
n1 : resb 1
ans1 : resb 1
ans2 : resb 1
ans3 : resb 1
ans4 : resw 1

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
	mov edx, 1
	int 80h
	
	;Calculating first 2-digit number
	mov bl, 10
	mov al, byte[d1]
	sub al, 30h
	mul bl
	mov bx, word[d2]
	sub bx, 30h
	add ax, bx
	mov word[n1], ax
	
	;Calculating second 2-digit number
	mov bl, 10
	mov al, byte[d3]
	sub al, 30h
	mul bl
	mov bx, word[d4]
	sub bx, 30h
	add ax, bx
	
	;Adding both numbers
	add ax, word[n1]
	
	mov bl, 100
	mov ah, 0
	div bl    ;now ah:al = remainder:quotient
	mov byte[ans1], al
	add byte[ans1], 30h
	
	mov bl, 10
	mov [ans4], ah
	mov ax, word[ans4]
	div bl
    add al, 30h
    mov byte[ans2], al
    add ah, 30h
    mov byte[ans3], ah
    
    ;Print sum
    mov eax, 4
    mov ebx, 1
    mov ecx, ans1
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, ans2
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, ans3
    mov edx, 1
    int 80h
    
    mov eax, 4
	mov ebx, 1
	mov ecx, msg3
	mov edx, l3
	int 80h
    
    mov eax, 1
    mov ebx, 0
    int 80h
