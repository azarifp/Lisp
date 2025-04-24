#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "allocateur.h"
#include "erreur.h"

typedef uint32_t bloc;

#define TAILLE_MEMOIRE_DYNAMIQUE (1<<15)



bloc MEMOIRE_DYNAMIQUE[TAILLE_MEMOIRE_DYNAMIQUE] ;

void initialiser_memoire_dynamique(void) {

	MEMOIRE_DYNAMIQUE[0] = ( (1<<15) - 1 ) ;
	MEMOIRE_DYNAMIQUE[TAILLE_MEMOIRE_DYNAMIQUE - 1] = ((1<<16) -1 ) ;

}



bloc cons_bloc(int rm, int precedant, int libre, int suivant) {

	return (rm << 31) | (precedant << 16) | (libre << 15) | suivant ;
}

bloc masque = (1 << 15) - 1 ;

int bloc_suivant(int i) {
	return (MEMOIRE_DYNAMIQUE[i]) & masque;
}



int bloc_precedant(int i) {
	return (MEMOIRE_DYNAMIQUE[i]>>16) & masque ;
}

int usage_bloc(int i){
    return (MEMOIRE_DYNAMIQUE[i] >> 15) & 1;
}

int rm_bloc(int i) {
    return (MEMOIRE_DYNAMIQUE[i] >> 31) & 1;
}



int taille_bloc(int i) {
	int suivant = bloc_suivant(i) ;
    if (i == suivant) {
        return 0 ;
    }
    else {
        return suivant - i - 1 ;
    }

}
int octets_vers_case(size_t size) {
    if ( size % sizeof(bloc) == 0) {
        return size/ sizeof(bloc) ;
    }
    else {
    return ( size/sizeof(bloc) ) + 1 ;
    }
}

int rechercher_bloc_libre(size_t size) {
    
    int i;
    for( i = 0 ; i != bloc_suivant(i) ; i = bloc_suivant(i) ) {
        
        if (taille_bloc(i) >= size && (!usage_bloc(i))) return i ;

    }
    return -1;
}
void *allocateur_malloc(size_t size) {
    int p,i,n,j,s;
    int taille_dispo;
    size = octets_vers_case(size) ;
    i = rechercher_bloc_libre(size) ;
    taille_dispo = taille_bloc(i) ;
    
   

    if (i == -1) return NULL ;

    if(taille_dispo > size) {
        p = bloc_precedant(i) ;
        j = bloc_suivant(i) ;
        s = bloc_suivant(j) ;
        n = i + size + 1 ;


        MEMOIRE_DYNAMIQUE[i] = cons_bloc(0,p,1,n) ;
        MEMOIRE_DYNAMIQUE[n] = cons_bloc(0,i,0,j) ;
        MEMOIRE_DYNAMIQUE[j] = cons_bloc(0,n,1,s) ;
    }
        else {
            p = bloc_precedant(i) ;
            j = bloc_suivant(i) ;
            MEMOIRE_DYNAMIQUE[i] = cons_bloc(0,p,1,j);
        }

        return &MEMOIRE_DYNAMIQUE[i + 1] ;
    }


void info_bloc(size_t i) {
    int t = taille_bloc(i);
    int p = bloc_precedant(i);
    int s = bloc_suivant(i);
    char * u = usage_bloc(i) ? "[x]" : "[ ]";

    printf("%s %p %5d → %ld → %-5d (%u)\n",
           u, (void *) &MEMOIRE_DYNAMIQUE[i], p, i, s, t);
}

void afficher_memoire(void) {
    int i;
    for (i=0; bloc_suivant(i) != i; i = bloc_suivant(i)) {
	printf("[%5d] ",i);
	info_bloc(i);
    }
    printf("[%5d] ",i);
    info_bloc(i);
}

void afficher_stat_memoire(void) {
    size_t i = 0;
    int t = TAILLE_MEMOIRE_DYNAMIQUE;
    int n = 0;
    int b = 0;
    int a = 0;
    for (i=0; bloc_suivant(i) != i; i = bloc_suivant(i)) {
        n+=1;
        if (usage_bloc(i)) {
            a += taille_bloc(i) + 1;
            b += 1;
        }
    }
    printf("%d/%d (%.2f %%) %d/%d blocs alloués", a, t, (100.*a)/t, b,n);
}

void afficher_stat_memoire_bref(void) {
    size_t i = 0;
    int t = TAILLE_MEMOIRE_DYNAMIQUE;
    int n = 0;
    int b = 0;
    int a = 0;
    for (i=0; bloc_suivant(i) != i; i = bloc_suivant(i)) {
        n+=1;
        if (usage_bloc(i)) {
            a += taille_bloc(i) + 1;
            b += 1;
        }
    }
    printf("%.2f%%", (100.*a)/t);
}

int pointeur_vers_indice(void *ptr) {
    int i =  (bloc*) ptr - MEMOIRE_DYNAMIQUE - 1;
    if (i < 0 || i >= TAILLE_MEMOIRE_DYNAMIQUE) {
        ERREUR_FATALE("Indice de MEM invalide");
    }
    return i;
}


int ramasse_miettes_lire_marque(void *ptr){
    
    return rm_bloc(pointeur_vers_indice(ptr));
}

int ramasse_miettes_poser_marque(void *ptr) {
    if (ramasse_miettes_lire_marque(ptr)) {
        ERREUR_FATALE("Erreur : bloc déjà marqué");
    }
    else {
        int i;
        i=pointeur_vers_indice(ptr);
        MEMOIRE_DYNAMIQUE[i] = cons_bloc(1, bloc_precedant(i), usage_bloc(i), bloc_suivant(i));
        return 0;
    }

}


int bloc_libre(int i){
    if (i==bloc_suivant(i) || rm_bloc(i)){
        return 0;
    }
    return 1;
}


void ramasse_miettes_liberer(void) {
    int i,j,p;
    i = 0;
    
    for(i=0 ; i != bloc_suivant(i); i=bloc_suivant(i)) {
        
        if (bloc_libre(i)){
            
            p = bloc_precedant(i);
            for (j = i; j != bloc_libre(j); i = bloc_suivant(i)){
                    MEMOIRE_DYNAMIQUE[i] = cons_bloc(0, p, 0, bloc_suivant(j));
                    MEMOIRE_DYNAMIQUE[j] = cons_bloc(0, i, 1,bloc_suivant(j));
                    i=j;
                }
            }
        else{
            MEMOIRE_DYNAMIQUE[j] = cons_bloc(0, p, 1, bloc_suivant(j));

        }
}
}


