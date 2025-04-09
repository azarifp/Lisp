#ifndef TYPES_H
#define TYPES_H


typedef int bool ;
/* struct valisp_object ; */
typedef struct valisp_object* sexpr ;
sexpr new_integer(int i) ;
bool integer_p (sexpr val) ;

#endif