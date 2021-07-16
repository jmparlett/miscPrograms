#include "bookheader.h"
#include "alloc.h"
#include "stdlib.h"

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES]; //array of character pointers for each line

int readlines(char *lineptr[], int nlines);

void writelines(char *lineptr[], int nlines, int n);


int main(int argc, char *argv[])
{
	int n = 10;

	if((*++argv)[1] == 'n') n = atoi((*++argv));

		
	int nlines;

	if((nlines = readlines(lineptr, MAXLINES))>= 0){
		writelines(lineptr, nlines, n);
		return 0;
	} else {
		printf("error: input to big to parse\n");
		return -1;
	}

		

}

int getLine(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines){
	int len, nlines=0;
	
	char *p, line[MAXLEN];
	
	while((len=getLine(line, MAXLEN)) > 1){
		if(nlines >= maxlines || (p = alloc(len)) == NULL) return -1;

		else{
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			
		}
	}	return nlines;
		
}

void writelines(char *lineptr[], int nlines, int n){
	int i;
	
	for(i=(nlines-(n+1) > 0 ? nlines-(n+1) : 0); i < nlines; i++) printf("%s\n", lineptr[i]);

}

