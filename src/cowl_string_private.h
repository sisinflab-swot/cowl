/// @author Ivano Bilenchi

#ifndef COWL_STRING_PRIVATE_H
#define COWL_STRING_PRIVATE_H

#include "cowl_string.h"
#include "khash_utils.h"

COWL_BEGIN_DECLS

KHASH_MAP_UTILS_DECL(CowlStringMap, char const*, CowlString*);

struct CowlString {
    char const *cstring;
    size_t length;
    uint32_t ref_count;
};

CowlString* cowl_string_alloc(char const *cstring, size_t length);
void cowl_string_free(CowlString *string);

COWL_END_DECLS

#endif // COWL_STRING_PRIVATE_H
