#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char* argv[]){
    if (argc != 4) {
        printf("Usage: %s N op N\n", argv[0]);
        return -1;
    }
    long a = atol(argv[1]);
    long b = atol(argv[3]);
    long res;
  
    if (strcmp(argv[2], "+") == 0)
        res = a + b;   
    else if (strcmp(argv[2], "-") == 0)
        res = a - b;
    else if (strcmp(argv[2], "*") == 0)
        res = a * b;      
    else if (strcmp(argv[2], "/") == 0)
        res = a / b;    
    else {
        printf("Usage: %s N op N\n", argv[0]);
        return -1;
    }
    printf("%ld %s %ld = %ld\n", a, argv[2], b, res);
    return -1;
} 
