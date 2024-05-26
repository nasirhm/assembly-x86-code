section .text

global min_max

min_max:
	push rbp
	mov rbp, rsp

	; Arguments:
	; rdi = array
	; len = rsi
	; min = rdx
	; max = rcx

	shr rsi, 3 ; Divide by 8 to get the length of the string
	mov rax, 0
	mov r8, 0

	test rdi, rdi ; Check if array is empty
	jz .end

	; max and min are first elements
	mov rax, [rdi]
	mov r8, [rdi]

.loop_start:
	cmp rsi, 1
	je .end

	add rdi, 8 ; move to next elem
	mov r9, [rdi] ; load elem

	cmp r9, rax ; compare it with rax
	cmovl rax, r9 ; move if below r9
	cmp r9, r8 ; compare it with r8
	cmovg r8, r9 ; moce if aboce r8

	dec rsi ; rsi--
	jmp .loop_start

.end:
	mov [rdx], rax
	mov [rcx], r8

	mov rsp, rbp
	pop rbp
	ret
