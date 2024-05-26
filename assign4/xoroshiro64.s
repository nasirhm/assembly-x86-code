section .data 

s:    dd     137546,  729 ;inint state
result: dw   0

section .text

global _start

_start:

 push  rbp
 mov   rbp,  rsp

.loop:

 call next

 mov  rax, 1
 mov  rdi, 1
 lea  rsi, [result]
 mov  rdx, 4

 syscall

 jmp  .loop

next: 

 push rbp
 mov  rbp, rsp

 mov  eax, [s]
 mov  ebx, [s+4]

 mov ecx, 0x9E3779BB
 imul eax, ecx
 mov ecx, 5
 rol eax, cl
 imul eax, 5
 mov [result], eax
 mov eax, [s]
 mov ecx, ebx
 xor ecx, eax
 mov edx, ecx
 mov cl, 26
 rol eax, cl
 shl ecx, 9
 xor eax, ecx
 xor eax, edx
 mov [s], eax
 mov eax, edx
 mov cl, 13
 rol eax, cl
 mov [s+4], eax
 mov eax, [result]
 pop rbp 
 ret
