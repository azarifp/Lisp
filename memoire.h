#include <stdlib.h>


#ifndef MEMOIRE_H
#define MEMOIRE_H

void *valisp_malloc(size_t size);
void valisp_ramasse_miettes(sexpr env);
int longueur_env(sexpr env);
void afficher_env(sexpr env);

#endif
