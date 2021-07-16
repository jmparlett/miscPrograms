#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


/* CONCATENATE THE FILES */

void filecopy(FILE *, FILE *);

int main(int argc, char * argv[])
{
	FILE *fp; /* file pointer. FILE is its own type */


	if(argc == 1){ /* NO FILES SO TRAP THEM IN INFINITE LOOP FOR BEING DUMB */
		filecopy(stdin, stdout);
	} else {
		while(--argc > 0)
			
			if((fp = fopen(*++argv, "r")) == NULL){
				printf("cat file error opening(%s): I dunno what your trying to make me do but I dont wanna\n", *argv);
			} else {
				
				filecopy(fp, stdout);

				fclose(fp);
			}
		return 0;
	}
}

/* this copys the contents of a file pointer to another file pointer */
void filecopy(FILE *ifp, FILE *ofp)
{
	int c;

	while((c = getc(ifp)) != EOF) putc(c, ofp);
}
