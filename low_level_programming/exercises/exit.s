.section .text
	.global _start

exit:
	.type exit,@function
	
	movl %eax,%ebx          #place la valeur de %eax dans %ebx
	movl $1, %eax		#place 1 dans eax			
	int $0x80		# dans $? il y a ebx

calcul:
	.type _start,@function	#page 10 dans quel registre vont les résultats
	movl %eax, %ecx
	imull %eax	#la x met le resultat dans edx:eax ici on dépasse pas
	movl $0, %edx	#on met quand meme edx a 0
	movl $4, %ebx
	idivl %ebx	#on divise eax par ebx
	movl %eax, %ebx	#on met 25 dans ebx
	movl $5, %eax
	imull %ecx	#on met 5*10 dans ecx
	subl %eax, %ebx	#on soustrait 
	addl $7, %ebx	
	movl %ebx, %eax
	ret
	
_start:
	.type _start,@function
	
	movl $10, %eax
	call calcul
	call exit

# réponse 238 modulo 256 car la reponse est -18
# echo $?
