#include "synchronize.h"

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

  //close files and free buf
  close(srcFd);
  close(destFd);
  free(buf);

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
