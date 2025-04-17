#include "types.h"

#ifndef VALISP_ERREUR_H
#define VALISP_ERREUR_H

enum erreurs{
    TYPAGE,
    ARITE,
    NOM,
    MEMOIRE,
    DIVISION_PAR_ZERO,
    SYNTAXE,
    MEMOIRE_PARSEUR,
    RUNTIME
};



void erreur_fatale(char  *fichier, int ligne, char* causes);
void afficher_erreur(void);
void erreur(enum erreurs type, char* fonction, char* message, sexpr s);
#define ERREUR_FATALE(CAUSE) erreur_fatale(__FILE__,__LINE__,CAUSE)

#endif
