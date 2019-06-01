/// @author Ivano Bilenchi

#ifndef COWL_LITERAL_SET_PRIVATE_H
#define COWL_LITERAL_SET_PRIVATE_H

#include "cowl_literal_set.h"

COWL_BEGIN_DECLS

cowl_hash_decl_mutable(CowlLiteralSet, CowlMutableLiteralSet);

bool cowl_literal_set_insert(CowlMutableLiteralSet *set, CowlLiteral *literal);

COWL_END_DECLS

#endif // COWL_LITERAL_SET_PRIVATE_H
