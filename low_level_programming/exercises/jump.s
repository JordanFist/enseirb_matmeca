.section .text
	.globl _start

exit:
	.type exit,@function

	movl %eax, %ebx
	movl $1, %eax
	int $0x80

max2:
	.type max2,@function
	
	cmpl %eax, %ebx		#la comparaison est pour jl apres
	jl fin_max2
	xchgl %ebx, %eax	#echange les 2 valeurs entre les registres

fin_max2:
	ret
	
_start:
	.type _start,@function

	movl $192, %eax
	movl $217, %ebx
	call max2
	call exit
