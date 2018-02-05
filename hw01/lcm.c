#include<stdio.h>
#include<stdlib.h>


void main() {
  int fir, sec;

  printf("Enter the first number: ");
  scanf("%d", &fir);
  printf("Enter the second number: ");
  scanf("%d", &sec);
  int mult = fir * sec;
  for(int i = mult; i >= fir && i >= sec; i--) {
    if(i % fir == 0 && i % sec == 0) {
      mult = i;
    }
  }
  printf("The least common multiple of %d and %d is %d.\n", fir, sec, mult);
}
