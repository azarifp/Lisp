#include "primitives.h"
#include "types.h"
#include "erreur.h"
#include "primitives.h"

sexpr add_valisp(sexpr liste, sexpr val) {
    sexpr a;
    int sum = 0;
    if (liste == NULL) {
        return NULL;
    }
    while (liste != NULL) {
        a = car(liste);
        if (!integer_p(a)) {
            ERREUR_FATALE("Erreur dans la liste d'arguments");
        }
        sum += get_integer(a);
        liste = cdr(liste);
    }
    return new_integer(sum);
}

sexpr defvar_valisp(sexpr liste, sexpr env) {
    sexpr nom;
    sexpr exp;
    sexpr res;
    test_nb_parametres(liste,"defvar",2);
    nom = car(liste);
    exp = car(cdr(liste));
    if (!symbol_p(nom)) {
    erreur(TYPAGE,"defvar",
    "Le 1er paramètre doit être un symbole",
    nom);
    }
    res = eval(exp, env); /* Il faut évaluer à la main le */
    definir_variable_globale(nom,res); /* second paramètre */
    return res;
    }

sexpr setq_valisp(sexpr lis) {
    
}