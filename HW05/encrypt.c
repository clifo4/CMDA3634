#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "functions.h"

int main (int argc, char **argv) {

	//seed value for the randomizer 
  double seed = clock(); //this will make your program run differently everytime
  //double seed = 0; //uncomment this and your program will behave the same everytime it's run

  srand(seed);

  int bufferSize = 1024;
  unsigned char *message = (unsigned char *) malloc(bufferSize*sizeof(unsigned char));

  printf("Enter a message to encrypt: ");
  int stat = scanf (" %[^\n]%*c", message); //reads in a full line from terminal, including spaces

  //declare storage for an ElGamal cryptosytem
  unsigned int n, p, g, h;

  printf("Reading file.\n");

  /* Q2 Complete this function. Read in the public key data from public_key.txt,
    convert the string to elements of Z_p, encrypt them, and write the cyphertexts to 
    message.txt */
  unsigned int count = 0;
  for(count; message[count]!='\0'; count ++);
  char* keyFile = "public_key.txt";
  FILE *keys = fopen(keyFile, "r");
  fscanf(keys, "%u %u %u %u", &n, &p, &g, &h);
  unsigned int charsperint = n%9;
  padString(message, charsperint);
  unsigned int ints = count/charsperint;
  //printf("Inputs: %s %u %u %u\n", message, count, charsperint, ints);
  unsigned int* z = (unsigned int*)malloc(ints*sizeof(int));
  convertStringToZ(message, count, z, ints);
  unsigned int *a = (unsigned int*)malloc(ints*sizeof(int));
  ElGamalEncrypt(z, a, ints, p, g, h);
  fclose(keys);
  char* outname = "message.txt";
  FILE *outp = fopen(outname, "w+");
  char* outs = (char*)malloc(25*sizeof(char));
  sprintf(outs, "%u\n", ints);
  fputs(outs, outp);
  for(int i=0; i<ints; i++) {
    sprintf(outs, "%u %u\n", z[i], a[i]);
    fputs(outs, outp);
  }
  fclose(outp);
  free(z);
  free(a);
  free(message);
  free(outs);
  
  return 0;
}
