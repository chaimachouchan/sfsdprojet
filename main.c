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

 //declaration buffer
   typedef struct TypeBloc buffer;

  // declaration entete n3amroha dans main entete au debut de fichier
  typedef struct entete{
     int indice_der_bloc; //pour compare
     int totalblocs; // nb  de bloc
     int totaleng; // nb d'enrg

   }entete;

  //dclaration tov tab ordonee variable
   typedef struct TOV {
       FILE *f;
       entete entete;
   }TOV;