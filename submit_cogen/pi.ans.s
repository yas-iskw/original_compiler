	.file	"pi.c"
	.text
.globl get_random
	.type	get_random, @function
get_random:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$20, %esp
	movl	8(%ebp),%ecx
	movl	$1103515245,-8(%ebp)
	movl	%ecx,%eax
	imull	-8(%ebp),%eax
	movl	%eax,%ecx
	movl	$12345,-8(%ebp)
	addl	-8(%ebp),%ecx
	movl	%ecx,%eax
	jmp	.RETURN0
.RETURN0:
	leave
	ret
	.size	get_random, .-get_random
.globl c0func
	.type	c0func, @function
c0func:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$48, %esp
	movl	$0,-32(%ebp)
	movl	-32(%ebp),%ecx
	movl	%ecx,-4(%ebp)
	movl	16(%ebp),%edx
	movl	%edx,-32(%ebp)
	movl	-32(%ebp),%ecx
	movl	%ecx,-8(%ebp)
	movl	$0,-32(%ebp)
	movl	-32(%ebp),%ecx
	movl	%ecx,-12(%ebp)
.L1:
	movl	-4(%ebp),%ecx
	movl	8(%ebp),%edx
	movl	%edx,-32(%ebp)
	cmpl	-32(%ebp),%ecx
	setl	%al
	movzbl	%al,%ecx
	cmpl	$0,%ecx
	je	.L2
	movl	-8(%ebp),%edx
	movl	%edx,-32(%ebp)
	pushl	-32(%ebp)
	movl	%ecx, -28(%ebp)
	call	get_random
	addl	$4, %esp
	movl	-28(%ebp), %ecx
	movl	%eax, -32(%ebp)
	movl	-32(%ebp),%ecx
	movl	%ecx,-8(%ebp)
	movl	-8(%ebp),%edx
	movl	%edx,-32(%ebp)
	movl	12(%ebp),%edx
	movl	%edx,-36(%ebp)
	movl	-32(%ebp),%eax
	sarl	$31,%edx
	idivl	-36(%ebp)
	movl	%edx,-32(%ebp)
	movl	-32(%ebp),%ecx
	movl	%ecx,-16(%ebp)
	movl	-8(%ebp),%edx
	movl	%edx,-32(%ebp)
	pushl	-32(%ebp)
	movl	%ecx, -28(%ebp)
	call	get_random
	addl	$4, %esp
	movl	-28(%ebp), %ecx
	movl	%eax, -32(%ebp)
	movl	-32(%ebp),%ecx
	movl	%ecx,-8(%ebp)
	movl	-8(%ebp),%edx
	movl	%edx,-32(%ebp)
	movl	12(%ebp),%edx
	movl	%edx,-36(%ebp)
	movl	-32(%ebp),%eax
	sarl	$31,%edx
	idivl	-36(%ebp)
	movl	%edx,-32(%ebp)
	movl	-32(%ebp),%ecx
	movl	%ecx,-20(%ebp)
	movl	-8(%ebp),%edx
	movl	%edx,-32(%ebp)
	pushl	-32(%ebp)
	movl	%ecx, -28(%ebp)
	call	get_random
	addl	$4, %esp
	movl	-28(%ebp), %ecx
	movl	%eax, -32(%ebp)
	movl	-32(%ebp),%ecx
	movl	%ecx,-8(%ebp)
	movl	-8(%ebp),%edx
	movl	%edx,-32(%ebp)
	movl	12(%ebp),%edx
	movl	%edx,-36(%ebp)
	movl	-32(%ebp),%eax
	sarl	$31,%edx
	idivl	-36(%ebp)
	movl	%edx,-32(%ebp)
	movl	-32(%ebp),%ecx
	movl	%ecx,-24(%ebp)
	movl	-16(%ebp),%ecx
	movl	-16(%ebp),%edx
	movl	%edx,-32(%ebp)
	movl	%ecx,%eax
	imull	-32(%ebp),%eax
	movl	%eax,%ecx
	movl	-20(%ebp),%edx
	movl	%edx,-32(%ebp)
	movl	-20(%ebp),%edx
	movl	%edx,-36(%ebp)
	movl	-36(%ebp),%edx
	movl	-32(%ebp),%eax
	imull	%edx,%eax
	movl	%eax,-32(%ebp)
	addl	-32(%ebp),%ecx
	movl	-24(%ebp),%edx
	movl	%edx,-32(%ebp)
	movl	-24(%ebp),%edx
	movl	%edx,-36(%ebp)
	movl	-36(%ebp),%edx
	movl	-32(%ebp),%eax
	imull	%edx,%eax
	movl	%eax,-32(%ebp)
	addl	-32(%ebp),%ecx
	movl	12(%ebp),%edx
	movl	%edx,-32(%ebp)
	movl	12(%ebp),%edx
	movl	%edx,-36(%ebp)
	movl	-36(%ebp),%edx
	movl	-32(%ebp),%eax
	imull	%edx,%eax
	movl	%eax,-32(%ebp)
	cmpl	-32(%ebp),%ecx
	setle	%al
	movzbl	%al,%ecx
	cmpl	$0,%ecx
	jne	.L3
	jmp	.L4
.L3:
	movl	-12(%ebp),%edx
	movl	%edx,-32(%ebp)
	movl	$1,-36(%ebp)
	movl	-36(%ebp),%edx
	addl	%edx,-32(%ebp)
	movl	-32(%ebp),%ecx
	movl	%ecx,-12(%ebp)
.L4:
	movl	-4(%ebp),%edx
	movl	%edx,-32(%ebp)
	movl	$1,-36(%ebp)
	movl	-36(%ebp),%edx
	addl	%edx,-32(%ebp)
	movl	-32(%ebp),%ecx
	movl	%ecx,-4(%ebp)
	jmp	.L1
.L2:
	movl	-12(%ebp),%ecx
	movl	$6,-32(%ebp)
	movl	%ecx,%eax
	imull	-32(%ebp),%eax
	movl	%eax,%ecx
	movl	8(%ebp),%edx
	movl	%edx,-32(%ebp)
	movl	%ecx,%eax
	sarl	$31,%edx
	idivl	-32(%ebp)
	movl	%eax,%ecx
	pushl	%ecx
	movl	%ecx, -28(%ebp)
	call	print_int
	addl	$4, %esp
	movl	-28(%ebp), %ecx
	movl	%eax, %ecx
	movl	$46,%ecx
	pushl	%ecx
	movl	%ecx, -28(%ebp)
	call	print_char
	addl	$4, %esp
	movl	-28(%ebp), %ecx
	movl	%eax, %ecx
	movl	-12(%ebp),%ecx
	movl	$6,-32(%ebp)
	movl	%ecx,%eax
	imull	-32(%ebp),%eax
	movl	%eax,%ecx
	movl	8(%ebp),%edx
	movl	%edx,-32(%ebp)
	movl	%ecx,%eax
	sarl	$31,%edx
	idivl	-32(%ebp)
	movl	%edx,%ecx
	pushl	%ecx
	movl	%ecx, -28(%ebp)
	call	print_int
	addl	$4, %esp
	movl	-28(%ebp), %ecx
	movl	%eax, %ecx
	movl	%ecx, -28(%ebp)
	call	print_line
	addl	$0, %esp
	movl	-28(%ebp), %ecx
	movl	%eax, %ecx
	movl	$0,%ecx
	movl	%ecx,%eax
	jmp	.RETURN1
.RETURN1:
	leave
	ret
	.size	c0func, .-c0func
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
