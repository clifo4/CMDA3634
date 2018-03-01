#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

int main (int argc, char **argv) {
  int numThreads = 4;
  omp_set_num_threads(numThreads);

  #pragma omp parallel
  {
    int rank = omp_get_thread_num();
    int size = omp_get_num_threads();

    printf("Hello World, from thread %d of %d!\n", rank, size);
  }
  return 0;
}
