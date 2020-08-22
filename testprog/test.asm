
global _start

section .text:

_start:
    ;counter
    mov esi, 10
    head:
    ;syscall 4 (printf)
    mov eax, 0x4
    mov ebx, 1
    mov ecx, message
    mov edx, message_length
    int 0x80
    dec esi
    jnz head

    ;SysCall Exit
    mov eax, 0x1
    mov ebx, 0x0
    int 0x80

section .data:
    message: db " Hello World!", 0xA
    message_length equ $-message
