;;;
;;; assign1.s
;;; Assignment 1 for CSCI 241
;;;

section .data

prompt:       db      "What is your name? "
prompt_len:   equ     $-prompt

buffer:       times 255 db '!'
BUFLEN:       equ     256

resp1:        db      "Hello, "
resp1_len:    equ     $-resp1
resp2:        db      ", nice to meet you!", 10
resp2_len:    equ     $-resp2

section .text
global _start
_start:
	; SYS_WRITE to write the prompt
	mov rax, 1
	mov rdi, 1
	mov rsi, prompt
	mov rdx, prompt_len
	syscall

	; SYS_READ to get name
	mov rax, 0
	mov rdi, 0
	mov rsi, buffer
	mov rdx, BUFLEN
	syscall

	mov r8, rax ; Put the number of characters read in r8

	; SYS_WRITE
	mov rax, 1
	mov rdi, 1
	mov rsi, resp1
	mov rdx, resp1_len
	syscall

	; SYS_WRITE for Buffer
	mov rax, 1
	mov rdi, 1
	mov rsi, buffer
	dec r8
	mov rdx, r8
	syscall

	; SYS_WRITE
	mov rax, 1
	mov rdi, 1
	mov rsi, resp2
	mov rdx, resp2_len
	syscall

	; SYS_EXIT
	mov rax, 60
	mov rdi, 0
	syscall
