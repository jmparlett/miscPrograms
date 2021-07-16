#include "filestruct.h"
#include <fcntl.h>


#define PERMS 0666 /* RW for owner, group, others */


/* open a file and return a pointer to it. This is for demo only so perms are defaulted to 0666 */
FILE *fopen(char *name, char *mode)
{
	int fd;

	FILE *fp;

	if(*mode != 'r' && *mode != 'w' && *mode != 'a') return NULL; /* invalid perms */

	for(fp = _iob; fp < _iob +OPEN_MAX; fp++)
		
		if((fp->flag &(_READ | _WRITE)) == 0)
			 break; /* if no flags on file obj in array then it is an empty slot */			

	if(fp >= _iob + OPEN_MAX) return NULL;/* no free slots */	


	/* check desired perms creat obj accordingly */	
	if(*mode == 'w') fd = creat(name, PERMS); 
	
	else if(*mode == 'a'){ /* if file doesnt exist create an empty one and return the file descriptor
				  if it does move to end of file with lseek and return descriptor */
		
		if((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else fd = open(name, O_RDONLY, 0);


	if(fd == -1) return NULL;/* failed to open file */

	/* init file pointer */
	fp->fd = fd;

	fp->cnt = 0;

	fp->base = NULL;

	fp->flag = (*mode == 'r') ? _READ : _WRITE;

	return fp;
}


/* close a file freeing file descriptor */
