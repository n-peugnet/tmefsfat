#include <stdlib.h>
#include <stdio.h>

#include "fat.h"
int main (int argc, char ** argv)
{
  
  open_FS();
  
  printf ("\nREPETOIRE AVANT:\n");
  list_dir ();
  

  switch (mv_file (argv[1], argv[2]))
  {
  case 1:
    printf ("%s n'existe pas\n", argv[1]);
    break;
  case 2:
    printf ("%s existe déjà\n", argv[2]);
    break;

  default:
    printf ("\nREPETOIRE APRES :\n");
    list_dir ();
    break;
  }

  close_FS ();

  return EXIT_SUCCESS;  
}
