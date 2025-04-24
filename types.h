#ifndef TYPES_H
#define TYPES_H


typedef int bool ;
/* struct valisp_object ; */
typedef struct valisp_object* sexpr ;
sexpr new_integer(int i) ;
bool integer_p (sexpr val) ;
int get_integer(sexpr val) ;
void afficher(sexpr val) ;
char* chaine_vers_memoire(const char *c) ;
sexpr new_string(char * c) ;
sexpr new_symbol(char * c) ;
char* get_symbol(sexpr val) ;
char* get_string(sexpr val) ;
bool string_p(sexpr val) ;
sexpr cons(sexpr e1 , sexpr e2);
bool cons_p(sexpr e);
bool list_p(sexpr e);
sexpr car(sexpr e);
sexpr cdr(sexpr e);
sexpr set_car(sexpr e, sexpr nouvelle);
sexpr set_cdr(sexpr e, sexpr nouvelle);
bool symbol_p(sexpr val) ;
bool symbol_match_p(sexpr val, const char *chaine) ;
sexpr new_primitive(sexpr (*prim) (sexpr,sexpr)) ;
sexpr new_special(sexpr (*p)(sexpr, sexpr));
bool prim_p (sexpr val);
bool spec_p (sexpr val);
bool sexpr_equal(sexpr e1, sexpr e2);
#endif
