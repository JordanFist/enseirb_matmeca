.section .text
	.globl _start

exit:
	movl %eax, %ebx
	movl $1, %eax
	int $0x80

fact:
	.type fact,@function
	pushl %ebp
	movl %esp, %ebp
	movl 8(%esp), %ebx
	cmpl $0, %ebx
	jle fin

	decl %ebx
	pushl %ebx
	call fact
	popl %ebx
	incl %ebx
	mull %ebx
	jmp fini

fin:
	movl $1, %eax

fini:
	movl %ebp, %esp
	popl %ebp
	ret
	
_start:	
	.type _start,@function
	pushl $4
	call fact
	addl $4, %esp
	call exit
