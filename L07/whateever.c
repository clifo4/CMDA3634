
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

  if(rank ==0) {
    int N = 10;
    int destRank = 1;
    int tag = 1;
    MPI_Request reqs[2];
    MPI_Status status[2];

    int *sendData = (int *) malloc(N*sizeof(int));

    for(int i =0; i<N; i++) {sendData[i] = 2*i}

    MPI_ISend(&N, //pointer to data we're sending 
      1,        //number of entries to send
      MPI_INT, //data type of eash entry
      destRank, //rank of destination
      tag,     //tags the message with an identifier
      MPI_COMM_WORLD,//flag the full MPI network
      reqs);//flag the full MPI network
    tag = 2;
    MPI_ISend(&sendData, //pointer to data we're sending 
      N,        //number of entries to send
      MPI_INT, //data type of eash entry
      destRank, //rank of destination
      tag,     //tags the message with an identifier
      MPI_COMM_WORLD,//flag the full MPI network
      reqs+1);//flag the full MPI network
    MPI_Wait(reqs, status);
    MPI_Wait(reqs+1, status+1);
  } else if(rank == 1) {
    int N;
    int sourceRank = 0;
    int tag=1;
    MPI_Request reqs[2];
    MPI_Status status[2];
    MPI_IRecv(&N,
        1,
        MPI_INT,
        sourceRank,
        tag,
        MPI_COMM_WORLD,
        reqs);
    MPI_Wait(reqs, status);
    tag=2;
    int*recvData = (int *) malloc(N*sizzeof(int));
    MPI_IRecv(&recvData,
        N,
        MPI_INT,
        sourceRank,
        tag,
        MPI_COMM_WORLD,
        reqs+1);
    MPI_Wait(reqs+1, status+1);
    for(int i = 0; i<N;i++) {printf("Rank %d recieved an message from %d: value = %d\n", rank, sourceRank, recData[i]);}
  }
  //All MPI programs must end with a finalize
  MPI_Finalize();
}
