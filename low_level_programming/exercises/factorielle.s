.section .text
	.globl _start

exit :
	.type exit, @function

	movl %eax, %ebx
	movl $1, %eax
	int $0x80

factorielle:
	movl %eax, %ecx
	movl $1, %eax

prod_suiv:
	imull %ecx
	loop prod_suiv	#decremente ecx jusqu'a qu'il soit a 0
	ret

_start:
	.type _start, @function
	movl $5, %eax
	call factorielle
	call exit
