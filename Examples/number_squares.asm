in 
pop rbx

push 1
pop rax

next:

push rax
push rax
mul 
out 

push rax 
push 1
add
pop rax

push rax
push rbx
jbe next:

dump

hlt