#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<cuda.h>

//device function
__global__ void kernelAddMatrices1D(int N, double *A, double *B, double *C) {
  int threadId = threadIdx.x;
  int blockId = blockIdx.x;
  int blockSize = blockDim.x;

  int id = thread + blockId*blockSize;

  C[id] = A[id] + B[id];
}

__global__ void kernelAddMatrices2D(int N, double *A, double *B, double *C) {
  int tIdx = threadIdx.x;
  int tIdy = threadIdx.y;
  int bIdx = blockIdx.x;
  int bIdy = blockIdx.y;

  int bSizex = blockDim.x;
  int bSizey = blockDim.y;

  int i= tIdx + bIdx*bSizex;
  int j= tIdy + bIdy*bSizey;
  
  nx = 1024;

  C[i+j*nx] = A[i+j*nx] + B[i+j*nx];

}

__global__ void kernelMatrixTranspose2D_v1(double *A, double *At) {
  
  int tIdx = threadIdx.x;
  int tIdy = threadIdx.y;
  int bIdx = blockIdx.x;
  int bIdy = blockIdx.y;

  int bSizex = blockDim.x;
  int bSizey = blockDim.y;


  int i= tIdx + bIdx*bSizex;
  int j= tIdy + bIdy*bSizey;
  
  nx = 1024;

  At[i+j*nx] = A[j+i*nx];
}


__global__ void kernelMatrixTranspose2D_v2(double *A, double *At) {
  
  int tIdx = threadIdx.x;
  int tIdy = threadIdx.y;
  int bIdx = blockIdx.x;
  int bIdy = blockIdx.y;

  int bSizex = blockDim.x;
  int bSizey = blockDim.y;

  __shared__ double s_A[32][32];

  int i= tIdx + bIdx*bSizex;
  int j= tIdy + bIdy*bSizey;
  
  nx = 1024;
  //fetch a block of A into shared array
  s_A[tIdx][tIdy] = A[i+j*nx]; //read from A and write the block's transpose
  
  __syncthreads(); //barrier the threads on this block
  
  At[i+j*nx] = s_A[tIdy][tIdx];
}

int main(int argc, char** argv){
  int nx = 1024;
  int ny = 1024;

  int N = nx*ny;

  double seed = clock();
  srand48(seed);

  double *h_a, *h_b, *h_c;
  h_a= (double*) malloc(N*sizeof(double));
  h_b= (double*) malloc(N*sizeof(double));
  h_c= (double*) malloc(N*sizeof(double));
  
  for(int n=0; n<N; n++) {
    h_a[n] = drand48();
    h_b[n] = drand48();
  }

  double hostStart = clock();

  for(int j=0; j<ny; j++) {
    for(int i=0; i<nx; i++) {
      h_c[j*ny+i] = h_a[j*ny+i] + h_b[j*ny+i];
    }
  }

  double hostEnd = clock();

  double hostTime = (hostEnd-hostStart)/(double)CLOCKS_PER_SEC;
  size_t inputMem = 2*N*sizeof(double);
  size_t outputMem = 1*N*sizeof(double);
  size_t totalMem_GB = (inputMem + outputMem)/0x20000000;
  printf("The host took %f seconds to computer\n", hostTime)
  
  //Device arrays
  double *d_a, *d_b, *d_c;
  cudaMalloc(&d_a, N*sizeof(double));
  cudaMalloc(&d_b, N*sizeof(double));
  cudaMalloc(&d_c, N*sizeof(double));

  double copyStart = clock();
  cudaMemcpy(d_a, //destination
              h_a,  //source
              N*sizeof(double), //size 
              cudaMemcpyHostToDevice);  //Command
  cudaMemcpy(d_b,h_b,N*sizeof(double), cudaMemcpyHostToDevice);
  cudaMemcpy(d_c,h_c,N*sizeof(double), cudaMemcpyHostToDevice);
  double copyEnd = clock();
  double copyTime = (copyEnd - copyStart)/(double) CLOCKS_PER_SEC;
  printf("Copying took %f seconds", copyTime);

  
  int nThreads = 32;
  int nBlocks = (N+nThreads-1)/nThreads;
  
  double deviceStart = clock();

  kernellAddVectors <<< nBlocks,nThreads >>>(d_a, d_b, d_c, N);
  
  cudaDeviceSynchronize();

  double deviceEnd = clock();
  double deviceTime = (deviceEnd - deviceStart)/(double) CLOCKS_PER_SEC;

  printf("The device took %f seconds", deviceTime);

  //use 2D thread blocks instead
  int Nthreadsx = 32;
  int Nthreadsy = 32;
  int Nthreadsz = 1;
  
  //declare size of block
  //Nthreadsx*Nthreadsy*Nthreadsz <= 1024
  dim3 Nthreads3(Nthreadsx, Nthreadsy, Nthreadsz);
  
  int Nblocksx = (nx+Nthreadsx-1)/Nthreasdsx;
  int Nblocksy = (ny+Nthreadsy-1)/Nthreasdsy;
  int Nblocksz = 1;
  dim3 Nblocks3(Nblocksx, Nblocksy, Nblocksz);
  kernel AddMatrices2D <<< Nblocks, Nthreads3 >>> (N, d_a, d_b, d_c);

  cudaDeviceSynchronize();



  kernelMatrixTranspose2d_v1 <<< Nblocks3, Nthreads3 >>>(d_a, d_c);

  cudaDeviceSynchronize();





  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);

  free(h_a);
  free(h_b);
  free(h_c);
}
