#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "cuda.h"
#include "functions.c"

__device__ unsigned int cumodprod(unsigned int a, unsigned int b, unsigned int p) {
  unsigned int za = a;
  unsigned int ab = 0;

  while (b > 0) {
    if (b%2 == 1) ab = (ab +  za) % p;
    za = (2 * za) % p;
    b /= 2;
  }
  return ab;
}

__device__ unsigned int cumodExp(unsigned int a, unsigned int b, unsigned int p) {
  unsigned int z = a;
  unsigned int aExpb = 1;

  while (b > 0) {
    if (b%2 == 1) aExpb = cumodprod(aExpb, z, p);
    z = cumodprod(z, z, p);
    b /= 2;
  }
  return aExpb;
}

__global__ void cuDecrypt(unsigned int p, unsigned int g, unsigned int h, unsigned int max, unsigned int *x) {
  int tid = threadIdx.x;
  int bid = blockIdx.x;
  int bSize = blockDim.x;
  int id = tid + bim*bSize + 1;
  int tSize = gridDim.x*bSize;
  __shared__ unsigned int *re = &0;
  while(id < max-tSize && re[0]==0) {
    if(modExp(g, id, p)) {
      re[0]=id;
      x[0] = id;
    }
    id+=tSize;
  }
}

int main (int argc, char **argv) {

  /* Part 2. Start this program by first copying the contents of the main function from 
     your completed decrypt.c main function. */


  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h, x;
  unsigned int Nints;

  //get the secret key from the user
  printf("Enter the secret key (0 if unknown): "); fflush(stdout);
  char stat = scanf("%u",&x);

  printf("Reading file.\n");

  /* Q3 Complete this function. Read in the public key data from public_key.txt
    and the cyphertexts from messages.txt. */
  
  char* keyFile = "public_key.txt";
  FILE *keys = fopen(keyFile, "r");
  fscanf(keys, "%u %u %u %u", &n, &p, &g, &h);
  fclose(keys);
  unsigned int *m, *a;
  char* enname = "message.txt";
  FILE *enfile = fopen(enname, "r");
  fscanf(enfile, "%u", &Nints);
  m=(unsigned int*)malloc(Nints*sizeof(int));
  a=(unsigned int*)malloc(Nints*sizeof(int));
  for(int i=0; i<Nints; i++) {
    fscanf(enfile, "%u %u", &m[i], &a[i]);
  }
  fclose(enfile);
  // find the secret key
  if (x==0 || modExp(g,x,p)!=h) {
    printf("Finding the secret key...\n");
    int max = 1;
    for(int i=0; i<n; i++) {max *=2}
    max = max-1;
    int nThreads = 32;
    int nBlocks = 10;
    unsigned int *d_x;
    cudaMemcpy(d_x, &0, 1, cudaMemcpyHostToDevice);
    double startTime = clock();
    
    cudecrypt <<< nThreads, nBlocks >>>(p, g, h, max, d_x);
    cudaDeviceSynchronize();

    double endTime = clock();

    double totalTime = (endTime-startTime)/CLOCKS_PER_SEC;
    double work = (double) p;
    double throughput = work/totalTime;

    printf("Searching all keys took %g seconds, throughput was %g values tested per second.\n", totalTime, throughput);
  }

  /* Q3 After finding the secret key, decrypt the message */
  ElGamalDecrypt(m, a, Nints, p, x);
  int charsperint = n%9;
  int chars = charsperint*Nints;
  char* message = (char*)malloc(chars*sizeof(char)+2);
  convertZToString(m, Nints, message, chars);
  printf("%s\n", message);
  free(message);
  free(m);
  free(a);
  /* Q4 Make the search for the secret key parallel on the GPU using CUDA. */

  return 0;
}
