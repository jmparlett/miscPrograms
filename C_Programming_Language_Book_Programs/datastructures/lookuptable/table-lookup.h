#include "strdup.h"



/* 
a look up table is basically what is used for replacements with #defines. It is a hash table useing linked lists
each node contains the name, the value to replace the name, and a pointer to the next list element 
*/


#define HASHSIZE 101

char *strdup(char *); /* uses malloc to make return a char pointer big enough for the given string */


struct nlist /* hashtable node */
{
	struct nlist *next;

	char *name;

	char *defn;
}; 

static struct nlist *hashtab[HASHSIZE]; /* table of nodes */

unsigned hash(char *s){ /* hash function for indexing into our table */
	
	unsigned hashval=0;

	for(hashval; *s; s++) hashval = *s + 31 * hashval;

	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s){ /* find and return a target node or NULL if it is not in the list */

	struct nlist *np;

	for(np = hashtab[hash(s)]; np != NULL; np = np->next)

		if(strcmp(s, np->name) == 0) return np; /* found */
	
	return NULL; /* return in for never reach so return NULL/not found */
}

struct nlist *install(char *name, char *defn){ /* add a new name, or replace a names defn */

	struct nlist *np;

	unsigned hashval; 

	if((np = lookup(name)) == NULL){ /* its not in the table */
		
		np = (struct nlist *) malloc(sizeof(*np));
	
		if(np == NULL || ((np->name = strdup(name)) == NULL)) return NULL; /* if malloc fails stop */

		hashval = hash(name);

		np->next = hashtab[hashval]; /* prepend our new name */

		hashtab[hashval] = np;
	} else { /* already there then overwrite it */
		
		free((void *) np->defn);

	if((np->defn = strdup(defn)) == NULL) return NULL; /* if malloc fails... -_- */

	else return np;
	}
}

struct nlist *undef(char *name){ /* attemp to remove a defined name always returns NULL */
		
	struct nlist *np;	
		
	unsigned hashval;
	
	if((np=lookup(name)) == NULL) return NULL; /* its not in table */

	else {

		hashval = hash(name);
	
		hashtab[hashval] = np->next;

		free((void*) np);

		return np;
	}	
}
