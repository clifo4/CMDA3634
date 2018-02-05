
#include<stdio.h>
#include<stdlib.h>


void main() {
  int fir, sec;

  printf("Enter the first number: ");
  scanf("%d", &fir);
  printf("Enter the second number: ");
  scanf("%d", &sec);
  //int div = 0;
  for(int i = 1; i <= fir && i <= sec; i++) {
    if(fir % i == 0 && sec % i == 0 && i> 1) {
      printf("%d and %d are not coprime.\n", fir, sec);
      return;
    }
  }
  printf("%d and %d are coprime.\n", fir, sec);
}
