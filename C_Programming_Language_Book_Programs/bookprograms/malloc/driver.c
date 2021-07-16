#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/* return a pointer to n objects of size n. If returns p then p is first obj size n, p+1 is 2nd obj, p+n-1 
   is nth obj. Storage is zeroed before return. */
void *mycalloc(unsigned n, unsigned size)
{
	/* create pointer that points to n locations */
	/* each location gets n memory */
	
	void **p = (void **)malloc(n);

	*p = malloc(size);	
	for(;n-- > 0;){
		if((*p = malloc(size)) == NULL) return NULL; /* if malloc failed */
		*p++ = NULL; /* zeroize */
	}
	return p;
}
int main()
{
	int *p = (int *)mycalloc(3, sizeof(int));

	p[0]=2;

	printf("p sub 0: %d\n", p[0]);

	return 0;
}
