#ifndef SYNCHRONIZE_H //include guard

#define SYNCHRONIZE_H



#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/***** Defines *****/
#define ENTRIES_INCREMENT 100
#define PDIR argv[1]
#define SDIR argv[2]

/***** Structs *****/
typedef struct dirent dirent;

typedef struct {
  size_t size;
  size_t capacity;
  char **files;
} flist;

/**************** File List Functions ****************/
flist* initDirlist(size_t size);
flist* dirList(DIR* D);
void makeNullFlist(flist* L);
void printFlist(flist* L);
/**************** Error Handling / Info  ****************/
void die(char *err);
void info(char *info);


/**************** Utilities ****************/
long compareModTime(char* fn1, char* fn2);
int copyFile(char* src, char* dest);
void* ec_malloc(size_t size);
int qstrcmp(const void* a, const void* b);


#endif /**** SYNCHRONIZE_H ****/
