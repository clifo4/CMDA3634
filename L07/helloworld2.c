#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>

int main(int argc, char **argv) {
  
  //every MPI program must start with an initialize
  //always do this first
  MPI_Init(&argc, &argv);
  
  int rank, size;

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  printf("Hello World from rank %d of %d!\n", rank, size);

  //All MPI programs must end with a finalize
  MPI_Finalize();
}
