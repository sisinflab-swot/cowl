/// @author Ivano Bilenchi

#ifndef COWL_STRING_H
#define COWL_STRING_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlString CowlString;

CowlString* cowl_string_get(char const *cstring, size_t length, bool owned);
void cowl_string_release(CowlString *string);

char const* cowl_string_cstring(CowlString const *string);
size_t cowl_string_length(CowlString const *string);

bool cowl_string_equals(CowlString const *string, CowlString const *other);
uint32_t cowl_string_hash(CowlString const *string);

COWL_END_DECLS

#endif // COWL_STRING_H
