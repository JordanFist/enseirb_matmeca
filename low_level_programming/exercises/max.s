.section .text
	.globl _start

exit:
	.type exit, @function

	movl %eax, %ebx
	movl $1, %eax
	int $0x80

max:
	.type max, @function

	movl %eax, %esi		#en general les adresses de tableau sont dans esi
	movl (%esi), %ebx
	movl %ebx, %eax

max_suiv:
	cmpl $0, %ebx
	je fin_max
	addl $4, %esi
	movl (%esi), %ebx
	cmpl %eax, %ebx
	jle max_suiv
	movl %ebx, %eax
	jmp max_suiv

fin_max:
	ret

_start:
	.type _start,@function
	leal liste, %eax	       #dans eax on a l'adresse du premier entier
	call max
	call exit

.section .data

liste:	
	.long 31, 8, 55, 21, 59, 71, 13, 129, 64, 9, 25, 102, 87, 0
