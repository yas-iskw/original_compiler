	.file	"f26.c"
	.text
.globl f
	.type	f, @function
f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$9,%ecx
	pushl	%ecx
	movl	$8,%ecx
	pushl	%ecx
	movl	$7,%ecx
	pushl	%ecx
	movl	%ecx, -4(%ebp)
	call	g
	movl	-4(%ebp), %ecx
	movl	%eax, %ecx
	pushl	%ecx
	movl	$6,%ecx
	pushl	%ecx
	movl	$5,%ecx
	pushl	%ecx
	movl	$4,%ecx
	pushl	%ecx
	movl	%ecx, -4(%ebp)
	call	g
	movl	-4(%ebp), %ecx
	movl	%eax, %ecx
	pushl	%ecx
	movl	$3,%ecx
	pushl	%ecx
	movl	$2,%ecx
	pushl	%ecx
	movl	$1,%ecx
	pushl	%ecx
	movl	%ecx, -4(%ebp)
	call	g
	movl	-4(%ebp), %ecx
	movl	%eax, %ecx
	pushl	%ecx
	movl	%ecx, -4(%ebp)
	call	g
	movl	-4(%ebp), %ecx
	movl	%eax, %ecx
	movl	%ecx,%eax
	jmp	.RETURN0
.RETURN0:
	leave
	ret
	.size	f, .-f
.globl g
	.type	g, @function
g:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	8(%ebp),%ecx
	movl	12(%ebp),%edx
	movl	%edx,-8(%ebp)
	addl	-8(%ebp),%ecx
	movl	16(%ebp),%edx
	movl	%edx,-8(%ebp)
	addl	-8(%ebp),%ecx
	movl	%ecx,%eax
	jmp	.RETURN1
.RETURN1:
	leave
	ret
	.size	g, .-g
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
