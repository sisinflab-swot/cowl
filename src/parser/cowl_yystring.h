/// @author Ivano Bilenchi

#ifndef COWL_YYSTRING_H
#define COWL_YYSTRING_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlYYString {
    char const *cstring;
    uint32_t length;
} CowlYYString;

#define COWL_YY_STRING_INIT(CSTR, LEN) ((CowlYYString){ .cstring = (CSTR), .length = (LEN) })

COWL_END_DECLS

#endif // COWL_YYSTRING_H
