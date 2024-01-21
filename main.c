
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













   










































 //fct creation un fichier
       TOV *ouvrir(char *nomfich,char mod)  // mod = 'A' ancien (r+)
{
    TOV *fichier=malloc(sizeof(TOV)) ;
    char s[3];
    if ((mod == 'A') || (mod =='a')) {
        sprintf(s,"rb+");
    }
    else {
    sprintf(s,"wb+");
         }
    fichier->f=fopen(nomfich,s);

    if ((mod == 'A') || (mod =='a'))
    {
        fread(&(fichier->entete),sizeof(entete),1,fichier->f);
    }
    else
    {
        (fichier->entete).indice_der_bloc=0;
        (fichier->entete).totalblocs=0;
        (fichier->entete).totaleng=0;
        fwrite(&(fichier->entete),sizeof(entete),1,fichier->f);
    }
    return fichier;

}

 //fct fermer le bloc pour sauvegarde les modification
void fermer(TOV *fichier)
{

    fseek(fichier->f,0,0);
    fwrite(&(fichier->entete),sizeof(entete),1,fichier->f);
    fclose(fichier->f);

}


