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

