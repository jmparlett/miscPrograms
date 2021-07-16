#include "wordbst.h"

#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *);

void treeprint(struct tnode *);

void treeconvert(struct tnode *, struct tnode *);

int getword(char *, int);

/* count word frequency ... basically */

int main()
{
	struct tnode *root;

	char word[MAXWORD];

	root = NULL;

	while(getword(word, MAXWORD) != EOF)
		
		if(isalpha(word[0])) root = addtree(root, word);

	// after count print tree
	treeprint2(root);

	return 0;
}
