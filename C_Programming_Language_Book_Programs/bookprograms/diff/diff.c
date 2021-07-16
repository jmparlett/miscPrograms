#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100


/* compare two files and print first line where they differ */
int main(int argc, char *argv[]){

	char *prog = argv[0];


	system("echo \"I just wanted to let you know this works\n\"");	
	if(argc < 3){ /* not enough args */
		fprintf(stderr, "%s: not enough arguments\n", prog);
		return -1;
	} else { 
		FILE *fp1, *fp2;
		
		fp1 = fopen(*++argv, "r");

		fp2 = fopen(*++argv, "r");
		
		if(fp1 == NULL || fp2 == NULL){

			fprintf(stderr, "%s: cannot open one or more files\n", prog);
			return -1;
		}

		char f1line[MAXLINE];
		char f2line[MAXLINE];
		
		int lineno=1;
		while(fgets(f1line, MAXLINE, fp1) != NULL && fgets(f2line, MAXLINE, fp2) != NULL){
			
			if(strcmp(f1line, f2line) != 0){
				fprintf(stdout, "line %d: %s => %s", lineno, f1line, f2line);
				return 0;
			}
			lineno++;
		}
		return 0;
	}
}
