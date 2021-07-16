#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "getch.h"


#define MAXTOKEN 100
enum { NAME,
       PARENS,	
       BRACKETS};

void dcl(void);

void dirdcl(void);

int gettoken(void);

int tokentype; //type of last token duh

char token[MAXTOKEN]; // string of the last token

char name[MAXTOKEN]; //name/id of last token

char datatype[MAXTOKEN]; // datatype of last token... less duh

char out[1000]; // output string written to by dcl functions

int crashflag = 0; // used to exit dcl call early if given invalid input

int main()
{
	while(gettoken() != EOF) {
		
		strcpy(datatype, token);

		out[0] = '\0';

		dcl();

		if(tokentype != '\n' || crashflag){
			printf("syntax error\n");
			crashflag = 0;
			continue;
		}

		printf("%s: %s %s\n", name, out, datatype);
	}

	return 0;
}


/* begin dcl block */

int gettoken(void);

void dcl(void)
{
	int ns=0;

	for(ns; gettoken() == '*'; ns++); //count *s

	dirdcl();
	if(crashflag) return;

	while(ns-- > 0) strcat(out, " pointer to");
}


void dirdcl(void)
{
	int type;

	if (tokentype == '('){
		
		dcl();

		if(tokentype != ')'){
			 printf("error: missing )\n");
			 crashflag = 1;
			 return;
		}

	} else if(tokentype == NAME) {
		
		strcpy(name, token);

	} else {

		printf("error: expected name or (dcl)\n");
		crashflag = 1;
		return;
		
	}
	
	while((type = gettoken()) == PARENS || type == BRACKETS)
		
		if (type == PARENS){
			 strcat(out, " function taking args of type ");
			 while(gettoken() != ')'){
				if(tokentype == ',') strcat(out, ", ");
				else strcat(out, token);
			 }  
			 strcat(out, " returning");
		}
		
		else {
			strcat(out, " array");

			strcat(out, token);

			strcat(out, " of");
		}
}
/* end dcl block */

/* begin gettoken block */



int gettoken(void)
{
	int c, getch(void);
	
	void ungetch(int);

	char *p = token;

	while((c=getch()) == ' ' || c == '\t');


	if(c == '('){
		/* if((c = getch()) == ')') old if */

		if(tokentype == NAME || tokentype == ')' || tokentype == BRACKETS || tokentype == PARENS){
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';	
		}
	} else if( c == '['){

		for(*p++ = c; (*p++ = getch()) != ']';);

		*p = '\0';

		return tokentype = BRACKETS;

	} else if (isalpha(c)) {
		for(*p++ = c; isalnum(c = getch());) *p++ = c;
	
		*p = '\0';

		ungetch(c);

		return tokentype = NAME;
	} else {
		return tokentype = c;
	}


}
/*end getttoken block */
