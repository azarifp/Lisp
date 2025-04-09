#include <stdlib.h>
#include <std
#include "memoire.h"
#include "types.h"


typedef enum {
    entier ,
    chaine ,
    symbole ,
    couple ,
    prim ,
    spec
} valisp_type ;

typedef struct {
    sexpr car ;
    sexpr cdr ;
} valips_cons ;

typedef union {
    int INTEGER ;
    char* STRING ;
    valips_cons CONS ;
    sexpr (*PRIMITIVE) (sexpr,sexpr);
} valisp_data ;

struct valisp_object {
    valisp_type type ;
    valisp_data data ;
};

sexpr new_integer(int i) {

   sexpr s = valisp_malloc(sizeof(struct valisp_object)) ;
   s->type = entier ;
   s->data.INTEGER = i ;
   return s ;

}

bool integer_p (sexpr val) {
    return (val != NULL) && val->type == entier ;
}

int get_integer(sexpr val) {
    return val->data.INTEGER ;
}

void afficher(sexpr val) {

    if(val != NULL ) {
        printf("NILL") ;
    }
    switch (val->type) {
        case entier :
        printf("ENTIER");
        case chaine :
        printf("CHAINE");
        case symbole :
        printf("SYMBOLE") ;
        case couple :
        printf("COUPLE") ;
        case prim :
        printf("PRIM") ;
        case spec :
        printf("SPEC") ;

    }

}

