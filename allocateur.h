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
int pointeur_vers_indice(void *ptr);
int ramasse_miettes_lire_marque(void *ptr);
int ramasse_miettes_poser_marque(void *ptr);
int bloc_libre(int i);
void ramasse_miettes_liberer(void);
void ramasse_miette_parcourir_et_marquer(sexpr s);


#endif
  
