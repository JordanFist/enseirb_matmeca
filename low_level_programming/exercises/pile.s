.section .text
	.globl _start
	.extern puts

exit :
	.type exit, @function

	movl %eax, %ebx
	movl $1, %eax
	int $0x80

_start:
	.type _start, @function
	pushl $message
	call puts
	addl $4, %esp
	call exit

.section .data

message:
	.string "Ce message est affiche par puts"

#on compile avec as --32 pile.s -o pile.o
# puis ld -dynamic-linker /lib/ld-linux.so.2 -ls -m elf_i386 pile.o -o pile
