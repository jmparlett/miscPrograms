#define BUFSIZE 100


char buf[BUFSIZE];

int bufp = 0;

int getch(void){
	return ((bufp > 0) ? buf[--bufp] : getchar()); /* return a buffered character or get a new one */
}

void ungetch(int c){
	if(bufp	>= BUFSIZE) printf("ungetch: too many character\n"); 
	else buf[bufp++] = c;
}
