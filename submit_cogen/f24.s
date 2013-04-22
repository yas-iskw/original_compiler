	.file	"f24.c"
	.text
.globl f
	.type	f, @function
f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp),%ecx
	pushl	%ecx
	movl	%ecx, -4(%ebp)
	call	g
	movl	$4, %esp
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
	pushl	%ecx
	movl	%ecx, -4(%ebp)
	call	h
	movl	$4, %esp
	movl	-4(%ebp), %ecx
	movl	%eax, %ecx
	movl	8(%ebp),%edx
	movl	%edx,-8(%ebp)
	pushl	-8(%ebp)
	movl	%ecx, -4(%ebp)
	call	h
	movl	$4, %esp
	movl	-4(%ebp), %ecx
	movl	%eax, -8(%ebp)
	addl	-8(%ebp),%ecx
	movl	%ecx,%eax
	jmp	.RETURN1
.RETURN1:
	leave
	ret
	.size	g, .-g
.globl h
	.type	h, @function
h:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	8(%ebp),%ecx
	pushl	%ecx
	movl	%ecx, -4(%ebp)
	call	i
	movl	$4, %esp
	movl	-4(%ebp), %ecx
	movl	%eax, %ecx
	movl	8(%ebp),%edx
	movl	%edx,-8(%ebp)
	pushl	-8(%ebp)
	movl	%ecx, -4(%ebp)
	call	i
	movl	$4, %esp
	movl	-4(%ebp), %ecx
	movl	%eax, -8(%ebp)
	addl	-8(%ebp),%ecx
	movl	%ecx,%eax
	jmp	.RETURN2
.RETURN2:
	leave
	ret
	.size	h, .-h
.globl i
	.type	i, @function
i:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$1,%ecx
	movl	%ecx,%eax
	jmp	.RETURN3
.RETURN3:
	leave
	ret
	.size	i, .-i
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
