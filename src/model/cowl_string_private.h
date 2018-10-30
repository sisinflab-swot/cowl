/// @author Ivano Bilenchi

#ifndef COWL_STRING_PRIVATE_H
#define COWL_STRING_PRIVATE_H

#include "cowl_string.h"

COWL_BEGIN_DECLS

struct CowlString {
    uint32_t ref_count;
    uint32_t length;
    char const *cstring;
};

#define COWL_STRING_INIT(CSTR, LEN) { .ref_count = 1, .cstring = CSTR, .length = LEN }

#define cowl_string_ref_get(s) (((struct CowlString *)(s))->ref_count)
#define cowl_string_ref_incr(s) (++cowl_string_ref_get(s), (s))
#define cowl_string_ref_decr(s) (--cowl_string_ref_get(s))

void cowl_string_split_two(char const *cstring, uint32_t length, char character, CowlString **out);

COWL_END_DECLS

#endif // COWL_STRING_PRIVATE_H
