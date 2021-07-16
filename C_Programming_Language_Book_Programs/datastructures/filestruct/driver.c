#include "fopen.c"


int main(int argc, char *argv[])
{

	char mode[]="r";
	FILE *fp = fopen(argv[1], mode);

	int c;

	while((c = getc(fp)) != EOF) putc(c, stdout);	

	return 0;
}
