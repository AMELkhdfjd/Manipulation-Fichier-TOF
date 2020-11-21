/**************************************************************************
 * Impl�mentation du mod�le simplfi� de fichier TOF *
 **************************************************************************/




#include "fonction.h"
#include <stdio.h>




// ouvre un fichier et m-a-j de l'ent�te ent
void ouvrir( FILE **f, char *nom, char mode, t_entete *ent )
{
   if ( mode == 'A' || mode == 'a' ) {
	*f = fopen( nom, "rb+" );
	if ( *f == NULL ) perror( "ouvrir (probleme dans fopen)" );
	fread( ent, sizeof(t_entete), 1, *f );
   }
   else { // mode == 'N' || mode == 'n'
	*f = fopen( nom, "wb+" );
	if ( *f == NULL ) perror( "ouvrir (probleme dans fopen)" );
	ent->nb_bloc = 0;
	ent->nb_ins = 0;
	ent->nb_sup = 0;
	fwrite( ent, sizeof(t_entete), 1, *f );
   }
}


// ferme le fichier et sauvegarde de l'entete au d�but du fichier
void fermer( FILE *f, t_entete *ent )
{
   fseek(f, 0L, SEEK_SET);
   fwrite( ent, sizeof(t_entete), 1, f );
   fclose(f);
}


// lecture du bloc de donn�es num�ro i dans la variable buf
void lireDir( FILE *f, long i, tbloc *buf )
{
   fseek(f, sizeof(t_entete) + (i-1)*sizeof(tbloc), SEEK_SET);
   fread( buf, sizeof(tbloc), 1, f );
}


// �criture du contenu de buf dans le bloc de donn�es num�ro i
void ecrireDir( FILE *f, long i, tbloc *buf )
{
   fseek(f, sizeof(t_entete) + (i-1)*sizeof(tbloc), SEEK_SET);
   fwrite( buf, sizeof(tbloc), 1, f );
}









