;count number of vowels in a given string

section .data
msg1 : db 'Enter string : '
l1 : equ $-msg1
msg_a : db 'No. of vowel a : '
l_a : equ $-msg_a
msg_e : db 'No. of vowel e : '
l_e : equ $-msg_e
msg_i : db 'No. of vowel i : '
l_i : equ $-msg_i
msg_o : db 'No. of vowel o : '
l_o : equ $-msg_o
msg_u : db 'No. of vowel u : '
l_u : equ $-msg_u
newline : db 10

section .bss
string : resb 100
char : resb 1
count_a : resb 1
count_e : resb 1
count_i : resb 1
count_o : resb 1
count_u : resb 1

section .text
global _start
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, l1
    int 80h
    
    mov ebx, string
    
read_string:
    push ebx
    
    mov eax, 3
    mov ebx, 0
    mov ecx, char
    mov edx, 1
    int 80h
    
    pop ebx
    
    cmp byte[char], 10
    je end_reading
    mov al, byte[char]
    mov byte[ebx], al
    inc ebx
    jmp read_string
    
end_reading:
    mov byte[ebx], 0
    
    mov ebx, string
    
    ;initialize counts to zero
    mov byte[count_a], 0
    mov byte[count_e], 0
    mov byte[count_i], 0
    mov byte[count_o], 0
    mov byte[count_u], 0
    
    dec ebx
    
counting:
    inc ebx
    cmp byte[ebx], 0
    je print_result
    mov al, byte[ebx]
    cmp al, 'A'
    je inc_a
    cmp al, 'a'
    je inc_a
    cmp al, 'E'
    je inc_e
    cmp al, 'e'
    je inc_e
    cmp al, 'I'
    je inc_i
    cmp al, 'i'
    je inc_i
    cmp al, 'O'
    je inc_o
    cmp al, 'o'
    je inc_o
    cmp al, 'U'
    je inc_u
    cmp al, 'u'
    je inc_u
    jmp counting
    
inc_a:
    inc byte[count_a]
    jmp counting
    
inc_e:
    inc byte[count_e]
    jmp counting
    
inc_i:
    inc byte[count_i]
    jmp counting
    
inc_o:
    inc byte[count_o]
    jmp counting
    
inc_u:
    inc byte[count_u]
    jmp counting
    
print_result:
    add byte[count_a], 30h
    add byte[count_e], 30h
    add byte[count_i], 30h
    add byte[count_o], 30h
    add byte[count_u], 30h
    
    ;print count of a
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_a
    mov edx, l_a
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, count_a
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ;print count of e
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_e
    mov edx, l_e
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, count_e
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
 
    ;print count of i
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_i
    mov edx, l_i
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, count_i
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ;print count of o
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_o
    mov edx, l_o
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, count_o
    mov edx, 1
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ;print count of u
    mov eax, 4
    mov ebx, 1
    mov ecx, msg_u
    mov edx, l_u
    int 80h
    
    mov eax, 4
    mov ebx, 1
    mov ecx, count_u
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
