#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<cuda.h>


__global__ void reduction(float N,float* d_a, float* result) {
  int tid = threadIdx.x;
  int bid = blockIdx.x;
  int bSize = blockDim.x;
  int id = tid + bid*bSize;

  __shared__ float s_sum[256];
  if(id<N) {
  s_sum[tid] = a[id];
  } else {
    s_sum[tid]=0;
  }
  __syncthreads();


  if(tid<128) {
    s_sum[tid] += s_sum[tid+128];
  }
  
  __syncthreads();

  if(tid<64) {
    s_sum[tid] += s_sum[tid+64];
  }
  
  __syncthreads();
  if(tid<32) {
    s_sum[tid] += s_sum[tid+32];
  }
  
  __syncthreads();
  if(tid<16) {
    s_sum[tid] += s_sum[tid+16];
  }
  
  __syncthreads();

  if(tid<8) {
    s_sum[tid] += s_sum[tid+8];
  }
  
  __syncthreads();
  if(tid<4) {
    s_sum[tid] += s_sum[tid+4];
  }
  
  __syncthreads();

  if(tid<2) {
    s_sum[tid] += s_sum[tid+2];
  }
  
  __syncthreads();
  if(tid<1) {
    s_sum[tid] += s_sum[tid+1];
    result[bid] = s_sum[tid];
  }
  /*
  if(id<N) {
    *result += d_a[id];
  }*/
}

//perform a reduction of vector length N
int main(int argc, char** argv) {
  int N = atoi(argv[1]);
  double seed = 0;
  srand48(seed);

  float* h_a = (float*) malloc(N*sizeof(float));

  //populate array with randoms
  for(int n=0; n<N; n++) {
    h_a[n] = drand48();
  }
  float h_sum = 0.;
  for(int n=0; n<N; n++) {
    h_sum += h_a[n];
  }

  printf("The host sum was %f \n", h_sum);

  float *d_a, *d_sum;

  int Nnew = (N+256-1)/256;


  cudaMalloc(%d_a, N*sizeof(float));
  cudaMalloc(%d_sum, Nnew*sizeof(float));

  float *h_nSum = (float*) malloc(Nnew*sizeof(float));
  
  cudamMemcpy(d_a, h_a, N*sizeof(float), cudaMemcpyHostToDevice);
  
  do{
    
    Nnew = (N+256-1)/256;
    dim3 B(256, 1, 1);
    dim3 G(Nnew, 1, 1);

    reduction <<< G, B >>> (N, d_a, d_sum);
    
    cudaMemcp(d_a, d_sum, Nnew*sizeof(float), cudaMemcpyDeviceToDevice);

    n = Nnew;
  } while(Nnew>1); 
  cudaMemcpy(h_nSum, d_sum, Nnew*sizeof(float), cudaMemcpyDeviceToHost);

  printf("The device sum was %f \n", *h_nSum);
  return 0;
}
