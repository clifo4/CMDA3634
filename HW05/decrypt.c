#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"


int main (int argc, char **argv) {

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
    double startTime = clock();
    for (unsigned int i=0;i<p-1;i++) {
      if (modExp(g,i+1,p)==h) {
        printf("Secret key found! x = %u \n", i+1);
        x=i+1;
      } 
    }
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
  return 0;
}
