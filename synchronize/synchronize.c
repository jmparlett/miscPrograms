//Author: Jonathan Parlett
// Program Name: synchronize.c
// Created: 2022-January-21
// Purpose: This program synchronize 2 given directories. The first provided directory is the master/primary, the second is the slave
// anything in the slave, but not the master will be deleted, anything in the master, but not the slave will be copied to the slave.
// in the case of the file being present in both, the newest is taken and replicated to the other.
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
		
#define ll long long int
#define ull unsigned long long int
#define li long int
#define ui unsigned int


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



/**************** Error Handling / Info  ****************/
//print error msg and exit
void die(char *err){
  printf("Error: %s\n",err);
  exit(-1);
}

void info(char *info){
  printf("Info: %s\n",info);
}


/**************** File List Functions ****************/
flist* initDirlist(size_t size){
  flist* D = malloc(sizeof(flist*));

  D->size = 0;

  D->capacity = size;

  D->files = malloc(sizeof(char*)*size);

  return D;
}

//return a list of files in a directory (basically ls)
flist* dirList(DIR* D){
  flist* L = initDirlist(ENTRIES_INCREMENT);
  dirent *cur;
  while((cur = readdir(D)) != NULL){
    //lets ignore the implicit dirs
    if(!strcmp(cur->d_name,".") || !strcmp(cur->d_name,"..")) continue;

    if(L->size==L->capacity){//alloc more space
      L->capacity+= ENTRIES_INCREMENT;
      if(realloc(L->files,L->capacity*sizeof(char*)) == NULL)
        die("failed to allocate memory");
    }
    //add file to list 
    L->files[L->size] = malloc(strlen(cur->d_name));
    strcpy(L->files[L->size], cur->d_name);
    L->size++;
  }
  return L;
}

//free the flist** of a flist struct so we can free the struct after
void makeNullFlist(flist* L){
  for(unsigned int i=0; i < L->size; i++)
    free(L->files[i]);

  free(L->files);
}

void printFlist(flist* L){
  for(size_t i = 0; i < L->size; i++){
    printf("%s\n",L->files[i]);
  }
}

/**************** Utilities ****************/
//compares the last modified time of 2 files
long compareModTime(char* fn1, char* fn2){
  //returns positive if file1 is newer, negative if file2 is newer, and 0 if they are equal
  struct stat file1; 
  struct stat file2; 

  stat(fn1,&file1);
  stat(fn2,&file2);

  return (file1.st_mtime)-(file2.st_mtime);
}

//given 2 filenames copy the first file to the second, either or both files may not exist in which case any that do not will be created
int copyFile(char* src, char* dest){
  
  int srcFd = open(src,O_RDONLY|O_CREAT, S_IRUSR|S_IRGRP|S_IWUSR|S_IROTH);
  int destFd = open(dest,O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IRGRP|S_IWUSR|S_IROTH);
  
  //get file size for write
  struct stat srcStats;
  fstat(srcFd, &srcStats);
  
  //char is only a byte, but hey
  char* buf;
  if( (buf = malloc(sizeof(char)*srcStats.st_size)) == NULL)
    return -1;

  if(read(srcFd, buf, srcStats.st_size) < 0)
    return -1;

  if(write(destFd, buf, srcStats.st_size) < 0)
    return -1;

  //close files
  close(srcFd);
  close(destFd);

  //completed sucessfully
  return 0;
}

//error checked malloc
void* ec_malloc(size_t size){
  void *ptr;
  if((ptr = malloc(size)) == NULL)
    die("failed to alloc memory");
  return ptr;
}

//for quicksort/bsearch
int qstrcmp(const void* a, const void* b){
    return strcmp(*(const char**)a, *(const char**)b);
}
  










int main(int argc, char *argv[]){

  if(argc < 3)
    die("not enough args (usage: 'synchronize dir1 dir2')");

  DIR* primaryDirP, *slaveDirP;

  if((primaryDirP= opendir(argv[1])) == NULL)
    die("could not open dir1");

  if((slaveDirP = opendir(argv[2])) == NULL)
    die("could not open dir2");

  //after this point we will use the macros to refer to dirnames (reference defines)


  //primary dir list, and slave dir list
  flist* pDList = dirList(primaryDirP);
  flist* sDList = dirList(slaveDirP);

  //sort the lists 
  qsort(sDList->files, sDList->size, sizeof(const char*), qstrcmp);
  qsort(pDList->files, pDList->size, sizeof(const char*), qstrcmp);

  info("loaded file lists, syncing files");
  
  // compare files in master to slave and act accordingly
  for(unsigned int pdx=0; pdx < pDList->size; pdx++){
    //need to make enough space in a path variable for the dir name, file name, and a path seperator '/'

    //full file path with primary dir
    char *fp1 = ec_malloc(sizeof(char)*(strlen(PDIR)+strlen(pDList->files[pdx])+1));
    strcpy(fp1,PDIR);
    strcat(fp1,"/");
    strcat(fp1,pDList->files[pdx]);

    //full file path with slave dir
    char *fp2 = ec_malloc(sizeof(char)*(strlen(SDIR)+strlen(pDList->files[pdx])+1));
    strcpy(fp2,SDIR);
    strcat(fp2,"/");
    strcat(fp2,pDList->files[pdx]);

    //check if current file in primary dir is present in slave dir
    int inS = (bsearch(&pDList->files[pdx], sDList->files, sDList->size,sizeof(char*), qstrcmp) == NULL ? -1 : 1);
    // printf("%s at %d in %s", pDList->files[pdx], inS, SDIR);

    if(inS == -1){//not present place it in slave dir

      printf("Info: copying %s to %s\n",fp1,fp2);

      if(copyFile(fp1,fp2) == -1)
        die("failed to copy file");

    } else {//present in both, but which is newer?

      int pNewer = compareModTime(fp1,fp2);

      if(pNewer > 0){//primary dir file is newer
      printf("Info: copying %s to %s\n",fp1,fp2);

        if(copyFile(fp1,fp2) == -1)
          die("failed to copy file");

      } else if(pNewer < 0){//slave dir file is newer

      printf("Info: copying %s to %s\n",fp2,fp1);

        if(copyFile(fp2,fp1) == -1)
          die("failed to copy file");
      }
      //else they are the same age and we do nothing
    }
    // free ptrs and cleanup
    free(fp1);
    free(fp2);
  } //end for

  //check files in slave dir and delete any not present in master
  for(unsigned int sdx=0; sdx < sDList->size; sdx++){
    //check if current file in master
    int inP = (bsearch(&sDList->files[sdx], pDList->files, pDList->size,sizeof(char*), qstrcmp) == NULL ? -1 : 1);
    if( inP == -1){
      //full file path with slave dir
      char *fp1 = ec_malloc(sizeof(char)*(strlen(SDIR)+strlen(sDList->files[sdx])+1));
      strcpy(fp1,SDIR);
      strcat(fp1,"/");
      strcat(fp1,sDList->files[sdx]);

      printf("Info: %s not in %s, deleting..\n", fp1, PDIR); 

      //delete extra
      remove(fp1);

      //cleanup
      free(fp1);
    }
    // printf("%s at %d in %s", sDList->files[sdx], inP, SDIR);
  }

  

  // int result = binSearch((void *)pDList->files,pDList->size,"Makefile",bstrcmp);
//
  // printf("Makefile at %d in primary\n", result);
//
  // result = binSearch((void *)sDList->files,sDList->size,"Makefile",bstrcmp);
//
  // printf("Makefile at %d in slave\n", result);
//
  // result = binSearch((void *)sDList->files,sDList->size,sDList->files[1],bstrcmp);
//
  // printf("%s at %d in slave\n",sDList->files[1], result);
//
  // printf("size of P: %d\n",pDList->size);
  // printf("size of S: %d\n",sDList->size);
//
  // printf("\nFile Lists\n");
  // printFlist(pDList);
  // printFlist(sDList);
//


  //cleanup and exit
  makeNullFlist(pDList);
  free(pDList);
  makeNullFlist(sDList);
  free(sDList);
  closedir(primaryDirP);
  closedir(slaveDirP);


  info("synchronization complete");
  return 0;
}
