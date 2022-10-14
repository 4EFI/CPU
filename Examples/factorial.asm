in 
pop rax

push 1
pop rbx 

call :Factorial

hlt

Factorial:  	
	push 0
	push rax
	je :outFactorial

	push rbx
    push rax
	mul
	pop rbx

	push rax
	push -1
	add
	pop rax

	call :Factorial	
	jmp :endFactorial

	outFactorial:
		push rbx
		out     	
	
	endFactorial:
	ret

         
