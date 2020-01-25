#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tokenize.h"

int
main(int _argc, char** _argv) {
    char line[100];

    while (1) {
        printf("token$ ");
        fflush(stdout);
        char* rv = fgets(line, 100, stdin); //fgets adds null terminating 0
        if (!rv) {
            break;
        }
        list* tokens = tokenize(line);
        print_list(tokens);
    }

    return 0;
}
