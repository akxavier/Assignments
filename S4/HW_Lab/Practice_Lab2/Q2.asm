section .data
msg: db 'Enter a two-digit number : '
l: equ $-msg
newline: db 10

section .bss
d1: resb 1
d2: resb 1
junk: resb 1
num: resw 1
count: resb 1
temp: resb 1

section .text
  global _start:
  _start:

  mov eax,4
  mov ebx,1
  mov ecx,msg
  mov edx,l
  int 80h

  mov eax,3
  mov ebx,0
  mov ecx,d1
  mov edx,1
  int 80h

  mov eax,3
  mov ebx,0
  mov ecx,d2
  mov edx,2
  int 80h

  sub byte[d1],30h
  sub byte[d2],30h
  mov al,byte[d1]
  mov bl,10
  mul bl
  mov bl,byte[d2]
  mov bh,0
  add ax,bx

  mov bx,ax
  mul bx

  mov word[num],ax 
  call print_num

  mov eax,1
  mov ebx,0
  int 80h


print_num:
  mov byte[count],0
  pusha
  extract_no:
    cmp word[num],0
    je print_no
    inc byte[count]
    mov dx,0
    mov ax,word[num]
    mov bx,10
    div bx 
    push dx 
    mov word[num],ax 
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
 
popa
ret
