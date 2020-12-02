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
	movb $0, %al

len:
	scasb
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

# on compile avec as --32 pile.s -o pile.o
# puis ld -dynamic-linker /lib/ld-linux.so.2 -lc -m elf_i386 pile.o -o pile

# 1) lire un octet dans /dev/random   printf
# 2) idem mais afficher 2 chiffres pris dans les 2 moitiés de l'octet
	# afficher a%10, b%10
# 3) comme 2) mais sans appels de fonction(uniquement des appels système
# 4) afficher une grille de 80 colonnes x20lignes de chiffres obtenus avec la méthode 3
# 5) au lieu des chiffres afficher des blocs de couleur (codes ansi)
