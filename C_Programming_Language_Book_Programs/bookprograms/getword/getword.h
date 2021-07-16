#include "getch.h"
#include <ctype.h>
/* get words and stuff */


int getword(char *word, int lim)
{
	int c, getch(void);

	void ungetch(int);

	char *w = word;

	while(isspace(c = getch())); // skip spaces

	if( c != EOF) *w++ = c; //if there is a character it is our first c

	if(!isalpha(c) || c == '/' || c == '#' || c == '\"') {	
		*w = '\0'; 

		return c;
	}

	for(; --lim > 0; w++) /*iter through word till you reach a non alpha character  */

		if(!isalnum(*w = getch())){
			
			ungetch(*w);
	
			break;
		}	
	*w = '\0';

	return word[0];
}
