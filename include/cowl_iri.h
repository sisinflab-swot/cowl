/// @author Ivano Bilenchi

#ifndef COWL_IRI_H
#define COWL_IRI_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlString const CowlString;

typedef struct CowlIRI const CowlIRI;

CowlIRI* cowl_iri_parse(char const *cstring, uint32_t length);
CowlIRI* cowl_iri_get(CowlString *ns, CowlString *rem);
CowlIRI* cowl_iri_retain(CowlIRI *iri);
void cowl_iri_release(CowlIRI *iri);

CowlString* cowl_iri_get_ns(CowlIRI *iri);
CowlString* cowl_iri_get_rem(CowlIRI *iri);

bool cowl_iri_equals(CowlIRI *lhs, CowlIRI *rhs);
uint32_t cowl_iri_hash(CowlIRI *iri);

CowlIRI* cowl_iri_from_cstring(char const *cstring);
CowlIRI* cowl_iri_from_ns_rem(char const *ns, char const *rem);

COWL_END_DECLS

#endif // COWL_IRI_H
