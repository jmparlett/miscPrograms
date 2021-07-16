#include <unistd.h>

#define NALLOC 1024 /* min membytes to request from OS */

typedef long Align; /* instance of most restrictive type (long is arbitrary) to be used as
		       a member of a union (each block). This ensures that each block is able
		       to store the most restrictive type */

union header { /* base block object */
	
	struct {
		
		union header *ptr; /* points to next free block */

		unsigned size; /* size of this block */
	} s;

	Align x; /* the alignment member will never be used */
};

typedef union header Header; /* recall that this syntax lets us shortcut creation of structs
				of this type to just "Header" */


static Header base; /* first node */

static Header *freep = NULL; /* start of list of free nodes */

/* request mem from OS */
static Header *morecore(unsigned nu)
{
	char *cp, *sbrk(int);

	void free(void *);
	
	Header *up;

	if(nu < NALLOC) nu = NALLOC; /* dont request less then NALLOC bytes */

	cp = sbrk(nu * sizeof(Header)); /* cast return val to char so we can compare to check for failure */

	if(cp == (char *) -1) return NULL; /* request failed. No free space */

	up = (Header *) cp;

	up->s.size = nu;

	free((void *)(up +1)); /* scan free list for place to insert new block */

	return freep; /* return pointer to free block */
}

/* general purpose storage allocator */
static void *malloc(unsigned nbytes)
{
	Header *p, *prevp;

	unsigned nunits;

	nunits = (nbytes + sizeof(Header)-1/sizeof(Header)+1); /* how many units of sizeof(Header) 
								 bytes to allocate*/

	if((prevp = freep) == NULL){ /* no free list yet exists */
		
		base.s.ptr = freep = prevp = &base;

		base.s.size = 0; /* no units allocated */
	}

	for(p = prevp->s.ptr; ;prevp = p, p = p->s.ptr){ /* crawl through list until a block big enough is found */

		if(p->s.size >= nunits){ /* block is large enough */
			
			if(p->s.size == nunits) /* block is exactly large enough. Allocate whole block */

				prevp->s.ptr = p->s.ptr; /* basically remove a node from a linked list */

			else{ /* allocate tail by jumping pointer by (blocksize -nunits) */
	
				p->s.size -= nunits;

				p+= p->s.size;

				p->s.size = nunits;				
			}

			freep = prevp; /*change free list start node */

			return (void *)(p+1);
		}
	}

		if(p == freep) /* we've wrapped around list. Attemp to request more mem */

			if((p = morecore(nunits)) = NULL) return NULL; /* mem request failed */
}


/* point new block in free list */
void free(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap -1; /* point to block header */

	for(p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) /* traverse list until you find two points between
								    which bp can fit */
		if(p >= p->s.ptr && (bp > p || bp < p->s.ptr)) break; /* weve wrapped around list and bp 
									 is before start or at end */
	if(bp + bp->s.size == p->s.ptr){ /* bp precedes begining of list */

		bp->s.size += p->s.ptr->s.size;

		bp->s.ptr = p->s.ptr->s.ptr; /* bp is now start of free list */
	} else {

		bp->s.ptr = p->s.ptr;
	}

	if(p + p->s.size == bp) { /* bp at end of list */

		p->s.size += bp->s.size;

		p->s.ptr = bp->s.ptr; /* extend end of list */
	} else { /* bp between two elements */

		p->s.ptr = bp;
	
		freep = p;
	}

	
}


