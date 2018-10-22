/// @author Ivano Bilenchi

#ifndef COWL_IRI_H
#define COWL_IRI_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlString CowlString;

typedef struct CowlIRI CowlIRI;

CowlIRI const* cowl_iri_get(CowlString const *ns, CowlString const *rem);
CowlIRI const* cowl_iri_retain(CowlIRI const *iri);
void cowl_iri_release(CowlIRI const *iri);

CowlString const* cowl_iri_get_ns(CowlIRI const *iri);
CowlString const* cowl_iri_get_rem(CowlIRI const *iri);

bool cowl_iri_equals(CowlIRI const *lhs, CowlIRI const *rhs);
uint32_t cowl_iri_hash(CowlIRI const *iri);

COWL_END_DECLS

#endif // COWL_IRI_H
