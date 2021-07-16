#include "clangBook.h"
#include "alloc.h"


#define MAXLINES 5000 // max lines to sort
#define MAXLEN 1000 // max length of line

char *lineptr[MAXLINES]; //array of character pointers for each line


int readlines(char *lineptr[], int nlines);

void writelines(char *lineptr[], int nlines);


void qsort(char *lineptr[], int left, int right);

int main()
{
	int nlines;

	if((nlines = readlines(lineptr, MAXLINES))>= 0){
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input to big to sort\n");
		return -1;
	}
}

int getLine(char s[], int lim);
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

void writelines(char *lineptr[], int nlines){
	int i;
	
	for(i =0; i < nlines; i++) printf("%s\n", lineptr[i]);

}

