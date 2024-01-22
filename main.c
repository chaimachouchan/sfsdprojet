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
   typedef struct Buffer {
    TypeBloc bloc;
} Buffer;

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



    // Fonction pour obtenir la i-ème caractéristique de l'en-tête ientete(f,i)

int ientete(TOV *f, int i) { // tov *f int i

    // Retourne la i-ème caractéristique en fonction de la valeur de i
    switch (i) {
        case 1:
            return (f->entete).indice_der_bloc;
        case 2:
            return (f->entete).totalblocs;
         case 3:
             return (f->entete).totaleng;
        // Ajoutez d'autres cas pour d'autres caractéristiques
        default:
            fprintf(stderr, "Caractéristique non prise en charge\n");
            return -1;  // Valeur par défaut pour caractéristique non prise en charge
    }}


           // mettre a jour l'entete affentete

        int AffEntete(TOV *f, int i, int val) {
             // si indice i = 1er cara alors on modifier la premiere cara
            if (i==1)
               return(f->entete).indice_der_bloc=val;
            //si indice i = 2eme cara alors on modifier la 2eme cara
            else if (i==2)
               return(f->entete).totalblocs=val;
            else if (i==3)
                return (f->entete).totaleng=val;

         }
         // Lecture du bloc i dans le tampon (buf)
void lireDir(TOV *fichier, int i, Buffer *buf) {
    // Vérifie si i est dans les limites du fichier
    if (i <= ientete(fichier, 1)) {
        // Positionne le curseur au début du bloc i
        fseek(fichier->f, sizeof(entete) + ((i - 1) * sizeof(TypeBloc)), SEEK_SET);
        // Lit le bloc dans le tampon (buf)
        fread(&(buf->bloc), sizeof(TypeBloc), 1, fichier->f);
    }
}

// Écriture du tampon (buf) dans le bloc i
void EcrireDir(TOV *fichier, int i, Buffer buf) {
    // Vérifie si i est dans les limites du fichier
    if (i <= ientete(fichier, 1)) {
        // Positionne le curseur au début du bloc i
        fseek(fichier->f, sizeof(entete) + (sizeof(TypeBloc) * (i - 1)), SEEK_SET);
        // Écrit le tampon dans le fichier
        fwrite(&(buf.bloc), sizeof(TypeBloc), 1, fichier->f);
    }
}
