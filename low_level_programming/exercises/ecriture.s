.section .text
	.globl _start

exit :
	.type exit, @function

	movl %eax, %ebx
	movl $1, %eax
	int $0x80

print:
	.type print, @function

	pushl %ebp
	movl %esp, %ebp

	cld
	movl 8(%ebp), %edi
	movl %edi, %ecx
	movb $0, %al 8

len:
	scasb  #incremente edi de 1 et si le bit pointé par edi est 0(fin de la chaine) il ne jmp pas
	jne len

	subl %ecx, %edi
	decl %edi
	movl %edi, %edx
	movl $1, %ebx
	movl $4, %eax
	int $0x80

	movl %ebp, %esp
	popl %ebp
	ret
	
_start:
	.type _start, @function
	pushl $message
	call print
	addl $4, %esp
	call exit

.section .data
	
message:
	.string "Hello World !\n"

