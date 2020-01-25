#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <assert.h>
#include <string.h>

#include "float_vec.h"
#include "barrier.h"
#include "utils.h"

long P; //threads
long* sizes;
barrier* bb;
floats* input;
float* output;


int
qsort_comp(const void* a, const void* b) {
    float aa = *(float*) a;
    float bb = *(float*) b;
    if (aa > bb) return 1;
    else if (aa < bb) return -1;
    else return 0;
}

floats*
read_floats(char* path) {
    int fd = open(path, O_RDONLY);
    assert(fd != -1);

    floats* xs = make_floats(10);

    float tmp;
    while (read(fd, &tmp, sizeof(float))) {
        floats_push(xs, tmp);
    }
    close(fd);
    return xs;
}

float*
sample() {
    int size = 3*(P-1);
    float tmp[size];
   // seed_rng();

    for (int ii = 0 ; ii < size ; ++ii) {
        tmp[ii] = input->data[random() % input->size];
    }

    qsort(&tmp, size, sizeof(float), qsort_comp);
    
    float* samples = malloc((P+1) * sizeof(float));
    samples[0] = 0; // 0 - 100
    samples[P] = 100.0f;
    
    for (int ii = 1, jj = 1 ; ii < P ; ++ii, jj+=3) {
            samples[ii] = tmp[jj];
    }

    return samples;
}

//builds the local array and sort it in place for every thread.
floats*
partition(float start, float end) {
    floats* local = make_floats(10);
    float item;
    for (int ii = 0; ii < input->size; ++ii) {
        item = input->data[ii];
        if (item >= start && item < end) {
            floats_push(local, item);
        }
    }

    qsort(local->data, local->size, sizeof(float), qsort_comp);
    return local;
}


void*
thread_main(void* arg) {
    thread_args* targs = (thread_args*) arg;
    int p = targs->p; //the current thread .. to print info.
    floats* local = partition(targs->start, targs->end); //assuming it works.
    sizes[p] = (long) local->size; //No data race here, each thread is writing to a distinct spot.
    printf("%d: start %.4f, count %ld\n", p, targs->start, sizes[p]);

    barrier_wait(bb);
   
    //compute offset
    int offset = 0;
    for (int ii = 0; ii < p; ++ii) {
        offset += sizes[ii];
    }
    //filling output(sorted) ..
    for (int ii = offset, jj = 0; jj < sizes[p]; ++ii, ++jj) {
        output[ii] = local->data[jj];
    }

    return 0;
}


int
main(int ac, char* av[]) {
   if (ac != 4) {
       puts("Usage: ./ssort N (threads) input-file output-file");
       abort();
   }

   P = atol(av[1]);
   sizes = malloc(P * sizeof(long));
   bb = make_barrier(P);
   input = read_floats(av[2]);
   float* samples = sample();

   int rv;
   pthread_t threads[P];
   thread_args* args;
   output = malloc(input->size*sizeof(float)); 

   for (int ii = 0; ii < P; ++ii) {
      args = make_thread_args(samples[ii], samples[ii+1], ii);
      rv = pthread_create(&(threads[ii]), 0, thread_main, args);
      assert(rv == 0);
   }
  
  //We join here and write to the file. 
   for (int ii = 0; ii < P; ++ii) {
        rv = pthread_join(threads[ii], 0);
   }
   //writing to file.
   long count = input->size;
   int ofd = open(av[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
   write(ofd, &count, sizeof(long));
   write(ofd, output, count*sizeof(float));

   close(ofd);
   free_floats(input);
   free_barrier(bb);
   free(samples);
   free(sizes);
   return 0;
}
