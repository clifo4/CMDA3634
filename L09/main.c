#include "mympi.h"


int main (int argc, char **argv) {

  MPI_Init(&argc,&argv);

  int rank,size;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  int N;

  if (rank==0) N=199;

  //myMPI_Bcast(&N,0);
  treeMPI_Bcast(&N);
  printf("Rank %d recieved the value N = %d\n",rank,N);

  if (rank==size-1) N=10;

  myMPI_Bcast(&N,size-1);
  printf("Rank %d recieved the value N = %d\n",rank,N);

  myMPI_Barrier();

  float val = 1.0;

  float sum = mpiReduction(val);

  printf("Rank %d has value %f after reduction.\n", rank, sum);

  MPI_Finalize();
  return 0;
}
