#define ENV (NULL);

sexpr environnement_global(void) {
    return ENV;
}

void initialiser_memoire(void){
    initialiser_memoire_dynamique();
    sexpr t = new_symbol("t");
    ENV = cons(t,t);
}

int trouver_variable(sexpr env, sexpr variable, sexpr *resultat){
    for (liste=env; liste!=NULL ; liste=cdr(liste)) {
        a = car(liste); /* a est de la forme (nom . valeur) */
        nom = car(a);
        val = cdr(a);
        if(variable==nom){
            *resultat = val;
            return 0;
        }
    }
    return -1;
}

int modifier_variable(sexpr env, sexpr variable, sexpr valeur) {
    sexpr resultat;
    if (trouver_variable(env, variable, &resultat) == 0) {
        set_cdr(resultat, valeur);
        return 0;
    }
    return -1;
}
