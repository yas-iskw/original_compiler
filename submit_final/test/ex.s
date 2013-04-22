	.file	"ex.c"
	.text
.globl f
	.type	f, @function
f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$4032, %esp
	pushl	%ebx
	movl	$0,-4004(%ebp)
.L1:
	movl	-4004(%ebp),%ebx
	movl	$1000,%ecx
	cmpl	%ecx,%ebx
	jge	.L2
	movl	-4004(%ebp),%ebx
	movl	%ebx,%edx
	movl	$1,-4000(%ebp,%edx,4)
	movl	-4000(%ebp,%edx,4),%ebx
	movl	-4004(%ebp),%ebx
	addl	$1,%ebx
	movl	%ebx,-4004(%ebp)
	jmp	.L1
.L2:
	movl	$2,-4004(%ebp)
.L3:
	movl	-4004(%ebp),%ebx
	movl	$1000,%ecx
	cmpl	%ecx,%ebx
	jge	.L4
	movl	-4004(%ebp),%ebx
	subl	$1,%ebx
	movl	%ebx,%edx
	movl	-4000(%ebp,%edx,4),%ebx
	movl	%ebx,-4008(%ebp)
	movl	-4004(%ebp),%ebx
	subl	$2,%ebx
	movl	%ebx,%edx
	movl	-4000(%ebp,%edx,4),%ebx
	movl	%ebx,-4012(%ebp)
	movl	-4004(%ebp),%ebx
	movl	%ebx,%edx
	movl	-4008(%ebp),%ebx
	addl	-4012(%ebp),%ebx
	movl	%ebx,-4000(%ebp,%edx,4)
	movl	-4000(%ebp,%edx,4),%ebx
	movl	-4004(%ebp),%ebx
	addl	$1,%ebx
	movl	%ebx,-4004(%ebp)
	jmp	.L3
.L4:
	movl	8(%ebp),%ebx
	movl	%ebx,%edx
	movl	-4000(%ebp,%edx,4),%ebx
	movl	%ebx,%eax
.RETURN0:
	popl	%ebx
	leave
	ret
	.size	f, .-f
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
