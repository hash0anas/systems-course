#ifndef LIST_H
#define LIST_H

typedef struct list {
    char* head;
    struct list* tail;
} list;

list* cons(char* xx, list* xs);
void free_list(list* xs);
void print_list(list* xs);

#endif
