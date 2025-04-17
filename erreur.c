#include <stdio.h>
#include "types.h"
#include "stdlib.h"
#include "couleurs.h"
#include "erreur.h"

/**********************/
/*                    */
/*  Erreurs Fatales   */
/*                    */
/**********************/

sexpr SEXPR_ERREUR ;
char* FONCTION_ERREUR ;
char* MESSAGE_ERREUR ;
enum erreurs TYPE_ERREUR ;




void afficher_erreur(void) {
    printf("%s", couleur_rouge);
    printf("Erreur d'exécution ");
    switch (TYPE_ERREUR) {
        case TYPAGE:
            printf("[TYPAGE]");
            break;
        case ARITE:
            printf("[ARITE]");
            break;
        case NOM:
            printf("[Nom]");
            break;
        case MEMOIRE:
            printf("[MEMOIRE]");
            break;
        case DIVISION_PAR_ZERO:
            printf("[DIVISION_PAR_ZERO]");
            break;
        case SYNTAXE:
            printf("[SYNTAXE]");
            break;
        case MEMOIRE_PARSEUR:
            printf("[MEMOIRE_PARSEUR]");
            break;
        case RUNTIME:
            printf("[RUNTIME]");
            break;
    }
    printf(" : %s\n", MESSAGE_ERREUR);
    printf("Fonction fautive : << %s >>\n", FONCTION_ERREUR);
    printf("valeur fautive : << %s >>\n", get_string(SEXPR_ERREUR));

}

void erreur(enum erreurs type, char* fonction, char* message, sexpr s) {
    TYPE_ERREUR = type;
    FONCTION_ERREUR = fonction;
    MESSAGE_ERREUR = message;
    SEXPR_ERREUR = s;
    afficher_erreur();
    exit(1);
}





void erreur_fatale(char  *fichier, int ligne, char* causes) {
    fprintf(stderr,"%s", couleur_rouge);
    fprintf(stderr,"\n   /!\\ Erreur fatale /!\\");
    fprintf(stderr,"%s", couleur_defaut);
    fprintf(stderr,"   %s ligne %d\n\n", fichier, ligne);
    fprintf(stderr,"%s\n", causes);
    exit(1);
}
