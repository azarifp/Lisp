#include <stdlib.h>
#ifndef ALLOCATEUR_H
#define ALLOCATEUR_H





void initialiser_memoire_dynamique(void);
void *allocateur_malloc(size_t size) ;
void afficher_stat_memoire(void);
void afficher_stat_memoire_bref(void);
void info_bloc(size_t i);
void afficher_memoire(void);
int taille_bloc(int i);


#endif
  
