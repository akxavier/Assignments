;find largest and smallest word in a string

section .data
msg1 : db 'Enter string : '
l1 : equ $-msg1
msg2 : db 'Largest word is : '
l2 : equ $-msg2
msg3 : db 'Smallest word is : '
l3 : equ $-msg3
newline : db 10

section .bss
string : resb 100
char : resb 1
wordaddr : resd 1
wordlen : resb 1
junk : resb 1
minaddr : resd 1
minlen : resb 1
maxaddr : resd 1
maxlen : resb 1

section .text
global _start
_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, l1
    int 80h
    
read_str:
    mov ebx, string
    
read_loop:
    push ebx
    
    mov eax, 3
    mov ebx, 0
    mov ecx, char
    mov edx, 1
    int 80h
    
    pop ebx
    
    cmp byte[char], 10
    je end_read
    mov al, byte[char]
    mov byte[ebx], al
    inc ebx
    jmp read_loop
    
end_read:
    mov byte[ebx], 0
    
    ;reinitialize ebx to string
    mov ebx, string
    
    ;set max and min as first word
    mov dword[wordaddr], ebx
    mov byte[wordlen], 0
first_word:
    cmp byte[ebx], 32
    je set_first_word
    inc byte[wordlen]
    inc ebx
    jmp first_word
    
set_first_word:
    ;set first word as min
    mov eax, dword[wordaddr]
    mov dword[minaddr], eax
    mov al, byte[wordlen]
    mov byte[minlen], al
    ;set first word as max
    mov eax, dword[wordaddr]
    mov dword[maxaddr], eax
    mov al, byte[wordlen]
    mov byte[maxlen], al
    
;loop to check for the remaining words in the string
next_word:
    cmp byte[ebx], 0
    je print_result
    inc ebx
    mov dword[wordaddr], ebx
    mov byte[wordlen], 0
word_loop:
    cmp byte[ebx], 0
    je check_min_max
    cmp byte[ebx], 32
    je check_min_max
    inc byte[wordlen]
    inc ebx
    jmp word_loop
check_min_max:
    mov al, byte[wordlen]
    cmp al, byte[minlen]
    jb change_min
    cmp al, byte[maxlen]
    ja change_max
    jmp next_word
    
change_min:
    mov byte[minlen], al
    mov eax, dword[wordaddr]
    mov dword[minaddr], eax
    jmp next_word
    
change_max:
    mov byte[maxlen], al
    mov eax, dword[wordaddr]
    mov dword[maxaddr], eax
    jmp next_word
    
print_result:
    ;print largest word
    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, l2
    int 80h
    
    mov ebx, dword[maxaddr]
    
print_max_word:
    cmp byte[ebx], 32
    je end_max_print
    cmp byte[ebx], 0
    je end_max_print
    mov al, byte[ebx]
    mov byte[char], al
    push ebx
    
    mov eax, 4
    mov ebx, 1
    mov ecx, char
    mov edx, 1
    int 80h
    
    pop ebx
    inc ebx
    jmp print_max_word
    
end_max_print:
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    ;print smallest word
    mov eax, 4
    mov ebx, 1
    mov ecx, msg3
    mov edx, l3
    int 80h
    
    mov ebx, dword[minaddr]
    
print_min_word:
    cmp byte[ebx], 32
    je end_min_print
    cmp byte[ebx], 0
    je end_min_print
    mov al, byte[ebx]
    mov byte[char], al
    push ebx
    
    mov eax, 4
    mov ebx, 1
    mov ecx, char
    mov edx, 1
    int 80h
    
    pop ebx
    inc ebx
    jmp print_min_word
    
end_min_print:
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 80h
    
    mov eax, 1
    mov ebx, 0
    int 80h
    
    

    
    
    
    
