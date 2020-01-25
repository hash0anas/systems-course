#include <stdio.h>
#include <stdlib.h>


long
fib(int x) {
    if (x < 2)
        return x;
    return fib(x - 1) + fib(x - 2);
}

int
main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s N, where N >= 0\n", argv[0]);
        return -1;
    }
    int x = atol(argv[1]);
    if (x < 0) {
        printf("Usage: %s N, where N >= 0\n", argv[0]);
        return -1;
    }
    long fibx = fib(x);
    printf("fib(%ld) = %ld\n", x, fibx);
    return 0;
}

