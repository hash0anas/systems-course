.global main

.data
bad_input: .string "bad input"
well: .string "%ld"
wellnl: .string "%ld\n"
wellsp: .string "%ld "
nl: .string "\n"

.text

//Var mapping ..
// nn > %rbx
// xs > %r12
// ii > %r13
// argc > %rdi
// argv > %rsi
main:
    push %rbx
    push %r12
    push %r13
    enter $8, $0

    lea 8(%rsp), %rdi
    call read_int
    mov 8(%rsp), %rbx // nn 
    
    mov %rbx, %rdi
    imul $8, %rdi
    call malloc
    mov %rax, %r12 // xs is in %r12    

    mov $0, %r13 // ii is %r13
loop: //to read input
    cmp %rbx, %r13
    jge loop_done

    lea (%r12,%r13,8), %rdi
    call read_int
    inc %r13
    jmp loop

loop_done:
    mov %r12, %rdi
    mov $0, %rsi
    mov %rbx, %rdx
    call quicksort
    
    mov $wellnl, %rdi
    mov %rbx, %rsi
    mov $0, %al
    call printf

    mov $0, %r13 //ii = 0
print_loop:
    cmp %rbx, %r13
    jge print_loop_done
    mov $wellsp, %rdi
    mov (%r12,%r13,8), %rsi
    mov $0, %al
    call printf

    inc %r13
    jmp print_loop


print_loop_done:
    mov $nl, %rdi
    mov $0, %al
    call printf

    mov %r12, %rdi
    call free
    mov $0, %rax
    leave
    pop %r13
    pop %r12
    pop %rbx
    ret

read_int:
    enter $0, $0
    mov %rdi, %rsi
    mov $well, %rdi
    mov $0, %al
    call scanf
    cmp $1, %rax
    jne abort_now
    leave
    ret

abort_now:
    mov $bad_input, %rdi
    call puts
    mov $1, %rdi
    call exit

//Vriable Mapping ..
//xs > %rdi
//ii > %rsi
//jj > %rdx
//tmp for ii > %rax
//tmp for jj > %rcx
swap:
    enter $0, $0

    mov (%rdi,%rsi,8), %rax //ii
    mov (%rdi,%rdx,8), %rcx //jj
    mov %rax, (%rdi,%rdx,8)
    mov %rcx, (%rdi,%rsi,8)

    leave
    ret

//Variable Mapping ..
//xs > %r12
//hi > %r13
//pivot > %r14
//ii > %r10
//jj > %r11
partition:
    push %r12 //xs
    push %r13 //hi
    push %r14 //pivot
    enter $8, $0
        
    mov %rdi, %r12
    mov %rdx, %r13
    dec %r13
    mov (%r12, %r13, 8), %r14
    mov %rsi, %r10 //ii
    mov %rsi, %r11 //jj

swap_loop:
    cmp %r13, %r11
    jge swap_loop_done
    
    cmp %r14, (%r12,%r11,8) //if (xs[jj] < pivot)
    jl call_swap_from_partition
    inc %r11 //++jj in the for loop, when jl doesn't hold
    jge swap_loop
    
call_swap_from_partition:
    mov %r12, %rdi
    mov %r10, %rsi
    mov %r11, %rdx
    call swap
    inc %r10
    inc %r11 //++jj in the for loop, when jl holds
    jmp swap_loop

swap_loop_done:
   //  swap(xs, ii, hi - 1); return ii;
    mov %r12, %rdi
    mov %r10, %rsi
    mov %r13, %rdx
    call swap
    mov %r10, %rax
    leave
    pop %r14
    pop %r13
    pop %r12
    ret

//Variable Mapping
//xs > %r12, %rdi
//pp > %r13
//lo > %r14, %rsi
//hi > %r15, %rdx
quicksort:
    push %r12 //xs
    push %r13 //pp
    push %r14 //lo
    push %r15 //hi
    enter $0, $0

    mov %rdi, %r12
    mov %rsi, %r14
    mov %rdx, %r15
    
    sub %rsi, %rdx
    cmp $1, %rdx
    jl base_case
    
    mov %r12, %rdi
    mov %r14, %rsi
    mov %r15, %rdx
    call partition
    mov %rax, %r13
    mov %r12, %rdi
    mov %r14, %rsi
    mov %r13, %rdx
    call quicksort

    mov %r12, %rdi
    mov %r13, %rsi
    add $1, %rsi
    mov %r15, %rdx
    call quicksort
    
base_case:
    leave
    pop %r15
    pop %r14
    pop %r13
    pop %r12
    ret

