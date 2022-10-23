GLOBAL sys_read
GLOBAL _sys_write
GLOBAL sys_writeat
GLOBAL sys_clearscreen
GLOBAL sys_screensize
section .text

sys_read:
    mov rax, 0
    int 80h
    ret

_sys_write:
    mov rax, 1
    int 80h
    ret

sys_clearscreen:
    mov rax, 4
    int 80h
    ret

sys_writeat:
    mov rax, 5
    mov r10, rcx
    int 80h
    ret

sys_screensize:
    mov rax, 6
    int 80h
    ret