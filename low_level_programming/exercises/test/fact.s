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
	movl %ebx, %eax
	decl %ebx

suite:	
	imull %ebx
	cmpl $0, %ebx
	je fin
	decl %ebx

fin:
	movl %ebp, %esp
	popl %ebp
	ret
	
_start:	
	.type _start,@function
	pushl $4
	call fact
	addl $4, %esp
	call exit
