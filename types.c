#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memoire.h"
#include "types.h"
#include "erreur.h"


typedef enum {
    entier,
    chaine,
    symbole,
    couple,
    prim,
    spec
} valisp_type;

typedef struct {
    sexpr car;
    sexpr cdr;
} valips_cons;

typedef union {
    int INTEGER;
    char* STRING;
    valips_cons CONS;
    sexpr (*PRIMITIVE) (sexpr,sexpr);
} valisp_data;

struct valisp_object {
    valisp_type type;
    valisp_data data;
};

/* [FONCTIONS OF INTEGER] */

/*     [LETS BEGIN]     */

 sexpr new_integer(int i) {
   sexpr s = valisp_malloc(sizeof(struct valisp_object));
   s->type = entier;
   s->data.INTEGER =i;
   return s ;
}

bool integer_p (sexpr val) {
    return (val != NULL) && (val->type == entier);
}

int get_integer(sexpr val) {
    return val->data.INTEGER;
}


/*     [END]     */





/* [FONCTIONS OF STRING] */

/*     [LETS BEGIN]     */


char* chaine_vers_memoire(const char *c) {
    char *chaine = valisp_malloc( sizeof(char)*(strlen(c)+1) );    
    strcpy(chaine,c); 
    return chaine ;
} 

sexpr new_string(char * c) {
    sexpr s = valisp_malloc(sizeof(struct valisp_object)) ;
    s->type = chaine ;
    s->data.STRING = chaine_vers_memoire(c) ;
    return s;
}

sexpr new_symbol(char * c) {
    sexpr s = valisp_malloc(sizeof(struct valisp_object)) ;
    if(strcmp(c,"nil")==0) return NULL;
    s->type = symbole ;
    s->data.STRING = chaine_vers_memoire(c) ;
    return s ;
}


char* get_symbol(sexpr val) {
    return (val==NULL) ? NULL : val->data.STRING ;
} 

char* get_string(sexpr val){
    return (val==NULL) ? NULL : val->data.STRING ;
}

bool string_p(sexpr val){
    return (val != NULL) && (val->type == chaine) ; 
}

bool symbol_p(sexpr val){
    return (val != NULL) && (val->type == symbole) ; 
}

bool symbol_match_p(sexpr val, const char *chaine) {
    return strcmp(val->data.STRING , chaine) == 0 ;
}


/*     [END]     */





/*  [FONCTIONS OF LIST]  */

/*      [LETS BEGIN]     */


sexpr cons(sexpr e1 , sexpr e2) {
    sexpr s = valisp_malloc(sizeof(struct valisp_object)) ;
    s->type = couple ;
    s->data.CONS.car = e1 ;
    s->data.CONS.cdr = e2 ;
    return s ;
}

bool cons_p(sexpr e) {
    return (e != NULL) && (e->type == couple) ;
}

bool list_p(sexpr e) {
    if (e == NULL) return 1 ;
    if (cons_p(e)) {
        return list_p(cdr(e)) ;
    }
    return 0;
}

sexpr car(sexpr e) {
    if (e==NULL) ERREUR_FATALE(NULL) ;
    return e->data.CONS.car ;
}

sexpr cdr(sexpr e) {
    return (e->type == couple) ? e->data.CONS.cdr : NULL ;
}

sexpr set_car(sexpr e, sexpr nouvelle) {
    if (e->type == couple) return e->data.CONS.car = nouvelle ; 
    return NULL ;
}

sexpr set_cdr(sexpr e, sexpr nouvelle) {
 
 if (e->type == couple) return e->data.CONS.cdr = nouvelle ; 
 return NULL ;
 
}



void afficher_liste(sexpr e) {
    sexpr x = car(e);
    sexpr y = cdr(e);
    afficher(x);
    if(y==NULL) return ;
    if(cons_p(y)){
        printf(" ");
        afficher_liste(y);
    }
    else{
        printf(" . ");
        afficher(y);
    }
    
}






sexpr new_primitive(sexpr (*p) (sexpr,sexpr)) {
    sexpr s = valisp_malloc(sizeof(struct valisp_object)) ;
    s->type = prim ;
    s->data.PRIMITIVE = p ;
    return s ;
}

sexpr new_special(sexpr (*p)(sexpr, sexpr)) {
    sexpr s = valisp_malloc(sizeof(struct valisp_object)) ;
    s->type = spec ;
    s->data.PRIMITIVE = p ;
    return s ;
}

bool prim_p (sexpr val) {
    return (val != NULL) && val->type == prim ;
}

bool spec_p (sexpr val) {
    return (val != NULL) && val->type == spec ;
}

sexpr run_prim(sexpr p, sexpr liste, sexpr env) {
    if (prim_p(p)) {
        return p->data.PRIMITIVE(liste, env) ; } 
        else {
            return NULL ;
        }
    }
    


    void afficher(sexpr val) {

        if(val == NULL ) {
            printf("nil");
            return;
        }
        switch (val->type) {
            case entier:
            printf("%d",get_integer(val));
            break;
            case chaine:
            printf("\"%s\"",get_string(val));
            break;
            case symbole:
            break;
            printf("%s",get_symbol(val));
            break;
            case couple:
            printf("(");
            afficher_liste(val);
            printf(")");
            break;
            case prim:
            printf("#<primitive>");
            case spec:
            printf("SPEC");
    
        }
    
    }
    


