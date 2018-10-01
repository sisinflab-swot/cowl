/// @author Ivano Bilenchi

#ifndef COWL_CLASS_H
#define COWL_CLASS_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlIRI CowlIRI;

typedef struct CowlClass CowlClass;

CowlIRI const* cowl_class_get_iri(CowlClass const *cls);

bool cowl_class_equals(CowlClass const *lhs, CowlClass const *rhs);
uint32_t cowl_class_hash(CowlClass const *cls);

COWL_END_DECLS

#endif // COWL_CLASS_H
