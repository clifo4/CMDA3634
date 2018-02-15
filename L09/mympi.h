#include <stdio.h>
#include<stdlib.h> 
#include<math.h>
#include "mpi.h"

void myMPI_Bcast(int *N, int root);
void myMPI_Barrier();
void treeMPI_Bcast(int *N);
float mpiReduction(float val);
