




/************************************************************************
 * Interface du mod�le simplif� d'un fichier TOF 	*
 * les types des blocs de donn�es et de l'ent�te 			*
 * les fonctions du mod�le : ouvrir, fermer, lireDir, ecrireDir ...	*
 ************************************************************************/


#ifndef MODELE_H
#define MODELE_H

#include <stdio.h>

// capacit� maximale d'un bloc de donn�es (en nombre d'enregistrements)
#define MAXTAB 10


// type d'un bloc de donn�es (et donc des buffers aussi)
typedef struct blc {
	   long tab[MAXTAB];	// tableau d'enregistremnts (des entiers longs)
	   char eff[MAXTAB];	// indicateurs d'effacement logique ('*' effac� / sinon non effac�)
	   int nb;		// nombre d'enregistrements dans le bloc
        } tbloc;


// type du bloc d'ent�te (les caract�ristiques du fichier)
typedef struct entete {
	   // nombre de blocs utilis� par les enreg (c'est aussi le num du dernier bloc)
	   long nb_bloc;
	   // nombre d'enregistrements dans le fichier
	   long nb_ins;
	   // nombre d'enregistrements supprim�s (logiquement) dans le fichier
	   long nb_sup;

	} t_entete;




// ouvrir un fichier en mode 'N' ou 'A'
// retourne le flux f et l'ent�te ent
void ouvrir( FILE **f, char *nom, char mode, t_entete *ent );

// fermer le fichier en sauvegardant l'ent�te ent dans le 1er bloc (num 0) du fichier
void fermer( FILE *f, t_entete *ent);

// lecture du bloc de donn�es num i dans la variable buf
void lireDir( FILE *f, long i, tbloc *buf );

// ecriture du contenu de la variable buf dans le bloc de donn�es num i
void ecrireDir( FILE *f, long i, tbloc *buf );


#endif

