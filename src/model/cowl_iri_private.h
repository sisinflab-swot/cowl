/// @author Ivano Bilenchi

#ifndef COWL_IRI_PRIVATE_H
#define COWL_IRI_PRIVATE_H

#include "cowl_iri.h"

COWL_BEGIN_DECLS

struct CowlIRI {
    cowl_uint_t ref_count;
    CowlString *ns;
    CowlString *rem;
};

#define COWL_IRI_INIT(NS, REM) { .ref_count = 1, .ns = ((NS)), .rem = ((REM)) }

#define cowl_iri_ref_get(i) (((struct CowlIRI *)(i))->ref_count)
#define cowl_iri_ref_incr(i) (++cowl_iri_ref_get(i), (i))
#define cowl_iri_ref_decr(i) (--cowl_iri_ref_get(i))

COWL_END_DECLS

#endif // COWL_IRI_PRIVATE_H
