#include "gettoken.h"

void dirdcl(void); // proto dec so dcl can call its sibling

void dcl(void)
{
	int ns=0;

	for(ns; gettoken() == '*'; ns++); //count *s

	dirdcl();

	while(ns-- > 0) strcat(out, "pointer to");
}


void dirdcl(void)
{
	int type;

	if (tokentype == '('){
		
		dcl();

		if(tokentype != ')') printf("error: missing )\n");

	} else if(tokentype == NAME) {
		
		strcpy(name, token);

	} else {

		printf("error: expected name or (dcl)\n");
	}
	
	while((type = gettoken()) == PARENS || type == BRACKETS)
		
		if (type == PARENS) strcat(out, "function returning");
		
		else {
			strcat(out, " array");

			strcat(out, token);

			strcat(out, " of");
		}
}


