.section .text

.global pclmul

pclmul:	
		movd 		%rcx, %xmm0
		movd 		%rdx, %xmm1
		pclmulqdq 	$0, %xmm0, %xmm1
		movd 		%xmm0,%rax
		ret

.global fetch1		
		
fetch1: 
		psrldq  	$8, %xmm0
		movd  		%xmm0, %rax
		and  		%rcx, %rax
		ret

.global fetch2		
		
fetch2: 
		psrldq 		$4, %xmm0
		movd  		%xmm0, %rax
		ret
