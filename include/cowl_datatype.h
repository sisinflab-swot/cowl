/// @author Ivano Bilenchi

#ifndef COWL_DATATYPE_H
#define COWL_DATATYPE_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);

cowl_struct_decl(CowlDatatype);

CowlDatatype* cowl_datatype_get(CowlIRI *iri);
CowlDatatype* cowl_datatype_retain(CowlDatatype *prop);
void cowl_datatype_release(CowlDatatype *prop);

CowlIRI* cowl_datatype_get_iri(CowlDatatype *prop);

bool cowl_datatype_equals(CowlDatatype *lhs, CowlDatatype *rhs);
cowl_uint_t cowl_datatype_hash(CowlDatatype *prop);

bool cowl_datatype_iterate_signature(CowlDatatype *prop, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_DATATYPE_H
