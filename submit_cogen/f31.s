	.file	"f31.c"
	.text
.globl f
	.type	f, @function
f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	12(%ebp),%ecx
	movl	$0,-8(%ebp)
	cmpl	-8(%ebp),%ecx
	setl	%al
	movzbl	%al,%ecx
	cmpl	$0,%ecx
	jne	.L1
	movl	8(%ebp),%ecx
	movl	$0,-8(%ebp)
	cmpl	-8(%ebp),%ecx
	setl	%al
	movzbl	%al,%ecx
	cmpl	$0,%ecx
	jne	.L3
	movl	12(%ebp),%ecx
	pushl	%ecx
	movl	8(%ebp),%ecx
	pushl	%ecx
	movl	%ecx, -4(%ebp)
	call	g
	popl	%edx
	popl	%edx
	movl	-4(%ebp), %ecx
	movl	%eax, %ecx
	movl	%ecx,%eax
	jmp	.RETURN0
	jmp	.L4
.L3:
	movl	12(%ebp),%ecx
	pushl	%ecx
	movl	8(%ebp),%ecx
	negl	%ecx
	pushl	%ecx
	movl	%ecx, -4(%ebp)
	call	g
	popl	%edx
	popl	%edx
	movl	-4(%ebp), %ecx
	movl	%eax, %ecx
	negl	%ecx
	movl	%ecx,%eax
	jmp	.RETURN0
.L4:
	jmp	.L2
.L1:
	movl	8(%ebp),%ecx
	movl	$0,-8(%ebp)
	cmpl	-8(%ebp),%ecx
	setl	%al
	movzbl	%al,%ecx
	cmpl	$0,%ecx
	jne	.L5
	movl	12(%ebp),%ecx
	negl	%ecx
	pushl	%ecx
	movl	8(%ebp),%ecx
	pushl	%ecx
	movl	%ecx, -4(%ebp)
	call	g
	popl	%edx
	popl	%edx
	movl	-4(%ebp), %ecx
	movl	%eax, %ecx
	negl	%ecx
	movl	%ecx,%eax
	jmp	.RETURN0
	jmp	.L6
.L5:
	movl	12(%ebp),%ecx
	negl	%ecx
	pushl	%ecx
	movl	8(%ebp),%ecx
	negl	%ecx
	pushl	%ecx
	movl	%ecx, -4(%ebp)
	call	g
	popl	%edx
	popl	%edx
	movl	-4(%ebp), %ecx
	movl	%eax, %ecx
	movl	%ecx,%eax
	jmp	.RETURN0
.L6:
.L2:
.RETURN0:
	leave
	ret
	.size	f, .-f
.globl g
	.type	g, @function
g:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	8(%ebp),%ecx
	movl	12(%ebp),%edx
	movl	%edx,-8(%ebp)
	cmpl	-8(%ebp),%ecx
	setl	%al
	movzbl	%al,%ecx
	cmpl	$0,%ecx
	jne	.L7
	movl	0(%ebp),%ecx
	movl	12(%ebp),%edx
	movl	%edx,-8(%ebp)
	movl	-8(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	$1,-8(%ebp)
	movl	-8(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	8(%ebp),%edx
	movl	%edx,-8(%ebp)
	movl	12(%ebp),%edx
	movl	%edx,-12(%ebp)
	movl	-12(%ebp),%edx
	subl	%edx,-8(%ebp)
	movl	-8(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	0(%ebp),%edx
	movl	%edx,-8(%ebp)
	cmpl	-8(%ebp),%ecx
	setg	%al
	movzbl	%al,%ecx
.L9:
	cmpl	$0,%ecx
	jne	.L10
	movl	0(%ebp),%ecx
	movl	0(%ebp),%edx
	movl	%edx,-8(%ebp)
	movl	0(%ebp),%edx
	movl	%edx,-12(%ebp)
	movl	-12(%ebp),%edx
	subl	%edx,-8(%ebp)
	movl	-8(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	0(%ebp),%edx
	movl	%edx,-8(%ebp)
	movl	0(%ebp),%edx
	movl	%edx,-12(%ebp)
	movl	-12(%ebp),%edx
	addl	%edx,-8(%ebp)
	movl	-8(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	0(%ebp),%edx
	movl	%edx,-8(%ebp)
	movl	0(%ebp),%edx
	movl	%edx,-12(%ebp)
	movl	-12(%ebp),%edx
	addl	%edx,-8(%ebp)
	movl	-8(%ebp),%ecx
	jmp	.L9
.L10:
	movl	0(%ebp),%ecx
	movl	12(%ebp),%edx
	movl	%edx,-8(%ebp)
	pushl	-8(%ebp)
	movl	0(%ebp),%edx
	movl	%edx,-8(%ebp)
	pushl	-8(%ebp)
	movl	%ecx, -4(%ebp)
	call	g
	popl	%edx
	popl	%edx
	movl	-4(%ebp), %ecx
	movl	%eax, -8(%ebp)
	addl	-8(%ebp),%ecx
	movl	%ecx,%eax
	jmp	.RETURN1
	jmp	.L8
.L7:
	movl	$0,%ecx
	movl	%ecx,%eax
	jmp	.RETURN1
.L8:
.RETURN1:
	leave
	ret
	.size	g, .-g
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
