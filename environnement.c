#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memoire.h"
#include "allocateur.h"
#include "types.h"
#include "erreur.h"
#include "environnement.h"
#include "types.h"

sexpr ENV=NULL;

sexpr environnement_global(void) {
    return ENV;
}

void initialiser_memoire(void){
    sexpr t;
    initialiser_memoire_dynamique();
    t = new_symbol("t");
    ENV = cons(t,t);
}

int trouver_variable(sexpr env, sexpr variable, sexpr *resultat){
    sexpr liste,a,nom,val;
    char* nom_var = get_symbol(variable);
    for (liste=env; liste!=NULL ; liste=cdr(liste)) {
        a = car(liste); /* a est de la forme (nom . valeur) */
        nom = car(a);
        val = cdr(a);
        if(symbol_match_p(nom,nom_var)){
            *resultat = val;
            return 0;
        }
    }
    return -1;
}

int modifier_variable(sexpr env, sexpr variable, sexpr valeur) {
    sexpr liste,a,nom;
    char* nom_var = get_symbol(variable);
    for (liste=env; liste!=NULL ; liste=cdr(liste)) {
        a = car(liste); /* a est de la forme (nom . valeur) */
        nom = car(a);
        if(symbol_match_p(nom,nom_var)){
            set_cdr(a,valeur);
            return 0;
        }
    }
    return -1;
}



void definir_variable_globale(sexpr variable, sexpr valeur) {
    sexpr s;
    if (modifier_variable(ENV, variable, valeur) == -1){
    s = cons(variable,valeur);
    cons(s,ENV);
    }

}

void charger_une_primitive(char* nom, sexpr (*prim)(sexpr, sexpr)){
    sexpr s;
    s = new_primitive(prim);
    definir_variable_globale(new_string(nom),s);
    
}

void charger_une_speciale(char* nom, sexpr (*prim)(sexpr, sexpr)){
    sexpr s;
    s = new_special(prim);
    definir_variable_globale(new_string(nom),s);
    
}