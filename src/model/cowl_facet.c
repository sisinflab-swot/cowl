/// @author Ivano Bilenchi

#include "cowl_facet_private.h"
#include "cowl_iri.h"
#include "cowl_vocab.h"

static CowlIRI *cowl_facet_iris[CF_COUNT] = { NULL };

void cowl_facet_init(void) {
    CowlXSDVocab *v = cowl_xsd_vocab_get();
    cowl_facet_iris[CF_NONE] = NULL;
    cowl_facet_iris[CF_LENGTH] = v->iri.length;
    cowl_facet_iris[CF_MIN_LENGTH] = v->iri.min_length;
    cowl_facet_iris[CF_MAX_LENGTH] = v->iri.max_length;
    cowl_facet_iris[CF_PATTERN] = v->iri.pattern;
    cowl_facet_iris[CF_MIN_INCLUSIVE] = v->iri.min_inclusive;
    cowl_facet_iris[CF_MIN_EXCLUSIVE] = v->iri.min_exclusive;
    cowl_facet_iris[CF_MAX_INCLUSIVE] = v->iri.max_inclusive;
    cowl_facet_iris[CF_MAX_EXCLUSIVE] = v->iri.max_exclusive;
    cowl_facet_iris[CF_TOTAL_DIGITS] = v->iri.total_digits;
    cowl_facet_iris[CF_FRACTION_DIGITS] = v->iri.fraction_digits;
    cowl_facet_iris[CF_LANG_RANGE] = v->iri.lang_range;
}

void cowl_facet_deinit(void) { /* No-op */ }

CowlFacet cowl_facet_from_iri(CowlIRI *iri) {
    cowl_facet_foreach(facet) { if (cowl_iri_equals(iri, cowl_facet_iris[facet])) return facet; }
    return CF_NONE;
}

CowlIRI* cowl_facet_get_iri(CowlFacet facet) {
    return cowl_iri_retain(cowl_facet_iris[facet]);
}
