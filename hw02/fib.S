// fib program following the recipe ...
// My functions will be fib and main

// Function Recipe .. 
//- Signature
//- Pseudocode
//- Variable Mappings
//- Skeleton
//- Function Body 

.global main

.data
fmt: .string "Usage: %s N, where N >= 0\n"
ifmt: .string "fib(%ld) = %ld\n"

.text

main:
    enter $0, $0
   
    mov (%rsi), %r10 //printing purposes .. r10 holds the program name
    cmp $2, %rdi
    jne error_handle
    
    mov 8(%rsi), %rdi
    call atol
    mov %rax, %r11 //printing purposes .. r11 holds x

    cmp $0, %rax
    jl error_handle

    mov %rax, %rdi
    call fib
    
    mov $ifmt, %rdi
    mov %r11, %rsi
    mov %rax, %rdx
    call printf
    jmp time_to_leave

error_handle:
    mov $fmt, %rdi
    mov %r10, %rsi
    call printf    

time_to_leave:
    leave
    ret


fib:
    push %rbx // will save %rax
    push %r12 // will save %rdi
    enter $0, $0
    
    cmp $2, %rdi
    jl return_same
    
    mov %rdi, %r12 
    sub $1, %rdi
    call fib
    mov %rax, %rbx
    sub $2, %r12
    mov %r12, %rdi
    call fib
    add %rbx, %rax
    jmp done
    
    
return_same:
    mov %rdi, %rax

done:
    leave
    pop %r12
    pop %rbx
    ret
