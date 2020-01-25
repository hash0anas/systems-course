// I will just need to define the main function, but I will need atol, strcmp and printf too..
// function recipe .. 
// signature
// psuedocode
// variables mapping
// skeleton
// body

.global main

.data 
fmt: .string "Usage: %s N op N\n"
ifmt: .string "%ld %s %ld = %ld\n"
myadd: .string "+"
mysub: .string "-"
mymul: .string "*"
mydiv: .string "/"

.text

main:
    push %r12   //stores the name of the output file
    push %rbx   //stores a
    push %r13   //stores the op
    push %r14   //stores b
    enter $0, $0

    mov (%rsi), %r12 //output purpose
   
    cmp $4, %rdi
    jne error_handle
    
    mov 8(%rsi), %rbx
    mov 16(%rsi), %r13
    mov 24(%rsi), %r14 
   
    // converting a to a long
    mov %rbx, %rdi
    call atol
    mov %rax, %rbx
    //converting b to a long
    mov %r14, %rdi
    call atol
    mov %rax, %r14

    
    //your if statements..
    mov %r13, %rdi

    mov $myadd, %rsi
    call strcmp
    cmp $0, %rax
    je sum
    
    mov $mysub, %rsi
    call strcmp
    cmp $0, %rax
    je diff
    
    mov $mymul, %rsi
    call strcmp
    cmp $0, %rax
    je mul

    mov $mydiv, %rsi
    call strcmp
    cmp $0, %rax
    je div
    jne error_handle


// %rbx = a, %r14 = b, %r13 = op
sum:
    // No need to setting rax to 0, because we visit all lables only when it's 0.
    add %rbx, %rax
    add %r14, %rax
    jmp print_result

diff:
    add %rbx, %rax
    sub %r14, %rax
    jmp print_result

mul:
    mov $1, %rax
    imul %rbx
    imul %r14
    jmp print_result

div:
    mov %rbx, %rax
    idiv %r14
    jmp print_result

print_result:
    // for the first time, I'm using 5 of the 6
    mov $ifmt, %rdi
    mov %rbx, %rsi
    mov %r13, %rdx
    mov %r14, %rcx
    mov %rax, %r8
    call printf // No need to return result, so rax can be overridden :)
    jmp done

error_handle:
    mov $fmt, %rdi
    mov %r12, %rsi
    call printf

done:
    leave 
    pop %r14
    pop %r13
    pop %rbx
    pop %r12
    ret
