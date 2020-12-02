.section .text
	.globl _start

exit :
	.type exit, @function

	movl %eax, %ebx
	movl $1, %eax
	int $0x80

puissance:	
	.type puissance, @function
	movl %ebx, %ecx
	movl %eax, %ebx
	movl $1, %eax

prod_suiv:
	jecxz fin_puissance #jump quand ecx est a 0
	imull %ebx, %eax
	decl %ecx
	jmp prod_suiv

fin_puissance:
	ret

_start:
	.type _start, @function
	movl $2, %eax
	movl $7, %ebx
	call puissance
	call exit
