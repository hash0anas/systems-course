# 1 "cube.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "cube.S"
.global cube
cube:
 enter $0, $0
 mov %rdi, %rax
 imul %rdi, %rax
 imul %rdi, %rax
 leave
 ret
