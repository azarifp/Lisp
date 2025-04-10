#include <stdio.h>
#include "types.h"
#include "stdlib.h"
#include "couleurs.h"

/**********************/
/*                    */
/*  Erreurs Fatales   */
/*                    */
/**********************/

/* Pour s’arrêter lorsque le développeur tombe sur cas qui ne devrait
   jamais arriver. Normalement, si le programme est écrit sans bugs,
   les erreurs fatales ne devrait jamais être rencontrées. */

enum erreurs {
    TYPAGE,
    ARITE,
    NOM,
    MEMOIRE,
    DIVISION_PAR_ZERO,
    SYNTAXE,
    MEMOIRE_PARSEUR,
    RUNTIME
};

typedef sexpr SEXPR_ERREUR ;
typedef char* FONCTION_ERREUR ;
typedef char* MESSAGE_ERREUR ;
typedef enum erreurs TYPE_ERREUR ;

void afficher_erreur(void) {
    printf("Erreur d'exécution",couleur_rouge);
}

void erreur_fatale(char  *fichier, int ligne, char* causes) {
    fprintf(stderr,"%s", couleur_rouge);
    fprintf(stderr,"\n   /!\\ Erreur fatale /!\\");
    fprintf(stderr,"%s", couleur_defaut);
    fprintf(stderr,"   %s ligne %d\n\n", fichier, ligne);
    fprintf(stderr,"%s\n", causes);
    exit(1);
}
