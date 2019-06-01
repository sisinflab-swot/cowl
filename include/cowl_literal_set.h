/// @author Ivano Bilenchi

#ifndef COWL_LITERAL_SET_H
#define COWL_LITERAL_SET_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlLiteral);

UHASH_SET_DECL(CowlLiteralSet, CowlLiteral*)
cowl_hash_decl(CowlLiteralSet);

void cowl_literal_set_free(CowlLiteralSet *set);

COWL_END_DECLS

#endif // COWL_LITERAL_SET_H
