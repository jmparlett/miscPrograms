#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "getword.h"
#include "sortlines.h"


struct tnode /* node for a BST containing words */
{
	char *word;	   // text of word

	int count; 	   // word count

	struct tnode *left; // left child

	struct tnode *right; // right child
};




/* talloc block begin */
struct tnode *talloc(void){
	return (struct tnode *) malloc(sizeof(struct tnode));
}
/* talloc block end */

/* stdrup block begin */
char *stdrup(char *s){

	char *p;

	p = (char *) malloc(strlen(s)+1); // +1 accounts for null	

	if(p != NULL) strcpy(p, s); // NULL is malloc failure signal

	return p;
}
/* stdrup block end */

/* treeprint block begin */
void treeprint(struct tnode *p){
	
	if(p != NULL){
		
		treeprint(p->left);
	
		printf("%4d %s\n", p->count, p->word);

		treeprint(p->right);
	}
}

/* treeprint block end */


/* addtree block begin */
struct tnode *addtree(struct tnode *p, char *w){
	
	int cond;

	if(p == NULL){ //create a new node
		
		p = talloc();

		p -> word = strdup(w);
		
		p -> count = 1;

		p -> left = p -> right = NULL;
	} else if((cond = strcmp(w, p->word)) == 0) p -> count++; //increment word count
	
	  else if(cond < 0) p = addtree(p->left, w); // move to left subtree 

	  else p-> right = addtree(p->right, w); // move right
	
	return p;
}
/* addtree block end */



/* gettreestrings block begin */
int nlines=0;
void gettreestrings(struct tnode *p){
	
	if(p != NULL){
		char s[MAXLEN];
		gettreestrings(p->left);
	
		sprintf(s, "%4d %s", p->count, p->word);
		
		lineptr[nlines++] = s;

		gettreestrings(p->right);
	}
}

void treeprint2(struct tnode *p){
	
	gettreestrings(p);
	
	qsort(lineptr, 0, nlines-1);

	writelines(lineptr, nlines);
}

