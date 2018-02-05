#include<stdio.h>
#include<stdlib.h>
#include<math.h>


void main() {
	int N;
	printf("Enter an upper bound");
	scanf("%d", &N);

	//storage for flags
	int* isPrime = (int*) malloc(N*sizeof(int));
	for(int n=0; n<N; n++) {
		isPrime[n] =1;
	}
	
	int sqrtN = (int) sqrt(N);
	
	for(int i = 2; i<sqrtN; i++) {
		if(isPrime[i]) {
			for(int j=i*i; j<N; j++) {
				isPrime[j] = 0;
			}
		}
	}

	//count the number of primes we found
	int count = 0;
	for(int n=0; n<N; n++) {
		if(isPrime[n]) {
			count++;
		}
	}

	//make a list of them
	int *primes = (int*) malloc(count*sizeof(int));
	count = 0;
	for(int n=0; n<N; n++) {
		if(isPrime[n]) {
			primes[count++] = n;
		}
	}
	//print the primes
	for(int n=0; n<count; n++) {
		printf("The %d-th prime is %d\n", n, primes[n]);
	}
}
