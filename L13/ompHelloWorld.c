#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

int main (int argc, char **argv) {
  int numThreads = 4;
  omp_set_num_threads(numThreads);
  
  float *val = (float*) malloc(numThreads*sizeof(float));
  
  int winner = 0;
  float  sum =0;
  #pragma omp parallel shared(val, winner) reduction(+:sum)
  {
    int rank = omp_get_thread_num();
    int size = omp_get_num_threads();


    printf("Hello World, from thread %d of %d!\n", rank, size);
    val[rank] = (float) rank;

    #pragma omp for
    for(int n=1; n<10000; n++) {
      sum += 1/(float) (n);
    }
    //bad
    //fix with master region
    #pragma omp master
    {
      winner = rank;
    }

    //#pragma omp critical
    //{
      //sum+=rank;
    //}
    //A better way is to tell OpenMP to reduce
    sum+= (float)rank;
  }
  
  #pragma omp parallel for
  for(int n=0; n<numThreads; n++) { 
    printf("val[%d]=%f\n", n, val[n]);
  }
  #pragma omp parallel
  {
    int rank = omp_get_thread_num();
    #pragma omp for
    for(int n=0; n<numThreads; n++) {
      if(rank ==n) {
        printf("val[%d]=%f\n",n,val[n]);
      }
    }
  }
  printf("The winner was %d\n", winner);
  printf("The sum was %f\n", sum);
  return 0;
}
