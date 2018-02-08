#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>

void myMPI_Bcast(int* n, int r);

int main(int argc, char **argv) {
  MPI_Init(&argc,&argv);
  
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int N;
  if(rank == 0) N=199;
  
  myMPI_Bcast(&N,0);

  printf("Rank %d recieved the value N= %d\n", rank, N);

  if(rank == size-1) N=10;

  myMPI_Bcast(&N, size-1);

  printf("Rank %d recieved the value N= %d\n", rank, N);

  MPI_Finalize();
  return 0;
}

void myMPI_Bcast(int *n, int r) {

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if(rank != r) {
    MPI_Status status;
    int tag = 1;
    int sourceRank = (size+rank-1)%size;
    
    MPI_Recv(n,
          1,
          MPI_INT,
          sourceRank,
          tag,
          MPI_COMM_WORLD,
          &status);
  }
  if(rank != (size+r-1)%size) {
    int tag = 1;
    int dest = (rank+1)%size;
    MPI_Send(n,
            1,
            MPI_INT,
            dest,
            tag,
            MPI_COMM_WORLD);
  }
}
