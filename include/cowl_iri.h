/// @author Ivano Bilenchi

#ifndef COWL_IRI_H
#define COWL_IRI_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlString);

cowl_struct_decl(CowlIRI);

CowlIRI* cowl_iri_parse(char const *cstring, cowl_uint_t length);
CowlIRI* cowl_iri_get(CowlString *ns, CowlString *rem);
CowlIRI* cowl_iri_retain(CowlIRI *iri);
void cowl_iri_release(CowlIRI *iri);

CowlString* cowl_iri_get_ns(CowlIRI *iri);
CowlString* cowl_iri_get_rem(CowlIRI *iri);

bool cowl_iri_equals(CowlIRI *lhs, CowlIRI *rhs);
cowl_uint_t cowl_iri_hash(CowlIRI *iri);

CowlIRI* cowl_iri_from_cstring(char const *cstring);
CowlIRI* cowl_iri_from_ns_rem(char const *ns, char const *rem);
CowlString* cowl_iri_to_string(CowlIRI *iri);

COWL_END_DECLS

#endif // COWL_IRI_H
