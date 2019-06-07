/// @author Ivano Bilenchi

#ifndef COWL_STRING_PRIVATE_H
#define COWL_STRING_PRIVATE_H

#include "cowl_string.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlString) {
    CowlHashObject super;
    cowl_uint_t length;
    char const *cstring;
};

#define COWL_STRING_INIT(S, L, H) \
    { .super = COWL_HASH_OBJECT_INIT(H), .cstring = (S), .length = (L) }

void cowl_string_split_two(char const *cstring, cowl_uint_t length,
                           char character, CowlString **out);

COWL_END_DECLS

#endif // COWL_STRING_PRIVATE_H
