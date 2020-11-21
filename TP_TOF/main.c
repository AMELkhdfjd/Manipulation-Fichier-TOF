#include <stdio.h>
#include <stdlib.h>

#include "fonction.h"


FILE *f = NULL;
t_entete ent;//l'entet
tbloc buf;//1er buffer
tbloc buf2;//2eme buffer

void charg();		// Chargement initial du fichier
void info();		// Affichage de l'entête
void compactage(double u );//compactage de fichier
void affichage();  // Affichage d'une séquence de blocs contigus (entre a et b)


#define MAXTAB 10


int main()
{
   int choix , i;
   char  nom[20], mode[20];
   double u;

   printf("Op%crations d'acc%cs sur un Fichier de type TOF\n",130,138);
   printf("Capacit%c maximale des blocs = %d enregistrements\t",130, MAXTAB);
   printf("Taille d'un bloc = %ld \tTaille entete = %ld\n\n", sizeof(tbloc), sizeof(t_entete) );

   // Ouverture du fichier ...
   printf("Donnez le nom du fichier : ");
   scanf(" %s", nom);
   printf("Ancien ou Nouveau ? (a/n) : ");
   scanf(" %s", mode);
   if ( mode[0] == 'a' || mode[0] == 'A' )
   {


	ouvrir( &f, nom , 'A', &ent );
   }
   else {
	ouvrir( &f, nom , 'N', &ent );
	charg();


   }

   // Menu principal ...
   do {
      	printf("\n--------- M E N U ---------\n");
	printf("1) Afficher l'entete du fichier\n");
	printf("2) compactage de fichier\n");
	printf("3) Affichage de bloc(s)\n");
	printf("0) Quitter le programme\n");
	printf("\tchoix : ");
	scanf(" %d", &choix);
	printf("\n---------------------------\n\n");

	switch(choix) {
	   case 1: info(); break;
	   case 2: printf("Donnez le taux de chargement souhait%c (entre 0 et 1) : ",130);
   		   scanf(" %lf", &u);
		   compactage( u);

		   break;
	  case 3: affichage(); break;
	  // case 6: reorg(); break;
	}
   } while ( choix != 0);

   // Fermeture du fichier (sauvegarde de l'entete) ...
   fermer(f, &ent);

   return 0;

} // main



// Chargement initial à u% ...
void charg()
{
   double u;
   long i, k, n;
   int l=0,j;
   char c;

   printf("Chargment initial du fichier\n");
   printf("Donnez le nombre d'enregistrement que vous voulez  ins%crer : ",130);
   scanf(" %ld", &n);
  printf("Donnez le taux de chargement souhait%c (entre 0 et 1) : ",130);
   scanf(" %lf", &u);
   if ( u < 1/MAXTAB ) u = 1/MAXTAB; // pour avoir au moins un enregistrement par bloc
   if ( u > 1 ) u = 1.0;	     // maximum = 100%

   printf("Remplissage des blocs avec %d enreg (sauf %cventuellement le dernier)\n",\
	   (int)(MAXTAB*u),130);
   j = 0;
   i = 1;
   for (k=0; k<n; k++) {
	if ( j < MAXTAB*u ) {

	   buf.tab[j] = k*10;
        printf("Donnez le caract%cre d'effacement (*) si effac%c :",130,130);
         scanf(" %c", &c);
         if (c=='*'){l++;}

	   buf.eff[j] = c;
	   j++;
	}
	//changement de bloc
	else {
	   buf.nb = j;
	   ecrireDir(f, i, &buf);

	   i++;
	   buf.tab[0] = k*10;
	    printf("Donnez le caract%cre d'effacement  : (*) si effac%c",130,130);
         scanf(" %c", &c);
          if (c=='*'){l++;}
	   buf.eff[0] = c;
	   j = 1;
	}
   }
   // dernière écriture ...
   buf.nb = j;
   ecrireDir(f, i, &buf);

   // m-a-j de l'entete ...
   ent.nb_bloc = i;
   ent.nb_ins = n;
   ent.nb_sup = l;
} // charg


void info()
{
   printf("Informations sur le fichier \n");
   printf("\tNombre de blocs utilis%cs = %ld\n",130, ent.nb_bloc);
   printf("\tNombre d'enregistrements ins%cr%cs = %ld\n",130,130, ent.nb_ins);
   printf("\tNombre d'enregistrements supprim%cs = %ld\n",130, ent.nb_sup);

} // info



  void compactage(double u)//u :est le taux de chargement
{
   long i=1;
   int m=0,j,h=0,k=0,g=0;

     while(i<=ent.nb_bloc)//1er boucle
   {
       lireDir(f,i,&buf );
       g++;

       for(j=0;j<buf.nb;j++)//2 eme boucle   si sur pas de vide
       {
           if ( buf.eff[ j ] != '*' )   {
              if ( k < MAXTAB*u )  //on donne u==1
                  {
                   buf2.tab[k] = buf.tab[j];
                   k++;
                 }
                 else  //  c-a-d k == MAXTAB*u
                {
                   h++;
                   buf2.nb = k;
                   ecrireDir( f, h, &buf2 );
                   g++;

                   buf2.tab[0] = buf.tab[j];
                   k = 1;
                 }
              m++;
    	   }
       } // for
       i++;
   } // while
   //2eme traitement :la dernier ecriture avec la modification de l'entete
   h++;
   buf2.nb = k;		     // m.a.j du champ nb
   ecrireDir(f, h, &buf2);
   g++;

   ent.nb_bloc =h;
   ent.nb_ins =m;
   ent.nb_sup = 0;
    printf("le co%ct est:     %d  ",150, g);


}//compactage


// Affichage d'une séquence de blocs contigus (entre a et b)
void affichage()
{
   long i, a, b;
   int j;

   printf("Affichage d'une s%cquence de bloc(s). ayant des adresses dans [a , b] \n",130);
   printf("le fichier commence dans le bloc num 1 et se termine dans le bloc num %ld\n", ent.nb_bloc);
   printf("donnez a : ");
   scanf(" %ld", &a);
   printf("donnez b : ");
   scanf(" %ld", &b);
   for (i = a; i <= b; i++) {
      lireDir(f, i, &buf);
      printf("[Bloc Num:%3ld \tNB = %2d \tCapacit%c max = %2d]\n", i, buf.nb,130, MAXTAB);
      for( j=0; j<buf.nb; j++)
	 if ( buf.eff[j] != '*' )
	    printf("%ld ", buf.tab[j]);
	 else
	    printf("*%ld* ", buf.tab[j]);
      printf("\n--------------------------------------------------\n");
   }

} // affichage








