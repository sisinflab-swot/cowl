/// @author Ivano Bilenchi

#ifndef COWL_DATATYPE_RESTR_H
#define COWL_DATATYPE_RESTR_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_hash_decl(CowlFacetRestrSet);

cowl_struct_decl(CowlDatatypeRestr);

CowlDatatypeRestr* cowl_datatype_restr_get(CowlDatatype *datatype, CowlFacetRestrSet *restrictions);
CowlDatatypeRestr* cowl_datatype_restr_retain(CowlDatatypeRestr *restr);
void cowl_datatype_restr_release(CowlDatatypeRestr *restr);

CowlDatatype* cowl_datatype_restr_get_datatype(CowlDatatypeRestr *restr);
CowlFacetRestrSet* cowl_datatype_restr_get_restrictions(CowlDatatypeRestr *restr);

bool cowl_datatype_restr_equals(CowlDatatypeRestr *lhs, CowlDatatypeRestr *rhs);
cowl_uint_t cowl_datatype_restr_hash(CowlDatatypeRestr *restr);

bool cowl_datatype_restr_iterate_signature(CowlDatatypeRestr *restr, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_DATATYPE_RESTR_H
