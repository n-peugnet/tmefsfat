#include "fat.h"
#include <string.h>
#include <stdio.h>

int file_found (char * file ) {
  int i;
  struct ent_dir * pt = pt_DIR;

  for (i=0; i< NB_DIR; i++) {
    if ((pt->del_flag) && (!strcmp (pt->name, file))) 
      return 0;
    pt++;
  }
  /* finchier n'existe pas */
  return 1;
}


void list_fat () {
  int i;
  short *pt = pt_FAT;
  for (i=0; i < NB_ENT_FAT; i++) {
    if (*pt)
      printf ("%d ",i);
    pt++;
  }
  printf ("\n");
}


void list_dir ( ) {
  struct ent_dir *pt = pt_DIR;
}

int cat_file (char* file) {
 /* A COMPLETER */
}

int mv_file (char*file1, char *file2) {
   /* A COMPLETER */
}

int delete_file (char* file)
{
   /* A COMPLETER */  
}

int create_file (char *file) {
  /* A COMPLETER */  
}


short alloc_bloc () { 
  /* A COMPLETER */  
}
 	
int append_file  (char*file, char *buffer, short size) { 
  /* A COMPLETER */  
}

struct ent_dir*  read_dir (struct ent_dir *pt_ent ) {
  /* A COMPLETER */  
}
