
 #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
void lireDir(TOV *fichier, int i, buffer buf) {
    // Vérifie si i est dans les limites du fichier
    if (i <= ientete(fichier, 1)) {
        // Positionne le curseur au début du bloc i
        fseek(fichier->f, sizeof(entete) + ((i - 1) * sizeof(TypeBloc)), SEEK_SET);
        // Lit le bloc dans le tampon (buf)
        fread(&buf, sizeof(TypeBloc), 1, fichier->f);
    }
}

// Écriture du tampon (buf) dans le bloc i
void EcrireDir(TOV *fichier, int i, buffer buf) {
    // Vérifie si i est dans les limites du fichier
    if (i <= ientete(fichier, 1)) {
        // Positionne le curseur au début du bloc i
        fseek(fichier->f, sizeof(entete) + (sizeof(TypeBloc) * (i - 1)), SEEK_SET);
        // Écrit le tampon dans le fichier
        fwrite(&buf, sizeof(TypeBloc), 1, fichier->f);
    }
}
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
//recherche dichotomique de la cle
 void recherche_dicho( TOV* fichier,int c,bool *trouv,int *i,int *j){

    struct TypeBloc buf ;
    bool stop;
    entete entete;
    int bi,bs,inf,sup,k; // pour parcourir les eng apres on donne val de k win l9ina la cle l j

    bs = ientete(fichier,1);  // la borne sup (le num du dernier bloc de f)
    bi = 1;  // la borne inf (le num du premier bloc de f)

    trouv=false;
    stop=false;
    k=1;
    //recherche dichotomique entre blocs
    while((bi<=bs) && (!trouv)&&(!stop)){
        i=(bi + bs)/2;
        lireDir(fichier,i,buf);

        //recherche dichotomique dans le bloc
        if((c>=buf.tab[1].cle) && (c <= buf.tab[buf.nb].cle)){
            inf = 1;
            sup = buf.nb;
            while((inf<=sup) && (!trouv)){
                k = (inf + sup)/2 ;

                if( c == buf.tab[k].cle){
                    trouv=true;
                    j=k;
                }else{
                    if(c < buf.tab[k].cle){
                       sup=k--;;
                       }else{
                        inf=k++;
                       }
                }
            }
            if(inf>sup){
                k=inf;
            }

            stop=true;

        }
        else{
                if(c < buf.tab[1].cle){
                    bs=i--;
                }else{
                    bi=i++;
                }
        }
    }

    if(bi>bs){
        i=bi;
        k=1;
        j=k;
    }


    fclose(fichier);
}
 // Insere un enregistrement dans le fichier TOV
void inserer(typeEng e, TOV *fichier) {
    TypeBloc buffer;
    bool trouv;
    bool continuer;
    int i, j, k;
    buffer.nb =1;
    recherche_dicho(fichier, e.cle, &trouv, &i, &j);

    if (!trouv) {
        continuer = true;

        while ((continuer) && (i <= ientete(fichier, 1))) {
            lireDir(fichier, i, buffer);
            typeEng x = buffer.tab[buffer.nb - 1];
            k = buffer.nb - 1;

            while (k >= j) {
                buffer.tab[k] = buffer.tab[k - 1];
                k = k - 1;
            }

            buffer.tab[j - 1] = e;
            buffer.nb = buffer.nb + 1;

            if (buffer.nb <= 10) {
                EcrireDir(fichier, i, buffer);
                continuer = false;
            } else {
                EcrireDir(fichier, i, buffer);
                i = i + 1;
                j = 1;
                e = x;
            }
        }

        if (i > ientete(fichier, 1)) {
            buffer.tab[0] = e;
            buffer.nb = 1;
            EcrireDir(fichier, i, buffer);
            AffEntete(fichier, 1, i);
        }

        AffEntete(fichier, 2, ientete(fichier, 2) + 1);

    }
}


// Suppression d'un enregistrement de clé c
void supression(int c, TOV *fichier) {
    int i, j; // i: indice de tableau de bloc, j: indice d'eng dans un tab d'eng dans un bloc
    bool trouv;
    TypeBloc buf;
    const char lo[20] = "logique";
    const char ph[20] = "physique";
    recherche_dicho(fichier, c, &trouv, &i, &j);

    if (trouv) {
        printf("Vous voulez la suppression physique ou logique? ");
        char type[20];
        scanf("%s", type);

        if (strcmp(type, lo) == 0) {
            buf.tab[j - 1].supp = true;
            EcrireDir(fichier, i, buf);
        } else if (strcmp(type, ph) == 0) {
            for (int k = j - 1; k < buf.nb - 1; k++) {
                buf.tab[k] = buf.tab[k + 1];
            }
            buf.nb--;
            EcrireDir(fichier, i, buf);
        }
    }

    AffEntete(fichier, 2, ientete(fichier, 2) - 1);
}


       //supression d un enregistrement de cle c
  void supression(int c , TOV *fichier){
     int i,j ;// i:indice de tableau de bloc j: indice d'eng dans un tab d'eng dans un bloc
     int k ; // pour faire decalage de tab d'eng
     char type[20] ;// type de supression
     bool trouv;
     TypeBloc buf ;
     const char lo[20]= "logique";
     const char ph[20]= "physique" ;
     recherche_dicho(fichier,c,&trouv,&i,&j); //cherche a cle c
      if(trouv == true){
        printf("vous voullez la supression physique ou logique? ");
        scanf("%s", type);//choisi si physique ou logique
        //strcmp pour compare 2 chaine de caractere type et lo ou ph si return 0 alors sont identique
         if(strcmp(type,lo) == 0){

            buf.tab[j].supp = true;
            EcrireDir(fichier,i,buf);
         }else if(strcmp(type,ph) == 0){

                for (k=j ; k<buf.nb ; k++){

                    buf.tab[k]=buf.tab[k+1]; //decalage apartir d enrg qui veut suprimer
                }
                buf.nb-- ; //pour suprime derniere case
             
              }
      }
        AffEntete(fichier, 2, ientete(fichier, 2) - 1);
      fclose(fichier);
   }

  int main()
    {

    int k,nbr;
    TypeBloc buf;
    TOV *fichier;
    int i, j, cle;
    bool trouv;
    char nomfich[30];
    typeEng e;
    char *nom = NULL;
    char *prenom = NULL;
    char Char;
    int tailleNom = 0;
    int taillePrenom = 0;
    entete mon_entete;
    int choix, choix1;
    mon_entete.indice_der_bloc=4;
    mon_entete.totalblocs=5;
    mon_entete.totaleng=50;

menuprincipal :
  printf("\n  LE MENU PRINCIPAL \n\n\n");
  printf(" [1] : creation d'un fichier;\n");
  printf(" [2] : ouverture d'un fichier existant;\n");
  printf(" [0] : quitter programme;\n");
  printf("\n\n Votre choix :\n ");

  scanf("%d",&choix);
  switch(choix)
    {
    case 0 : // fin programme ;
    {
      goto end;
    }
    case 1 : // nouveau fichier
    {

      printf("\n  CREATION FICHIER :\n");
      printf(" Veuillez donner le nom de votre fichier : ");
      scanf("%s",nomfich);
      fichier = ouvrir(nomfich,'N');
      
    manipulation_fichier :
      printf("\n\n [1] : Insertion.\n");
      printf(" [2] : Recherche.\n");
      printf(" [3] : Suppression.\n");
      printf(" [0] : menu principal.\n");

      printf("\n\n Votre choix : ");
      scanf("%d",&choix1);

       switch(choix1){
           case 0 : // retour au menu principal
        {
          fermer(fichier);
          goto menuprincipal;
        }
        case 1 : // insertion
        {
          int k ;
          printf("\n  INSERTION :\n");
          printf("Combien d'enregistrements voulez-vous entrer ? : ");
          scanf("%d", &k);
          getchar();// consume newline
          buf.nb=k;
    for (int i = 0; i <= k; i++) {
        // Nom
        printf("Veuillez entrer un nom [appuyer Entrer pour terminer] : ");
        while (1) {
            Char = getchar();
            if (Char == '\n') {
                break;
            }
            char *temp_nom = (char *)realloc(nom, (tailleNom + 1) * sizeof(char));
            if (temp_nom == NULL) {
                // Handle memory allocation failure
                printf("Memory allocation failed for nom\n");
                free(nom);
                free(prenom);
                return 1;
            }
            nom = temp_nom;
            nom[tailleNom] = Char;
            tailleNom++;
        }
        nom = (char *)realloc(nom, (tailleNom + 1) * sizeof(char));
        nom[tailleNom] = '\0';
        e.nom = nom;

        // Prenom
        printf("Veuillez entrer un prenom [appuyer Entrer pour terminer] : ");
        while (1) {
            Char = getchar();
            if (Char == '\n') {
                break;
            }
            char *temp_prenom = (char *)realloc(prenom, (taillePrenom + 1) * sizeof(char));
            if (temp_prenom == NULL) {
                // Handle memory allocation failure
                printf("Memory allocation failed for prenom\n");
                free(nom);
                free(prenom);
                return 1;
            }
            prenom = temp_prenom;
            prenom[taillePrenom] = Char;
            taillePrenom++;
        }
        prenom = (char *)realloc(prenom, (taillePrenom + 1) * sizeof(char));
        prenom[taillePrenom] = '\0';
        //e.prenom = prenom;

        // Cle
        printf("Veuillez entrer la cle : ");
        scanf("%d", &cle);
        e.cle = cle;

        inserer(e, fichier);
        getchar();
         }

          goto manipulation_fichier;
        }
         case 2 : // recherche
        {
         printf(" \n RECHERCHE: \n ");
         printf("Saisissez la cle a rechercher:\n");
         scanf("%d",&cle);
         recherche_dicho(fichier,cle,&trouv,&i,&j);
        if(trouv==true){
          printf("Resultat : La cle existe au bloc %d, position %d\n",i,j);
        }
       else{
         printf("Resultat: La cle %d n'existe pas dans le fichier",cle);
       }
        printf("\n");

          goto manipulation_fichier;


        }
          case 3 : // suppression logique
        {
          printf("\n  SUPPRESSION:\n\n");
          printf(" Donnez la cle a supprimer: ");
          scanf("%d",&cle);
          supression(cle , fichier);
          printf("la cle a ete supprimee! \n");
          goto manipulation_fichier;
        }
       }

    }
    case 2 : // ancien fichier
    {
      printf("\n  OUVERTURE FICHIER :\n");
      printf(" Veuillez donner le nom de votre fichier : ");
      scanf("%s",nomfich);
      fichier = ouvrir(nomfich,'A');
      if(fichier->f==NULL){
          printf("ce fichier n'existe pas! \n");
          fermer(fichier);
          goto menuprincipal;
      }else{
      goto manipulation_fichier;
      }

    end : return 0;
    } 
 }