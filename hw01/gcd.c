#include<stdio.h>
#include<stdlib.h>


void main() {
  int fir, sec;

  printf("Enter the first number: ");
  scanf("%d", &fir);
  printf("Enter the second number: ");
  scanf("%d", &sec);
  int div = 0;
  for(int i = 1; i <= fir && i <= sec; i++) {
    if(fir % i == 0 && sec % i == 0) {
      div = i;
    }
  }
  printf("The greatest common divisor of %d and %d is %d.\n", fir, sec, div);
}
