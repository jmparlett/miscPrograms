#include <stdio.h>
#include <stdlib.h>



int main ()
{
/*
int *day = (int *) malloc(sizeof(int)); int year; 
char * monthname; monthname = (char *) malloc(20);
printf("sizeofmonthname: %u\n", sizeof(monthname));
scanf("%d %s %d", day, monthname, &year);
printf("int:%d str:%s int:%d\n",day, monthname, year);
*/


int c;

/*
FILE *fp = fopen("CS172Final.py", "a");
while((c=getchar()) != '\n') putc(c, fp);
fp = fopen("CS172Final.py", "r");
while((c=getc(fp)) != EOF) putchar(c);
*/

	while(1){
		
		while((c=getc(stdin)) != EOF || c != '\n') putc(c, stdout);
	
	}

}
