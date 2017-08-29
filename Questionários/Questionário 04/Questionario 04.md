Para todas as questões, considere que as variáveis `f`, `g`, `h`, `i` e `j` são do tipo inteiro (16 bits na arquitetura do MSP430), e que o vetor `A[]` é do tipo inteiro. Estas variáveis estão armazenadas nos seguintes registradores:
	f: R4
	g: R5
	h: R6
	i: R7
	j: R8
	A: R9
Utilize os registradores R11, R12, R13, R14 e R15 para armazenar valores temporários.

1. Traduza as seguintes linhas em C para a linguagem assembly do MSP430. Utilize somente as seguintes instruções: mov.w, add.w e sub.w.

	(a) `f = 0;`
	
	```Assembly
	   mov.w #0, R4
	```
	(b) `g++;`
	
	```Assembly
	   mov.w #1, R11
	   add.w R11, R5
	```
	  
	(c) `h--;`
	
	```Assembly
	   mov.w #1, R12
	   sub.w R11, R6
	```
	  
	(d) `i += 2;`	
	
	```Assembly
	   mov.w #2, R13
	   add.w R11, R7
	```	
	  
	(e) `j -= 2;`	
	
	```Assembly
	   mov.w #2, R14
	   sub.w R11, R8
        ```
	
2. Traduza as seguintes linhas em C para a linguagem assembly do MSP430. Utilize somente as seguintes instruções: mov.w, add.w, sub.w, clr.w, dec.w, decd.w, inc.w e incd.w.

	(a) `f = 0;`
	
	```Assembly
	   mov.w #0, R4
	```	
	   
	(b) `g++;`
	
	```Assembly 
	   inc.w R5
	```	
	   
	(c) `h--;`
	
	```Assembly 
	   dec.w R6
	```	
	   
	(d) `i += 2;`
	
	```Assembly 
	   incd.w R7
	```
	   
	(e) `j -= 2;`
	
	```Assembly
	   decd.w R8
	```
	   
	
3. Traduza as seguintes linhas em C para a linguagem assembly do MSP430. Utilize somente as seguintes instruções: mov.w, add.w, sub.w, clr.w, dec.w, decd.w, inc.w e incd.w.

	(a) `f *= 2;`
	
	```Assembly  
		add.w R4, R4
	```
	
	(b) `g *= 3;`
	
	```Assembly
		mov.w R5, R11
		add.w R5, R11
		add.w R5, R11
		mov.w R11, R5
	```
	  
	(c) `h *= 4;`
	
	```Assembly
		mov.w R6, R12
		add.w R6, R12
		add.w R6, R12
		add.w R6, R12
		```
	  
	(d) `A[2] = A[1] + A[0];`
	 
	```Assembly
		mov.w 2(R9), 4(R9)
		add.w 0(R9), 4(R9)
	```
	 
	(e) `A[3] = 2*f - 4*h;`

	```Assembly
		mov.w R4, R11
		mov.w R6, R12
		add.w R4, R11
		add.w R6, R12
		add.w R6, R12
		add.w R6, R12
		sub.w R12, R11
		mov.w R11, R13
		mov.w R13, 6(R9)
	```  
	
	(f) `A[3] = 2*(f - 2*h);`
	
	```Assembly
		mov.w R4, R12
		mov.w R6, R13
		add.w R6, R13
		sub.w R6, R12
		mov.w R12, 6(R9)
	```
