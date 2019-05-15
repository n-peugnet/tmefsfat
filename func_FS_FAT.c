#include "fat.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

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

// returns the index of the file in the Dir array or else -1
int file_index(char *file) {
  int i;
  struct ent_dir * pt = pt_DIR;

  for (i=0; i< NB_DIR; i++) {
    if ((pt->del_flag) && (!strcmp (pt->name, file))) 
      return i;
    pt++;
  }
  /* finchier n'existe pas */
  return -1;
}

// returns the index of the first free index in the Dir array or else -1
int find_free_index() {
  int i;
  struct ent_dir * pt = pt_DIR;
  for (i=0; i< NB_DIR; i++) {
    if (!pt->del_flag)
      return i;
    pt++;
  }
  return -1;
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

void print_blocks(struct ent_dir *pt) {
  short nb = nb_blocks(pt);
  short pt_blocks[nb];
  list_blocks(pt->first_bloc, pt_blocks);
  int i;
  for (i = 0; i < nb; i++)
  {
    printf("%d ", pt_blocks[i]);
  }
}

void free_blocks(struct ent_dir *pt) {
  short nb = nb_blocks(pt);
  short pt_blocks[nb];
  list_blocks(pt->first_bloc, pt_blocks);
  int i;
  for (i = 0; i < nb; i++)
  {
    pt_FAT[pt_blocks[i]] = 0;
  }
}

short nb_blocks(struct ent_dir *pt) {
  return (pt->size + SIZE_SECTOR - 1) / SIZE_SECTOR;
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
  int index = file_index(file);
  if (index == -1) return 1;
  struct ent_dir *pt = pt_DIR + index;
  short nb = nb_blocks(pt);
  short pt_blocks[nb];
  char * text = malloc(SIZE_SECTOR);
  int i;
  list_blocks(pt->first_bloc, pt_blocks);
  for (i = 0; i < nb; i++)
  {
    if (read_sector(pt_blocks[i], text))
    {
      free(text);
      return 1;
    }
    printf("%s", text);
  }
  free(text);
  printf("\n");
  return 0;
}

int mv_file (char*file1, char *file2) {
  int index = file_index(file1);
  if (index == -1) return 1;
  if (!file_found(file2)) return 2;
  struct ent_dir *pt = pt_DIR + index;
  set_file_name(pt, file2);
  write_DIR_FAT_sectors();
  return 0;
}

void set_file_name(struct ent_dir *pt, char* name) {
  strncpy(pt->name, name, SIZE_FILE_NAME);
  pt->name[SIZE_FILE_NAME - 1] = '\0';
}

int delete_file (char* file)
{
  int index = file_index(file);
  if (index == -1) return 1;
  struct ent_dir *pt = pt_DIR + index;
  pt->del_flag = 0;
  free_blocks(pt);
  write_DIR_FAT_sectors();
  return 0;
}

int create_file (char *file) {
  int index = find_free_index();
  if (index == -1) return 1;
  if (!file_found(file)) return 2;
  struct ent_dir *pt = pt_DIR + index;
  set_file_name(pt, file);
  pt->del_flag = 1;
  pt->first_bloc = FIN_FICHIER;
  pt->last_bloc = FIN_FICHIER;
  pt->size = 0;
  write_DIR_FAT_sectors();
  return 0;
}


short alloc_bloc () { 
  /* A COMPLETER */
  return 1;
}
 	
int append_file (char*file, char *buffer, short size) { 
  /* A COMPLETER */
  return 1;
}

struct ent_dir* read_dir (struct ent_dir *pt_ent ) {
  /* A COMPLETER */
  return NULL;
}
