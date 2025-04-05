typedef uint_32 bloc;

#define TAILLE_MEMOIRE_DYNAMIQUE (1<<15)

bloc MEMOIRE_DYNAMIQUE[TAILLE_MEMOIRE_DYNAMIQUE] ;

void initialsier_memoire_dynamique() {

	MEMOIRE_DYNAMIQUE[0] = ( (1<<15) - 1 ) ;
	MEMOIRE_DYNAMIQUE[TAILLE_MEMOIRE_DYNAMIQUE - 1] = ((1<<16) -1 ) ;

}



bloc cons_bloc(int rm, int precedant, int libre, int suivant) {
	bloc cons_bloc = 0 ; 
	cons_bloc = ( rm & 1 ) << 31 ;
	cons_bloc = (precedant & 1 ) << 30 ;
	cons_bloc = (libre & 1) << 15 ;
	cons_bloc = (suivant & 1 ) ;
	return cons_bloc ;
}


int bloc_suivant(int i) {
	return MEMOIRE_DYNAMIQUE[i] & ((1<<16) - 1) ;
}


int bloc_precedant(int i) {
	return MEMOIRE_DYNAMIQUE[i] & ((1<<30) - 1) ;
}

int usage_bloc(int i){
	return MEMOIRE_DYNAMIQUE[i] & (1<<15) ;
}

int rm_bloc(int i) {	
	return MEMOIRE_DYNAMIQUE[i] & (1<<31) ;
}


int taille_bloc(int i) {
	int bloc_suivant = bloc_suivant( i ) ;
	int taille = i - bloc_suivant ;
	if (taille == 0 ) {
		return -1;
	}
	else {
		return taille ;
	}
}


