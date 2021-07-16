#include <stdio.h> 
#include <limits.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXLINE 1000
#define MAXLINES 5000

struct point {
		int x;
	
		int y;
	};

struct rect {
	
	struct point pt1;

	struct point pt2;

};


struct point makepoint(int x, int y){
		
		struct point t = {x, y};

		return t;
	}

struct point addpoint(struct point p1, struct point p2){
	return makepoint(p1.x + p2.x, p1.y + p2.y);
}

struct key {
	char *word;

	int count;

} keytab[] = {
	
	{"auto", 0},

	{"break", 0},

	{"for", 0},

	{"while", 0},

	{"do", 0}

	};

#define NKEYS (sizeof(keytab) / sizeof(keytab[0]))

int main()
{
	
	struct point p = {400,500};

	printf("p is the point (%d, %d)\n", p.x, p.y);

	double dist, sqrt(double);

	dist = sqrt((double)p.x * p.x + (double)p.y * p.y);
	
	printf("dist from p to origin: %lf\n", dist);
		
	struct point test = makepoint(33, 86);
	printf("test point: (%d, %d)\n", test.x, test.y);

	struct rect screen = {makepoint(0,0), makepoint(30,30)};
		
	char *s = "7bytes999", *e = "8bytessbullshitgo";

	printf("size of s: %lu, size of e: %lu\n", sizeof(s), sizeof(e));
	
	printf("should be 5. size: %lu\n", NKEYS);
	return 0;
}
