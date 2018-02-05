
#include<stdio.h>
#include<stdlib.h>


void main() {
  int fir, sec;

  printf("Enter a number: ");
  scanf("%d", &fir);
  for(int i = 2; i*i <= fir; i++) {
    if(fir % i == 0) {
      printf("%d is not prime.\n", fir);
      return;
    }
  }
  printf("%d is prime.\n", fir);
}
