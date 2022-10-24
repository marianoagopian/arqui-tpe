GLOBAL sys_read
GLOBAL sys_write
GLOBAL sys_write_at
GLOBAL sys_clear_screen
GLOBAL sys_screen_size
GLOBAL sys_info_reg
section .text

sys_read:
    mov rax, 0
    int 80h
    ret

sys_write:
    mov rax, 1
    int 80h
    ret

sys_info_reg:
    mov rax, 2
    int 80h
    ret

sys_clear_screen:
    mov rax, 4
    int 80h
    ret

sys_write_at:
    mov rax, 5
    mov r10, rcx
    int 80h
    ret

sys_screen_size:
    mov rax, 6
    int 80h
    ret