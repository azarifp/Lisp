#include "allocateur.h"
#include "erreur.h"
#include "types.h"
#include "environnement.h"
#include "couleurs.h"

void *valisp_malloc(size_t size) {
    void *p = allocateur_malloc(size) ;
    if(p == NULL) ERREUR_FATALE("ATTENTION PLUS D'ESPACE !!!") ;
    return p;
}

void ramasse_miette_parcourir_et_marquer(sexpr s){;
    if (s == NULL || ramasse_miettes_lire_marque(s)) return;
    
    if (cons_p(s)) {
        ramasse_miette_parcourir_et_marquer(ramasse_miettes_poser_marque(car(s)));
        ramasse_miette_parcourir_et_marquer(ramasse_miettes_poser_marque(cdr(s)));
    }
    else{
        ramasse_miettes_poser_marque(s);
    }
}

void valisp_ramasse_miettes(sexpr env){
    ramasse_miette_parcourir_et_marquer(env) ;
    ramasse_miettes_liberer();
}

int longueur_env(sexpr env){
    int i = 0;
    sexpr liste=env;;
    for (liste ; liste!=NULL ; liste=cdr(liste)) {
        i++;
    }
    return i;
}


void valisp_stat_memoire(void){
    int nb_variables = longueur_env(environnement_global());
    afficher_stat_memoire(); 
    printf("→ %d variables\n", nb_variables);
    
}

void afficher_env(sexpr env){
    int i = 0;
    sexpr liste=env;;
    for (liste ; liste!=NULL ; liste=car(liste)) {
        printf("%s%s ->%s ", couleur_bleu, liste ,couleur_defaut);
        printf("%s%s%s\n", couleur_jaune, cdr(liste) ,couleur_defaut);
    }

}