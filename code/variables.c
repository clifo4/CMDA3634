#include<stdio.h>
#include <stdlib.h>
void main() {
	int a,b, c; //Allocates an integer called 'a'
	int* pt_a,* pt_b;//Allocated a pointer, called 'pt_a', to an integer
	
	
	a=3;
	b = 4;
	pt_a = &a;//stores not the value of a, but its location
	pt_b = &b;

	c = *(pt_a+1);

	printf("The size of an int is %ld\n", sizeof(int));
	printf("a is located at %p\n", pt_a);
	printf("b is located at %p\n", pt_b);
	printf("a = %d\n", a);
	printf("b = %d\n", b);
	printf("c = %d\n", c);
	printf("a+b = %d\n", a+b);
	printf("a-b = %d\n", a-b);
	printf("a*b = %d\n", a*b);
	printf("a/b = %d\n", a/b);
	printf("a mod b = %d\n", a%b);

	int * array;

	int alsoArray[10]; //also allocates an array of size 10

	array = (int*) malloc(10*sizeof(int)); //Allocates an Array of size 10

	int n = 0;

	for(n = 0; n<10; n++) {
		if(n == 3) {
			continue;
		} else {
			printf("Not 3");
		}
		array[n]=n;
	}

	n = 0;
	while(n < 10) {
		printf("a[%d] = %d\n", n, array[n]);
		n++;
		if(n == 8) {
			break;
		}
	}


	/*More data types*/
	float fa; //32-bit floating point number
	double da; //64 bit floating point number

	char ch_a; // single character
	char *string; //string (Array of characters)

	unsigned int ui; //unsigned integer
	long lint; //64-bit integer
















}
