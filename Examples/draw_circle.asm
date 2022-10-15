
Start:
	in
	pop rdx ; in R to rdx 
	
	call :DrawFillCircle
	
	in	

	hlt

DrawCircle:
	push 0
	pop rax

	next:
		push rax
		cos
		push rdx ; R
		mul
		push 2
		mul
		pop rcx ; 2*R*cos(a)
		
		push rax
		sin
		push rdx ; R
		mul
		push 1
		mul 
		pop rbx ; 1*R*sin(a) 
		
		call :PushRAM

		push 0.05 ; step
		push rax
		add
		pop rax

		push rax
		push 2
		push 3.14
		mul
		jae :endDrawCircle 
		
		jmp :next

	endDrawCircle:
	ret

PushRAM:
	pushi rbx
	push 60
	mul
	pushi rcx
	add
			
	push 60
	push 29
	mul
	push 2
	div
	add
 
	pop rbx
            
	push 42 ; symbol '*' 
    pop [rbx]

    ret

DrawFillCircle:
	nextFillCircle:
		push rdx
		push 0
		jbe :endDrawFillCircle

		call :DrawCircle

		push rdx
		push 0.5
		sub
		pop rdx

		jmp :nextFillCircle
	
	endDrawFillCircle:
	ret

