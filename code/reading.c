#include<stdio.h>
#include<stdlib.h>

void main() {
	FILE* file = fopen("data.txt", "r");

	int n;

	fscanf(file, "%d", &n);
	
	//allocate space for data
	int *data = (int*) malloc(n*sizeof(int));
	for(int m = 0; m < n; m++) {
		fscanf(file, "%d", data+m);
	}
	fclose(file);	
	for(int m = 0; m < n;m++) {
		printf("data[%d] = %d\n", m, data[m]);
	}
	free(data);
}
