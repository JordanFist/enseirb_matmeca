.section .text
	.globl _start

exit:
	.type exit,@function
	movl %eax, %ebx
	movl $1, %eax
	int $0x80

max:
	.type max,@function
	movl %eax, %esi
	movl (%esi), %eax

max_2:
	cmpl $0, (%esi)
	je fin
	cmpl (%esi), %eax
	jl max_3
	addl $4, %esi
	jmp max_2

max_3:
	movl (%esi), %eax
	addl $4, %esi
	jmp max_2

fin:
	ret

_start:
	.type _start,@function
	leal liste, %eax
	call max
	call exit

.section .data
liste:
	.long 31, 8, 55, 21, 59, 71, 13 , 0
