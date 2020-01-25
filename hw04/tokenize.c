#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "tokenize.h"

char*
read_word(const char* text, int ii) {
    int nn = 0;
    while (isalpha(text[ii + nn]) || text[ii + nn] == '.' || text[ii + nn] == '/'
           || text[ii + nn] == '-'|| text[ii + nn] == '_' || isdigit(text[ii + nn])) { //while still a word
        ++nn;
    }

    char* word = malloc(nn + 1);
    memcpy(word, text + ii, nn);
    word[nn] = 0;
    return word;
}

char*
read_num(const char* text, int ii) {
    int nn = 0;
    while (isdigit(text[ii + nn])) {
        ++nn;
    }
    char* num = malloc(nn + 1);
    memcpy(num, text + ii, nn);
    num[nn] = 0;
    return num;
}

int
contains(char* text, char c) {
    for (int ii = 0 ; text[ii]; ++ii) {
        if (text[ii] == c)
            return 1;
    }
    return 0;
}

char*
read_op(const char* text, int ii) {
    char ops[] = {'<', '>', ';', '|', '&'};
    char* op = malloc(3);
    if (contains(ops, text[ii])) {
        if (text[ii + 1] == '|' || text[ii + 1] == '&'){
            memcpy(op, text + ii, 2);
            op[2] = 0;
        }
        else {
            memcpy(op, text + ii, 1);
            op[1] = 0;
        }
    }  
    return op;
}

list*
tokenize(const char* text) {
    list* xs = 0;
    int nn = strlen(text);
    int ii = 0;
    while (ii < nn) {
        if (isspace(text[ii])) {
            ++ii;
        }
        else if (isalpha(text[ii]) || text[ii] == '.' || text[ii] == '/'
            || text[ii] == '-' || text[ii] == '_'){ //possible initial chars of any word
            char* word = read_word(text, ii);
            xs = cons(word, xs);
            ii += strlen(word);
            free(word);
            continue;
        }
        else if (isdigit(text[ii])) {
            char* num = read_num(text, ii);
            xs = cons(num, xs);
            ii += strlen(num);
            free(num);
            continue;
        }
        else { //operator
            char* op = read_op(text, ii);
            xs = cons(op, xs);
            ii += strlen(op);
            free(op);
        }
   }
    return xs;
}
