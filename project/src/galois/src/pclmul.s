.CODE
pclmul PROC
   movd xmm0, rcx
   movd xmm1, rdx
   pclmulqdq xmm0, xmm1, 0
   movd rax, xmm0
   ret
pclmul ENDP 
fetch1 PROC
   psrldq xmm0, 8
   movd rax, xmm0
   and rax, rcx
   ret
fetch1 ENDP 
fetch2 PROC
   psrldq xmm0, 4
   movd rax, xmm0
   ret
fetch2 ENDP 
END 