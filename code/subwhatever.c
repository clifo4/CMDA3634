#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct {
	float x, y, z;
} point;

void printPoint(point);
void pointSetZero(point*);
float pointDistanceToOrigin(point);

void main() {
	point p;
	//access variables directly with '.'
	p.x = 1.0;
	p.y = 2.0;
	p.z = 3.0;
	
	float dist;

	dist = pointDistanceToOrigin(p);
	printf("dist = %f", dist);	
	pointSetZero(&p);
	
	printPoint(p);
}

void printPoint(point p) {
	printf("Point has coordinates (%f, %f, %f)\n", p.x, p.y, p.z);
}

void pointSetZero(point* p) {
	//(*p).x = 0.0;
	//(*p).y = 0.0;
	//(*p).z = 0.0;
	p->x = 0.0;
	p->y = 0.0;
	p->z = 0.0;
}

float pointDistanceToOrigin(point p) {
	float dist = sqrt(p.x*p.x+p.y*p.y+p.z*p.z);
	return dist;
}
