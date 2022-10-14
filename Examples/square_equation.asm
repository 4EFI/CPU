in
pop rax
in
pop rbx
in
pop rcx

call :SolveSquareEquation

hlt

SolveLinearEquation:
	push rbx
	push 0
	je  :isNullB
	jmp :isNotNullB	

	isNullB:
		push rcx
		push 0 
		je  :infLinearEqSolutions
		jmp  :noLinearEqSolutions

	isNotNullB:
		push -1
		push rcx
		mul
		push rbx
		div
		out
		jmp :endSolveLinearEquation

	infLinearEqSolutions:
		jmp :endSolveLinearEquation
	
	noLinearEqSolutions:
		jmp :endSolveLinearEquation	
	
	endSolveLinearEquation:			
	ret

SolveSquareEquation:
	push rax
	push 0
	je  :isNullA	
	jmp :isNotNullA

	isNullA:	
		call :SolveLinearEquation
		jmp :endSolveSquareEquation			

	isNotNullA:
		call :CountD

		push rdx
		push 0
		jb :noSolutions

		push rdx
		push 0
		je  :oneSolution
		jmp :twoSolutions

	noSolutions:
		jmp :endSolveSquareEquation

	oneSolution:
		push -1
		push rbx
		mul
		push 2
		div
		push rax
		div
		out

		jmp :endSolveSquareEquation

	twoSolutions:
		push rdx
		sqrt	
		pop rdx 

		push -1 
		push rbx
		mul
		push rdx
		add 
		push 2
		div
		push rax
		div
		out

		push -1 
		push rbx
		mul
		push rdx
		sub 
		push 2
		div
		push rax
		div
		out
	
		jmp :endSolveSquareEquation

	infiniteSolutions:
		jmp :endSolveSquareEquation

	endSolveSquareEquation:		
	ret

CountD:
	push rbx
	push rbx
	mul
 
	push rax
	push rcx
	mul
	push 4
	mul
	
	sub
	pop rdx

	ret
