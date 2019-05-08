/// @author Ivano Bilenchi

#ifndef COWL_PARSER_TYPES_H
#define COWL_PARSER_TYPES_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef cowl_struct(CowlYYString) {
    cowl_uint_t length;
    char const *cstring;
} CowlYYString;

#define cowl_yystring_init(CSTR, LEN) ((CowlYYString){ .cstring = (CSTR), .length = (LEN) })

COWL_END_DECLS

#endif // COWL_PARSER_TYPES_H
