	.file	"f28.c"
	.text
.globl f
	.type	f, @function
f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$28, %esp
	movl	-4(%ebp),%ecx
	movl	$0,-12(%ebp)
	movl	-12(%ebp),%ecx
	movl	%ecx,-4(%ebp)
	movl	12(%ebp),%ecx
	movl	$0,-12(%ebp)
	cmpl	-12(%ebp),%ecx
	setl	%al
	movzbl	%al,%ecx
	cmpl	$0,%ecx
	jne	.L1
	jmp	.L2
.L1:
	movl	8(%ebp),%ecx
	movl	8(%ebp),%edx
	movl	%edx,-12(%ebp)
	negl	-12(%ebp)
	movl	-12(%ebp),%ecx
	movl	%ecx,8(%ebp)
	movl	12(%ebp),%ecx
	movl	12(%ebp),%edx
	movl	%edx,-12(%ebp)
	negl	-12(%ebp)
	movl	-12(%ebp),%ecx
	movl	%ecx,12(%ebp)
.L2:
.L3:
	movl	12(%ebp),%ecx
	movl	$0,-12(%ebp)
	cmpl	-12(%ebp),%ecx
	setne	%al
	movzbl	%al,%ecx
	cmpl	$0,%ecx
	je	.L4
	movl	12(%ebp),%ecx
	movl	$2,-12(%ebp)
	movl	%ecx,%eax
	sarl	$31,%edx
	idivl	-12(%ebp)
	movl	%edx,%ecx
	movl	$1,-12(%ebp)
	cmpl	-12(%ebp),%ecx
	sete	%al
	movzbl	%al,%ecx
	cmpl	$0,%ecx
	jne	.L5
	jmp	.L6
.L5:
	movl	-4(%ebp),%ecx
	movl	-4(%ebp),%edx
	movl	%edx,-12(%ebp)
	movl	8(%ebp),%edx
	movl	%edx,-16(%ebp)
	movl	-16(%ebp),%edx
	addl	%edx,-12(%ebp)
	movl	-12(%ebp),%ecx
	movl	%ecx,-4(%ebp)
.L6:
	movl	8(%ebp),%ecx
	movl	8(%ebp),%edx
	movl	%edx,-12(%ebp)
	movl	8(%ebp),%edx
	movl	%edx,-16(%ebp)
	movl	-16(%ebp),%edx
	addl	%edx,-12(%ebp)
	movl	-12(%ebp),%ecx
	movl	%ecx,8(%ebp)
	movl	12(%ebp),%ecx
	movl	12(%ebp),%edx
	movl	%edx,-12(%ebp)
	movl	$2,-16(%ebp)
	movl	-12(%ebp),%eax
	sarl	$31,%edx
	idivl	-16(%ebp)
	movl	%eax,-12(%ebp)
	movl	-12(%ebp),%ecx
	movl	%ecx,12(%ebp)
	jmp	.L3
.L4:
	movl	-4(%ebp),%ecx
	movl	%ecx,%eax
	jmp	.RETURN0
.RETURN0:
	leave
	ret
	.size	f, .-f
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
