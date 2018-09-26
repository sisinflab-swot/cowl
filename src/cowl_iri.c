/// @author Ivano Bilenchi

#include <string.h>

#include "cowl_iri.h"
#include "cowl_string.h"

CowlIRI* cowl_iri_alloc(CowlString *ns, CowlString *rem) {
    CowlIRI iri_init = { .ns = ns, .rem = rem };
    CowlIRI *iri = malloc(sizeof(*iri));
    memcpy(iri, &iri_init, sizeof(*iri));
    return iri;
}

void cowl_iri_free(CowlIRI *iri) {
    if (!iri) return;
    cowl_string_release(iri->ns);
    cowl_string_release(iri->rem);
    free(iri);
}

bool cowl_iri_equals(CowlIRI *iri, CowlIRI *other) {
    return (iri == other || (cowl_string_equals(iri->ns, other->ns) &&
                             cowl_string_equals(iri->rem, other->rem)));
}
