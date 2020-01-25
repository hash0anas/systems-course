#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list*
cons(char* xx, list* xs) {
    list* ys = malloc(sizeof(list));
    ys->head = strdup(xx);
    ys->tail = xs;
    return ys;
}

void
free_list(list* xs) {
    if (xs) {
        free_list(xs->tail);
        free(xs->head);
        free(xs);
    }
}

void
print_list(list* xs) {
    for (; xs; xs = xs->tail) {
        printf("%s\n", xs->head);
    }
}

