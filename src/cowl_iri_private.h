/// @author Ivano Bilenchi

#ifndef COWL_IRI_PRIVATE_H
#define COWL_IRI_PRIVATE_H

#include "cowl_iri.h"

COWL_BEGIN_DECLS

typedef struct CowlIRI {
    CowlString const *ns;
    CowlString const *rem;
} CowlIRI;

COWL_END_DECLS

#endif // COWL_IRI_PRIVATE_H
