GLOBAL divByZero

section .text

divByZero:
  mov rax, 0
  div rax
  ret