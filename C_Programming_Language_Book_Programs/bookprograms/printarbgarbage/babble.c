#include <stdio.h>
#include <stdlib.h>
#include "pg.h"

#define MAXLINE 100

void itob(int , char [], int); /* converts number to base 2 or 16 based on arg 3 */


int main()
{
	int *linebuf;

	linebuf = (int *) malloc(sizeof(int)*MAXLINE);

	int c, i;

	while((i=getLine(linebuf, MAXLINE))){
		
		for(int j=0; j < i; j++){
			if(0 < linebuf[j] || linebuf[j] < ~(~0 << 8) && linebuf[j] != 255) printf("%c",linebuf[j]);
			linebuf[j] = '\0';
		}	
		printf("\n");
	}
}

