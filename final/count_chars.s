section .text


global count_chars

count_chars:
	push rbp
	mov rbp, rsp

	mov rcx, 0
	; mov rdi address into rsi
	mov rsi, rdi

.count_loop:
	mov al, byte[rsi]
	; if null
	cmp al, 0
	jz .end_count
	; if below 0
	cmp al, '0'
	jb .not_digit
	; if above 9
	cmp al, '9'
	ja .not_digit

	; rcx++ if digit is found
	inc rcx

.not_digit:
	; increment rsi and call loop again
	inc rsi
	jmp .count_loop

.end_count:
	; mov rcx (count) into rax.
	mov rax, rcx
	; restore rsp
	mov rsp, rbp

	pop rbp
	ret
