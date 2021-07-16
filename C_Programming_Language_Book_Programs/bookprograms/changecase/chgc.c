/* change case to upper or lower based on argv[0] */
#include <stdio.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char *argv[])
{	
	printf("argv[0] == %s\n", argv[0]);
	int c;

	if(strcmp(argv[0], "lower") == 0 || strcmp(argv[0], "./lower") == 0){ 
		while((c = getchar()) != EOF) putchar(tolower(c)); 
	} else { /* upper case whats lower */
		while((c = getchar()) != EOF) putchar(toupper(c)); 
	}

}
