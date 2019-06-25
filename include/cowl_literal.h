/// @author Ivano Bilenchi

#ifndef COWL_LITERAL_H
#define COWL_LITERAL_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlLiteral);
cowl_struct_decl(CowlString);

cowl_struct_decl(CowlLiteral);

CowlLiteral* cowl_literal_get(CowlDatatype *dt, CowlString *value, CowlString *lang);
CowlLiteral* cowl_literal_retain(CowlLiteral *literal);
void cowl_literal_release(CowlLiteral *literal);

CowlDatatype* cowl_literal_get_datatype(CowlLiteral *literal);
CowlString* cowl_literal_get_value(CowlLiteral *literal);
CowlString* cowl_literal_get_lang(CowlLiteral *literal);

CowlString* cowl_literal_to_string(CowlLiteral *literal);
bool cowl_literal_equals(CowlLiteral *lhs, CowlLiteral *rhs);
cowl_uint_t cowl_literal_hash(CowlLiteral *literal);

bool cowl_literal_iterate_signature(CowlLiteral *literal, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_LITERAL_H
