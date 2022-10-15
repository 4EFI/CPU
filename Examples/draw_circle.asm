
Start:
	in
	pop rdx ; in R to rdx 
	
	call :DrawCircle

	out [0]
	
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
		pop rbx ; R*sin(a) 
		
		call :PushRAM

		push 0.05
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

