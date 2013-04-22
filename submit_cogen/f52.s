	.file	"f52.c"
	.text
.globl f
	.type	f, @function
f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$28, %esp
	movl	0(%ebp),%ecx
	movl	$0,-12(%ebp)
	movl	-12(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	$0,-12(%ebp)
	movl	-12(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	$100,-12(%ebp)
	cmpl	-12(%ebp),%ecx
	setl	%al
	movzbl	%al,%ecx
.L1:
	cmpl	$0,%ecx
	jne	.L2
	movl	0(%ebp),%ecx
	movl	$4,-12(%ebp)
	movl	%ecx,%eax
	sarl	$31,%edx
	idivl	-12(%ebp)
	movl	%edx,%ecx
	movl	$0,-12(%ebp)
	cmpl	-12(%ebp),%ecx
	sete	%al
	movzbl	%al,%ecx
	cmpl	$0,%ecx
	jne	.L3
	jmp	.L4
.L3:
.L4:
	movl	0(%ebp),%ecx
	movl	0(%ebp),-12(%ebp)
	movl	$1,-16(%ebp)
	addl	-16(%ebp),-12(%ebp)
	movl	-12(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	$4,-12(%ebp)
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
.L6:
	movl	0(%ebp),%ecx
	movl	0(%ebp),-12(%ebp)
	movl	$100,-16(%ebp)
	addl	-16(%ebp),-12(%ebp)
	movl	-12(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	$4,-12(%ebp)
	movl	%ecx,%eax
	sarl	$31,%edx
	idivl	-12(%ebp)
	movl	%edx,%ecx
	movl	$2,-12(%ebp)
	cmpl	-12(%ebp),%ecx
	sete	%al
	movzbl	%al,%ecx
	cmpl	$0,%ecx
	jne	.L7
	movl	0(%ebp),%ecx
	movl	0(%ebp),-12(%ebp)
	movl	$1000000,-16(%ebp)
	addl	-16(%ebp),-12(%ebp)
	movl	-12(%ebp),%ecx
	jmp	.L8
.L7:
	movl	0(%ebp),%ecx
	movl	0(%ebp),-12(%ebp)
	movl	$10000,-16(%ebp)
	addl	-16(%ebp),-12(%ebp)
	movl	-12(%ebp),%ecx
.L8:
	movl	0(%ebp),%ecx
	movl	0(%ebp),-12(%ebp)
	movl	$1,-16(%ebp)
	addl	-16(%ebp),-12(%ebp)
	movl	-12(%ebp),%ecx
	jmp	.L1
.L2:
	movl	0(%ebp),%ecx
	movl	%ecx,%eax
	jmp	.RETURN
.RETURN:
	leave
	ret
	.size	f, .-f
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
