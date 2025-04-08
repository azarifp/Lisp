#ifndef ALLOCATEUR_H
#define ALLOCATEUR_H





void initialiser_memoire_dynamique(void);
void *allocateur_malloc(size_t size) ;
int ramasse_miette_lire_marque(void * ptr);
void afficher_stat_memoire(void);
void afficher_stat_memoire_bref(void);
int ramasse_miette_poser_marque(void * ptr);
void info_bloc(size_t i);
void afficher_memoire(void);
int taille_bloc(int i);
void ramasse_miette_liberer(void);
void allocateur_free (void * ptr) ;


#endif  
