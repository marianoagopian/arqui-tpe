
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler
GLOBAL _irq80Handler

GLOBAL _exception0Handler
GLOBAL getKey

EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN sysWrite
EXTERN sysRead
EXTERN sysClear
EXTERN sysScreenSize
EXTERN sysWriteAt
EXTERN sysInfoReg

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	mov rsi, rsp ; puntero a principio de dump de registros
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

%macro exceptionHandler 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

	popState
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
  mov rbp, rsp
  mov ax, di
  out	21h,al
  pop rbp
  retn

picSlaveMask:
	push    rbp
  mov     rbp, rsp
  mov     ax, di  ; ax = mascara de 16 bits
  out		0A1h, al
  pop     rbp
  retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	irqHandlerMaster 1

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

;Syscall
_irq80Handler:
	push rbp
	mov rbp, rsp
	cmp rax, 0
	je sys_read
	cmp rax, 1
	je sys_write
	cmp rax, 2
	je sys_inforeg
	cmp rax, 4
	je sys_clear_screan
	cmp rax, 5
	je sys_write_at
	cmp rax, 6
	je sys_screen_size
	jmp continue

continue:
	mov rsp, rbp
	pop rbp
	iretq

sys_read:
call sysRead
jmp continue

sys_write:
call sysWrite
jmp continue

sys_clear_screan:
call sysClear
jmp continue

sys_write_at:
call sysWriteAt
jmp continue

sys_screen_size:
call sysScreenSize
jmp continue

sys_inforeg:
call sysInfoReg
jmp continue

;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

haltcpu:
	cli
	hlt
	ret

SECTION .bss
	aux resq 1