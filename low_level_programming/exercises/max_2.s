.section .text
	.globl _start

exit :
	.type exit, @function

	movl %eax, %ebx
	movl $1, %eax
	int $0x80

max2:
	.type max2, @function

	pushl %ebp
	movl %esp, %ebp
	pushl %ebx

	movl 8(%ebp), %eax
	movl 12(%ebp), %ebx
	cmpl %eax, %ebx
	jl fin_max2
	movl %ebx, %eax

fin_max2:
	popl %ebx
	movl %ebp, %esp
	popl %ebp
	ret

_start:
	.type _start, @function
	pushl $217
	pushl $192
	call max2
	add $8, %esp
	call exit

