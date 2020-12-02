.section .text
	.globl _start

exit :
	.type exit, @function

	movl %eax, %ebx
	movl $1, %eax
	int $0x80

getchar:
	.type getchar, @function

	pushl %ebx
	pushl %ecx
	pushl %edx

	subl $1, %esp
	movl $3, %eax
	movl $0, %ebx
	movl %esp, %ecx
	movb $0xFF, (%ecx)
	movl $1, %edx
	int $0x80

	movb (%ecx), %al

	addl $1, %esp
	popl %edx
	popl %ecx
	popl %ebx

	ret
	
_start:
	.type _start, @function
	call getchar
	call exit

