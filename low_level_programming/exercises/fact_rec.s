.section .text
	.globl _start

exit :
	.type exit, @function

	movl %eax, %ebx
	movl $1, %eax
	int $0x80

fact:
	.type fact, @function

	pushl %ebp
	movl %esp, %ebp

	movl 8(%ebp), %ebx
	cmpl $0, %ebx
	jle terminaison

	decl %ebx
	pushl %ebx
	call fact
	popl %ebx
	incl %ebx
	mull %ebx

	jmp fini

terminaison:
	movl $1, %eax

fini:
	movl %ebp, %esp
	popl %ebp
	ret
	
_start:
	.type _start, @function
	movl $5, %esp
	
	call fact

