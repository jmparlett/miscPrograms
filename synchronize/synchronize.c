//Author: Jonathan Parlett
// Program Name: synchronize.c
// Created: 2022-January-21
// Purpose: This program synchronize 2 given directories. The first provided directory is the master/primary, the second is the slave
// anything in the slave, but not the master will be deleted, anything in the master, but not the slave will be copied to the slave.
// in the case of the file being present in both, the newest is taken and replicated to the other.
#include "synchronize.h" 



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
  }

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
