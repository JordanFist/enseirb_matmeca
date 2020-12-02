.section .text
	.globl _start
	.extern puts

exit :
	.type exit, @function

	movl %eax, %ebx
	movl $1, %eax
	int $0x80

arg_suiv:
	.type arg_suiv, @function

	movl 8(%ebp, %ecx, 4), %esi #ce que pointe l'adresse ebp + 4 * ecx + 8 est mis dans esi
	cmpl $0,%esi
	je args_exit

	pushl %ecx
	pushl %esi
	call puts
	popl %esi
	popl %ecx
	incl %ecx
	jmp arg_suiv

args_exit:
	.type args_exit, @function

	movl %ebp, %esp
	pop %ebp
	movl %ecx, %eax
	call exit
	
_start:
	.type _start, @function
	pushl %ebp
	movl %esp, %ebp
	movl $0, %ecx
	call arg_suiv

