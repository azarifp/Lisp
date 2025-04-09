#include "allocateur.h"
#include "erreur.h"

void *valisp_malloc(size_t size) {
    void *p = allocateur_malloc(size) ;
    if(p == NULL) ERREUR_FATALE("ATTENTION PLUS D'ESPACE !!!") ;
    else {
        return p;
    }
}
