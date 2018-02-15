#include<mympi.h>


//compute the global sum of all the values in val across all MPI ranks
float mpiReduction(float val) {
  
  float sum = val;
  float recvBuff;
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int Nactive = size;

  while(Nactive > 1) {
    if(rank >= (Nactive+1)/2) {
      //MPI_Send
      int destRank = rank - (Nactive+1)/2;

      int tag = Nactive;

      MPI_Send(&sum,
                1,
                MPI_FLOAT,
                destRank,
                tag,
                MPI_COMM_WORLD);
    }
    if(rank < (Nactive+1)/2) {
      //MPI_Recv
      int sourceRank = rank + (Nactive+1)/2;
      int tag = Nactive;
      MPI_Status status;

      MPI_Recv(&recvBuff,
                1,
                MPI_FLOAT,
                sourceRank,
                tag,
                MPI_COMM_WORLD,
                &status);
      
      sum += recvBuff;
    }

    Nactive = (Nactive +1) / 2;
  }
  return sum;
}
