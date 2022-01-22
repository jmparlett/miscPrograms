# Synchronize 
### Created: 2022-January-21

## Working with files and directories

We'll use dirent.h for directory management functions, and sys/stat.h to read file modified dates.
### Functions
- opendir("name") will return a dir pointer that we can file information from including a name
- readdir(<dir *>) will grab information from a DIR pointers stream, we can read filename with this, the struct returned is static alloc, dont free it.
- fstat()  can file information from a name
- remove() can remove a file or directory

Once we have list of files we need to act them based on a few criteria. We will name the lists *A,B*, and the directories *a,b*.
- if a file is in list A but not in B copy the file into dir b
- if a file is in list B but not in A remove it from dir b
- if a file is in list B and A we have 3 possibilites
  1. the file in B is newer then the one in A, copy the file into dir a
  2. the file in A is newer then the one in B, copy the file into dir b
  3. the files are the same age, do nothing

The stat structs *st_mtim* member returns last modifed time contained in a timespec struct. We can create a function to compare the
nanoseconds by subtraction.
```c
  struct timespec {
                  time_t  tv_sec;  /* Seconds */
                  long    tv_nsec; /* Nanoseconds */
              };
```

