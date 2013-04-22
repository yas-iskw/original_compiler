	.file	"f34.c"
	.text
.globl f
	.type	f, @function
f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$28, %esp
	movl	-4(%ebp),%ecx
	movl	8(%ebp),%edx
	movl	%edx,-12(%ebp)
	movl	12(%ebp),%edx
	movl	%edx,-16(%ebp)
	movl	-12(%ebp),%eax
	sarl	$31,%edx
	idivl	-16(%ebp)
	movl	%eax,-12(%ebp)
	movl	-12(%ebp),%ecx
	movl	%ecx,-4(%ebp)
	movl	8(%ebp),%ecx
	movl	-4(%ebp),%edx
	movl	%edx,-12(%ebp)
	movl	12(%ebp),%edx
	movl	%edx,-16(%ebp)
	movl	-16(%ebp),%edx
	imull	%edx,-12(%ebp)
	subl	-12(%ebp),%ecx
	movl	%ecx,%eax
	jmp	.RETURN0
.RETURN0:
	leave
	ret
	.size	f, .-f
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
