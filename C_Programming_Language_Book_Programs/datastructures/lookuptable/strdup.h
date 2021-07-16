#include <string.h>
#include <stdlib.h>

/* stdrup block begin */
char *strdup(char *s){

	char *p;

	p = (char *) malloc(strlen(s)+1); // +1 accounts for null	

	if(p != NULL) strcpy(p, s); // NULL is malloc failure signal

	return p;
}
