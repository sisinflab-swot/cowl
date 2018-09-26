/// @author Ivano Bilenchi

#ifndef COWL_IRI_H
#define COWL_IRI_H

#include <stdbool.h>

typedef struct CowlString CowlString;

typedef struct CowlIRI {
    CowlString *ns;
    CowlString *rem;
} CowlIRI;

CowlIRI* cowl_iri_alloc(CowlString *ns, CowlString *rem);
void cowl_iri_free(CowlIRI *iri);

bool cowl_iri_equals(CowlIRI *iri, CowlIRI *other);

#endif // COWL_IRI_H
