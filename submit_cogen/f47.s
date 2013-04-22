	.file	"f47.c"
	.text
.globl f
	.type	f, @function
f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$36, %esp
	movl	0(%ebp),%ecx
	movl	$0,-20(%ebp)
	movl	-20(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	$0,-20(%ebp)
	movl	-20(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	$100,-20(%ebp)
	cmpl	-20(%ebp),%ecx
	setl	%al
	movzbl	%al,%ecx
.L1:
	cmpl	$0,%ecx
	jne	.L2
	movl	0(%ebp),%ecx
	movl	$70,-20(%ebp)
	cmpl	-20(%ebp),%ecx
	setge	%al
	movzbl	%al,%ecx
	cmpl	$0,%ecx
	jne	.L3
	jmp	.L4
.L3:
	movl	0(%ebp),%ecx
	movl	$0,-20(%ebp)
	movl	-20(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	0(%ebp),-20(%ebp)
	cmpl	-20(%ebp),%ecx
	setl	%al
	movzbl	%al,%ecx
.L5:
	cmpl	$0,%ecx
	jne	.L6
	movl	0(%ebp),%ecx
	movl	0(%ebp),-20(%ebp)
	movl	0(%ebp),-24(%ebp)
	addl	-24(%ebp),-20(%ebp)
	movl	-20(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	0(%ebp),-20(%ebp)
	movl	$1,-24(%ebp)
	addl	-24(%ebp),-20(%ebp)
	movl	-20(%ebp),%ecx
	jmp	.L5
.L6:
	movl	0(%ebp),%ecx
	movl	0(%ebp),-20(%ebp)
	movl	$1,-24(%ebp)
	addl	-24(%ebp),-20(%ebp)
	movl	-20(%ebp),%ecx
jmp .L1
.L4:
	movl	0(%ebp),%ecx
	movl	0(%ebp),-20(%ebp)
	movl	0(%ebp),-24(%ebp)
	addl	-24(%ebp),-20(%ebp)
	movl	-20(%ebp),%ecx
	movl	0(%ebp),%ecx
	movl	0(%ebp),-20(%ebp)
	movl	$1,-24(%ebp)
	addl	-24(%ebp),-20(%ebp)
	movl	-20(%ebp),%ecx
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
