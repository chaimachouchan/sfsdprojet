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