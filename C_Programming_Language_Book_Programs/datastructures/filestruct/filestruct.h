#include <unistd.h>
#include <stdlib.h>
#include <cstring>

#define EOF (-1)

#define BUFSIZ 1024

#define OPEN_MAX 20 /* max #files open */


typedef struct _iobuf { /* this allows us to define an instance of the struct by using (FILE j) instead of (struct _iobuf j) */

	int cnt; /* characters left */

	char *ptr; /* next character pos */

	char *base; /* location of buffer (current position in file) */

	int flag; /* mode/perms (read, write, append, etc) */

	int fd; /* file descriptor (small int used to reference file */

} FILE;

enum _flags {
	
	_READ = 01,

	_WRITE = 02,

	_UNBUF = 04, /* file is unbuffered */

	_EOF = 010, /* reached end of file */

	_ERR = 020 /* err in file */
};

extern FILE _iob[OPEN_MAX] = { /* set stdin, stdout, stderr */

	{0, (char *) 0, (char *) 0, _READ, 0},

	{0, (char *) 0, (char *) 0, _WRITE, 1},
	
	{0, (char *) 0, (char *) 0, (_WRITE | _UNBUF), 2}
};

#define stdin (&_iob[0])

#define stdout (&_iob[1])

#define stderr (&_iob[2])




int _fillbuf(FILE *);

int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)

#define ferror(p) (((p)->flag & _ERR) != 0)

#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))

#define putc(x,p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))

/* allocate file and input buffer */
int _fillbuf(FILE *fp){

	int bufsize;

	if((fp->flag&(_READ | _EOF | _ERR)) != _READ) return EOF;

	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

	if(fp->base == NULL) /* there is no buffer so allocate one */

		if((fp->base = (char *)malloc(bufsize)) == NULL) return EOF; /* if malloc failed */

		
	fp->ptr = fp->base; /* point to first pos in buffer */

	fp->cnt = read(fp->fd, fp->ptr, bufsize); /* get number bytes read. This is number of chars in file */

	if(--fp->cnt < 0){
		
		if(fp->cnt == -1) fp->flag |= _EOF; /* -1 means we took one from zero and are dealing with an empty file*/
		else fp->flag |= _ERR; /* unknown behavior return error */

		fp->cnt = 0; 

		return EOF;
	}
	return (unsigned char) *fp->ptr++;	
}


/* allocate a buffer and write a char into it. If buffer is full append buffer to file object and reset buffer */ 
int _flushbuf(int c, FILE *fp){

	int bufsize;

	if((fp->flag&(_WRITE | _ERR)) != _WRITE) return EOF; /* if filen ot open for writing stop */

	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ; /* if writing unbuffered than bufsize is one */

	if(fp->base == NULL) /* there is no buffer so allocate one */

		if((fp->base = (char *)malloc(bufsize)) == NULL) return EOF; /* if malloc failed */
	

	fp->ptr = fp->base; /* point to first pos in buffer */
	
	fp->cnt = write(fp->fd, fp->ptr, bufsize);


	fp->cnt--; /* allocate char and decrement cnt */
	return (*fp->ptr++ = c);

	
}
