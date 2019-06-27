/// @author Ivano Bilenchi

#ifndef COWL_CLASS_H
#define COWL_CLASS_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);

cowl_struct_decl(CowlClass);

CowlClass* cowl_class_get(CowlIRI *iri);
CowlClass* cowl_class_retain(CowlClass *cls);
void cowl_class_release(CowlClass *cls);

CowlIRI* cowl_class_get_iri(CowlClass *cls);

bool cowl_class_equals(CowlClass *lhs, CowlClass *rhs);
cowl_uint_t cowl_class_hash(CowlClass *cls);

bool cowl_class_iterate_signature(CowlClass *cls, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_CLASS_H
