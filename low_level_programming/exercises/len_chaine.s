.section .text
	.globl _start

exit:
	.type exit, @function

	movl %eax, %ebx
	movl $1, %eax
	int $0x80

longueur:
	.type longueur,@function

	movl %eax, %esi		# dans esi on a eax
	movl $0, %eax

undeplus:
	cmpb $0, (%esi,%eax)	# on regarde vers quoi pointe esi + eax et lorsque esi + eax = 0 on jump car on a je
	je fin_longueur
	incl %eax
	jmp undeplus

fin_longueur:
	ret

_start:
	.type _start,@function
	leal message, %eax	       #dans eax on a l'adresse du premier caractere
	call longueur
	call exit

.section .data

message:
	.string "Hello World !\n", "AAA"
