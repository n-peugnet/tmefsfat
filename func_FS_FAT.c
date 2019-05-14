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
  int i;
  int count = 0;
  for (i=0; i< NB_DIR; i++) {
    if (pt->del_flag) {
      printf("%d %s ", pt->size, pt->name);
      print_blocks(pt);
      printf("\n");
      count++;
    }
    pt++;
  }
  printf("total %d\n", count);
}

void print_blocks(struct ent_dir* pt) {
  int nb_blocks = (pt->size + SIZE_SECTOR - 1) / SIZE_SECTOR;
  short pt_blocks[nb_blocks];
  list_blocks(pt->first_bloc, pt_blocks);
  int i;
  for (i = 0; i < nb_blocks; i++)
  {
    printf("%d ", pt_blocks[i]);
  }
}

int list_blocks(short first_block, short *pt_blocks) {
  short * pt_fat = pt_FAT;
  short next_block = first_block;
  short index = 0;
  while (next_block != -1)
  {
    pt_blocks[index] = next_block;
    index++;
    next_block = pt_fat[next_block];
  }
  return 0;
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
