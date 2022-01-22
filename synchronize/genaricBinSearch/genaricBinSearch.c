//Author: Jonathan Parlett
// Program Name: genaricBinSearch.c
// Created: 2022-January-22
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define ll long long int
#define ull unsigned long long int
#define li long int
#define ui unsigned int

//alias for strcmp to take void * for qsort
int bstrcmp(const void * a, const void * b){
  return strcmp(*(const char**)a, *(const char**)b);
  // return strcmp((const char *)a,(const char *)b);
}

//for quicksort
int qstrcmp(const void* a, const void* b){
    return strcmp(*(const char**)a, *(const char**)b);
}

int icmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

//genaric binsearch, takes array of void pointers, and a pointer to a compar func
//return -1 on fail else returns position of element
int binSearch(void* array, size_t size, size_t esize, void* target, int (*compar)(const void *, const void*)){

  int l=0, r=size-1, mid;

  while(l <= r){

    mid = (l+r)>>1;//overflow safe midpoint

    int result = compar(target,array+(mid*esize));
    
    if(result < 0){//go left
      r=mid-1;
    } else if(result > 0){//go right
      l=mid+1;
    } else {//found target
      return mid;
    }
  }
  //didn't find target
  return -1;
}


int main(){

  int arr[] = {1, 5, 2, 6, 8, 0};

  qsort(arr, 6, sizeof(int), icmpfunc);

  for(int i=0; i < 6; i++) printf("%d ",arr[i]);
  printf("\n");

  int t=8;
  
  int result = binSearch(arr,6,sizeof(int),&t,icmpfunc);

  printf("%d at %d in array\n",t,result);

  for(int i=0; i < 6; i++) printf("%d ",arr[i]);
  printf("\n");

}
