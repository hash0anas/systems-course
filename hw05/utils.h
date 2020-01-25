// Author: Nat Tuck
// CS3650 starter code

#ifndef UTILS_H
#define UTILS_H

#include "float_vec.h"

typedef struct thread_args {
    float start;
    float end;
    int p;
} thread_args;

thread_args* make_thread_args(float ii, float ff, int p);
void seed_rng();
void check_rv(int rv);

#endif

