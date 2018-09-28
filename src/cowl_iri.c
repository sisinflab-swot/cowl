/// @author Ivano Bilenchi

#include <string.h>

#include "cowl_iri_private.h"
#include "cowl_hash_utils.h"
#include "cowl_string_private.h"

CowlIRI* cowl_iri_alloc(CowlString const *ns, CowlString const *rem) {
    CowlIRI iri_init = { .ns = ns, .rem = rem };
    CowlIRI *iri = malloc(sizeof(*iri));
    memcpy(iri, &iri_init, sizeof(*iri));
    return iri;
}

void cowl_iri_free(CowlIRI *iri) {
    if (!iri) return;
    cowl_string_release((CowlString *)iri->ns);
    cowl_string_release((CowlString *)iri->rem);
    free(iri);
}

CowlString const* cowl_iri_ns(CowlIRI const *iri) {
    return iri->ns;
}

CowlString const* cowl_iri_rem(CowlIRI const *iri) {
    return iri->rem;
}

bool cowl_iri_equals(CowlIRI const *a, CowlIRI const *b) {
    return (a == b || (cowl_string_equals(a->ns, b->ns) &&
                       cowl_string_equals(a->rem, b->rem)));
}

uint32_t cowl_iri_hash(CowlIRI const *iri) {
    return cowl_hash_2(COWL_HASH_INIT_IRI,
                       cowl_string_hash(iri->ns),
                       cowl_string_hash(iri->rem));
}
