#include "mympi.h"

int main (int argc, char **argv) {

  MPI_Init(&argc,&argv);

  int rank,size;
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);

  int N;

  if (rank==0) N=199;

  //myMPI_Bcast(&N,0);
  MPI_Bcast(&N,
            1,
            MPI_INT,
            0,
            MPI_COMM_WORLD);
  printf("Rank %d recieved the value N = %d\n",rank,N);

  if (rank==size-1) N=10;

  MPI_Bcast(&N,
            1,
            MPI_INT,
            size-1,
            MPI_COMM_WORLD);
  printf("Rank %d recieved the value N = %d\n",rank,N);
  /*MPI Barrier*/
  MPI_Barrier(MPI_COMM_WORLD);

  //setup a test for the reduction
  float val = 1.0;
  float sum;
  /*MPI Reduction*/
  MPI_Reduce(&val,      //send buffer
            &sum,       //recieve buffer
            1,          //count
            MPI_FLOAT,    //type
            MPI_SUM,
            0,
            MPI_COMM_WORLD);
  
  for (int r=0;r<size;r++) {
    if (r==rank) {
      printf("Rank %d has value %f after the reduction.\n", rank, sum);
    }
    myMPI_Barrier(); 
  }
  /*MPI reduction + broadcast*/
  //This performs the reduction so all ranks have the final value
  MPI_Allreduce(&val,
                &sum,
                1,
                MPI_FLOAT,
                MPI_SUM,
                MPI_COMM_WORLD);

  for (int r=0;r<size;r++) {
    if (r==rank) {
      printf("Rank %d has value %f after the reduction.\n", rank, sum);
    }
    myMPI_Barrier(); 
  }

  val = (float) rank;
  float *gval;
  
  if(rank ==0) {gval = (float*) malloc(size*sizeof(float));}

  MPI_Gather(&val,        //send buffer
            1,            //send count
            MPI_FLOAT,    //send type
            gval,         //recieve buffer
            1,            //recieve amount
            MPI_FLOAT,    //recieve type
            0,            //root process
            MPI_COMM_WORLD);

  if(rank ==0) {
    for(int r=0; r<size; r++) {
      printf("gval[%d] = %f\n", r, gval[r]);
      gval[r] *= 2;
    }
  }
  
  MPI_Scatter(gval,
              1,
              MPI_FLOAT,
              &val,
              1,
              MPI_FLOAT,
              0,
              MPI_COMM_WORLD);
  printf("Rank %d has value %f after scatter.\n", rank, val);
  
  
  
  MPI_Finalize();
  return 0;
}
