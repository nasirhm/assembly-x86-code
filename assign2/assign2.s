section .data

BUFLEN:     equ                20
buffer:     times BUFLEN db    0    ; Buffer of 20 '\0's
newline:    db                 10   ; Single newline

section .text

global _start
_start:
    mov rsi, 1
    mov rdi, 10
    call print_int
 
    mov rsi, 1
    mov rdi, 186562354
    call print_int
 
    mov rsi, 1
    mov rdi, 0xdeadbeef12345678         ; = 16045690981402826360 decimal
    call print_int

    ; End program
    mov     rax,  60 
    mov     rdi,  0 
    syscall

print_int:
    ; Loop BUFLEN times
    mov rcx, BUFLEN ; Loop Counter
    ; Divisor to be used in div
    mov r8, 10
    ; div using RDX:RAX as divident
    mov rax, rdi

start_loop:
    ; stored quotient in RAX and remainder in RDX
    div r8
    ; add 48 as the offset for ASCII numerical characters
    add rdx, 48
    ; buffer has zero based indexing
    mov r9, rcx
    dec r9
    ; dl is the lowest byte for RDX
    mov byte[buffer+r9], dl
    ; empty rdx, as it'll be the higher qword for div in the next iteration
    mov rdx, 0
    ; loop, for rcx != 0;
    loop start_loop

print:
    ; SYS_WRITE for buffer
    mov rax, 1
    mov rdi, 1
    mov rsi, buffer
    mov rdx, BUFLEN
    syscall

    ; SYS_WRITE for new line
    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall
    ; Clear the registers as rax, rdx, rcx and r9 are callee preserved registers
    mov rax, 0
    mov rdx, 0

    ; Clear the buffer to clear out any existing values in there.
    mov rcx, BUFLEN ; Loop Counter
    mov r9, rcx
clear_buffer:
    dec r9
    mov byte[buffer+r9], 0
    loop clear_buffer

    ret         ; Return from print_int function
