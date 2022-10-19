GLOBAL getKey
GLOBAL tKey
section .text

; getKey:
; push rbp
; mov rbp, rsp
; mov rax, 0
; loop: 
; in al, 0x64
; mov cl, al
; and al, 0x01
; cmp al, 0
; je loop
; in al ,0x60
; mov rsp, rbp
; pop rbp
; ret

getKey:
push rbp
mov rbp, rsp
mov rax, 0
in al, 0x60
mov rsp, rbp
pop rbp
ret

; getKey:
;   push rbp
;   mov rbp, rsp

;   mov ah, 1                      ; 0000 0001
;   in al, 64h                    ; status del teclado/8042
;   and al, ah                    ; ???? bitwise(&)  0001 ; me quedo solo con el ultimo bit
;   cmp al, 1                     ; para poder recibir, bit 0 de status tiene que estar en 1
;   jne no_key            ; sino, sigo esperando hasta que sea 0

;   mov rax, 0
;   in al, 60h                    ; leo letra
;   jmp end

;   no_key:
;     mov rax, -1                ; caso letra no leída


;   end:
;     mov rsp, rbp
;     pop rbp
;     ret