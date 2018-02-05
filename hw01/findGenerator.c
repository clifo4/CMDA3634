
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void main() {
  int fir;

  printf("Enter a prime number: ");
  scanf("%d", &fir);
  for(int i = 1; i < fir-1; i++) {
    int i2 = 1;
    short iDiv = 1;
    for(int j = 1; j < fir-1; j++) {
      i2 *= i;
      if(i2 % fir == 1) {
        iDiv = 0;
        break;
      }
    }
    if(iDiv) {
      printf("%d is a generator of %d.\n", i, fir);
      return;
    }
  }
  printf("There are no generators of %d.\n", fir);
}
