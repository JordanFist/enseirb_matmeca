.section .text
	.globl _start

exit :
	.type exit, @function

	movl %eax, %ebx
	movl $1, %eax
	int $0x80

pgcd:
	.type pgcd, @function

boucle_pgcd:
	cmpl $0, %ebx
	je fin_pgcd
	mov $0, %edx
	idivl %ebx,%eax
	movl %ebx,%eax
	movl %edx, %ebx
	jmp boucle_pgcd

fin_pgcd:	
	ret

_start:
	.type _start, @function
	movl $192, %eax
	movl $111, %ebx
	call pgcd
	call exit
