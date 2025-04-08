/* Include the header for using it for writing my code on 32bits */
#include <stdint.h>
#include <stdio.h>

/* I declare a variable called bloc for  Unsigned 32-bit integer */
typedef uint32_t bloc;

/* So i need to code my adresse on 15bits so i consider 15 case of 32bits */
/* That makes it 2^15 */
#define TAILLE_MEMOIRE_DYNAMIQUE (1<<15)



bloc MEMOIRE_DYNAMIQUE[TAILLE_MEMOIRE_DYNAMIQUE] ;

void initialiser_memoire_dynamique(void) {

	MEMOIRE_DYNAMIQUE[0] = ( (1<<15) - 1 ) ;
	MEMOIRE_DYNAMIQUE[TAILLE_MEMOIRE_DYNAMIQUE - 1] = ((1<<16) -1 ) ;

}



bloc cons_bloc(int rm, int precedant, int libre, int suivant) {
	bloc cons_bloc = 0 ;
	int masque = (1 << 16) - 1 ;
	cons_bloc |= ( rm & 1 ) << 31 ;
	cons_bloc |= (precedant & masque ) << 30 ;
	cons_bloc |= (libre & 1) << 15 ;
	cons_bloc |= (suivant & masque) ;
	return cons_bloc ;
}


int bloc_suivant(int i) {
    return (MEMOIRE_DYNAMIQUE[i] >> 30) & 1;
}



int bloc_precedant(int i) {
	return MEMOIRE_DYNAMIQUE[i] & ((1<<30) - 1) ;
}

int usage_bloc(int i){
    return (MEMOIRE_DYNAMIQUE[i] >> 15) & 1;
}

int rm_bloc(int i) {
    return (MEMOIRE_DYNAMIQUE[i] >> 31) & 1;
}



int taille_bloc(int i) {
	int suivant = bloc_suivant( i ) ;
	int taille ;
	if (usage_bloc(i)) {
		taille = 0 ;
	}
	else if (rm_bloc(i)) {
		taille = 0 ;
	}
	else if (i == TAILLE_MEMOIRE_DYNAMIQUE - 1) {
		taille = 0 ;
	}
	else if (i == 0) {
		taille = 0 ;
	}
	else
	{
		taille = suivant - i - 1 ; 
	}

 	return taille ;	
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


void *allocateur_malloc(size_t size) {
    return NULL;
}

void allocateur_free(void *ptr) {
    
}

int ramasse_miette_poser_marque(void *ptr) {
    return 0;
}

void ramasse_miette_liberer(void) {
}
