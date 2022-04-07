;Write a program to read two sorted integer arrays of lengths m and n
;Then merge the arrays in sorted order by avoiding duplicates.

;INPUT
;m : 5
;n : 6
;Array1 : 5 5 12 34 67
;Array2 : 2 5 34 44 56 231 

section .data
msg1 : db 'm : '
l1 : equ $-msg1
msg2 : db 'n : '
l2 : equ $-msg2
msg3 : db 'Array1 : '
l3 : equ $-msg3
msg4 : db 'Array2 : '
l4 : equ $-msg4
newline : db 10
space : db 32

section .bss
m : resb 1
n : resb 1
array1 : resb 50
array2 : resb 50
temp : resb 1
junk : resb 1
count : resb 1
num : resb 1
prev : resb 1
count1 : resb 1
count2 : resb 1

section .text
global _start
_start:
	mov eax, 4
	mov ebx, 1
	mov ecx, msg1
	mov edx, l1
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, m
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
	mov ecx, n
	mov edx, 1
	int 80h

	mov eax, 3
	mov ebx, 0
	mov ecx, junk
	mov edx, 1
	int 80h

	sub byte[m], 30h
	sub byte[n], 30h

	;reading array 1
	mov eax, 4
	mov ebx, 1
	mov ecx, msg3
	mov edx, l3
	int 80h

	mov byte[count], 0
	mov ecx, array1

read_element1:
	mov byte[num], 0
	push ecx
read_digit1:
	mov eax, 3
	mov ebx, 0
	mov ecx, temp
	mov edx, 1
	int 80h

	cmp byte[temp], 32
	je store_element1
	cmp byte[temp], 10
	je store_element1
	sub byte[temp], 30h
	mov ah, 0
	mov al, byte[num]
	mov bl, 10
	mul bl
	mov bl, byte[temp]
	add al, bl
	mov byte[num], al
	jmp read_digit1

store_element1:
	pop ecx
	inc byte[count]
	mov al, byte[num]
	mov byte[ecx], al
	inc ecx
	mov al, byte[m]
	cmp byte[count], al
	jb read_element1

	;reading array 2
	mov eax, 4
	mov ebx, 1
	mov ecx, msg4
	mov edx, l4
	int 80h

	mov byte[count], 0
	mov ecx, array2

read_element2:
	mov byte[num], 0
	push ecx
read_digit2:
	mov eax, 3
	mov ebx, 0
	mov ecx, temp
	mov edx, 1
	int 80h

	cmp byte[temp], 32
	je store_element2
	cmp byte[temp], 10
	je store_element2
	sub byte[temp], 30h
	mov ah, 0
	mov al, byte[num]
	mov bl, 10
	mul bl
	mov bl, byte[temp]
	add al, bl
	mov byte[num], al
	jmp read_digit2

store_element2:
	pop ecx
	inc byte[count]
	mov al, byte[num]
	mov byte[ecx], al
	inc ecx
	mov al, byte[n]
	cmp byte[count], al
	jb read_element2

;merging begins here
mov byte[count1], 0
mov byte[count2], 0

mov ebx, array1
mov ecx, array2

;store array1 element in al
mov al, byte[ebx]
cmp al, byte[ecx]
jb print_array1_meta
jmp print_array2_meta


next_element:
	mov dl, byte[count1]
	cmp dl, byte[m]
	jnb print_array2
	mov dl, byte[count2]
	cmp dl, byte[n]
	jnb print_array1
	mov al, byte[ebx]
	cmp al, byte[ecx]
	jb print_array1
	jmp print_array2
	
print_array1_meta:
	mov al, byte[ebx]
	mov byte[prev], al
	mov byte[num], al
	inc byte[count2]
	inc ebx
	jmp print_loop1

print_array2_meta:
	mov al, byte[ecx]
	mov byte[prev], al
	mov byte[num], al
	inc byte[count2]
	inc ecx
	jmp print_loop2

print_array1:
	mov dl, byte[count1]
	cmp dl, byte[m]
	jnb exit
	inc byte[count1]
	mov al, byte[ebx]
	cmp al, byte[prev]
	je inc_ebx
	mov byte[prev], al
	mov byte[num], al
	inc ebx
print_loop1:
	cmp byte[num], 0
	je print_space
	mov ah, 0
	mov al, byte[num]
	mov dl, 10
	div dl
	mov byte[temp], ah
	mov byte[num], al

	pusha

	add byte[temp], 30h

	mov eax, 4
	mov ebx, 1
	mov ecx, temp
	mov edx, 1
	int 80h

	popa

	jmp print_loop1

print_array2:
	mov dl, byte[count2]
	cmp dl, byte[n]
	jnb exit
	inc byte[count2]
	mov al, byte[ecx]
	cmp al, byte[prev]
	je inc_ecx
	mov byte[prev], al
	mov byte[num], al
	inc ebx
print_loop2:
	cmp byte[num], 0
	je print_space
	mov ah, 0
	mov al, byte[num]
	mov dl, 10
	div dl
	mov byte[temp], ah
	mov byte[num], al

	pusha

	add byte[temp], 30h

	mov eax, 4
	mov ebx, 1
	mov ecx, temp
	mov edx, 1
	int 80h

	popa

	jmp print_loop2
inc_ebx:
	inc ebx
	jmp next_element

inc_ecx:
	inc ecx
	jmp next_element

print_space:
	pusha

	mov eax, 4
	mov ebx, 1
	mov ecx, space
	mov edx, 1
	int 80h

	popa
	jmp next_element


exit:
	mov eax, 4
	mov ebx, 1
	mov ecx, newline
	mov edx, 1
	int 80h

	mov eax, 1
	mov ebx, 0
	int 80h
