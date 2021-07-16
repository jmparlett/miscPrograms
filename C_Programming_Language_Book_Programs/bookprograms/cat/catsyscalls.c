#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFSIZE 100
#define STDIN 0
#define STDOUT 1
#define STDERR 2

/* CONCATENATE THE FILES */
void filecopy(int, int);

int main(int argc, char * argv[])
{
	int fd; /* file descriptor. gurenteed to be a non negative int to be used by read and write ops */


	if(argc == 1){ /* NO FILES SO TRAP THEM IN INFINITE LOOP FOR BEING DUMB */
		filecopy(STDIN, STDOUT);
	} else {
		while(--argc > 0)
			
			if((fd = open(*++argv, O_RDONLY)) == -1){
				printf("cat file error opening(%s): I dunno what your trying to make me do but I dont wanna\n", *argv);
			} else {
				
				filecopy(fd, STDOUT);

				close(fd);
			}
		return 0;
	}
}

/* this copys the contents of a file pointer to another file pointer */
void filecopy(int ifile, int ofile)
{
	char buf[BUFSIZE];
	int n;

	while((n=read(ifile, buf, BUFSIZE)) > 0) write(ofile, buf, n);

}
