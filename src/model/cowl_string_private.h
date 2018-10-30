/// @author Ivano Bilenchi

#ifndef COWL_STRING_PRIVATE_H
#define COWL_STRING_PRIVATE_H

#include "cowl_string.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

struct CowlString {
    CowlObject super;
    uint32_t length;
    char const *cstring;
};

#define COWL_STRING_INIT(S, L, H) { .super = COWL_OBJECT_INIT(H), .cstring = (S), .length = (L) }

#define cowl_string_ref_get(s) cowl_object_ref_get(s)
#define cowl_string_ref_incr(s) cowl_object_retain(s)
#define cowl_string_ref_decr(s) cowl_object_release(s)

#define cowl_string_hash_get(s) cowl_object_hash_get(s)

void cowl_string_split_two(char const *cstring, uint32_t length, char character, CowlString **out);

COWL_END_DECLS

#endif // COWL_STRING_PRIVATE_H
