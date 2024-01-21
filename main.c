#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

 //declaration  chauque enrg dans tab
  typedef struct typeEng{
      int cle;
      char *nom;
      char *prenom;
      bool supp;
  }typeEng;
 // decalaration de bloc
  typedef struct TypeBloc{
      typeEng tab[10];
      int nb;// nb d'enrg
  }TypeBloc;
