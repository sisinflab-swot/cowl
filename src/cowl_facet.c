/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_facet_private.h"
#include "cowl_iri.h"
#include "cowl_rdf_vocab.h"
#include "cowl_xsd_vocab.h"

static CowlIRI *cowl_facet_iris[COWL_FACET_COUNT] = { NULL };

cowl_ret cowl_facet_init(void) {
    CowlXSDVocab *xsd = cowl_xsd_vocab_get();
    CowlRDFVocab *rdf = cowl_rdf_vocab_get();
    cowl_facet_iris[COWL_FACET_NONE] = NULL;
    cowl_facet_iris[COWL_FACET_LENGTH] = xsd->iri.length;
    cowl_facet_iris[COWL_FACET_MIN_LENGTH] = xsd->iri.min_length;
    cowl_facet_iris[COWL_FACET_MAX_LENGTH] = xsd->iri.max_length;
    cowl_facet_iris[COWL_FACET_PATTERN] = xsd->iri.pattern;
    cowl_facet_iris[COWL_FACET_MIN_INCL] = xsd->iri.min_inclusive;
    cowl_facet_iris[COWL_FACET_MIN_EXCL] = xsd->iri.min_exclusive;
    cowl_facet_iris[COWL_FACET_MAX_INCL] = xsd->iri.max_inclusive;
    cowl_facet_iris[COWL_FACET_MAX_EXCL] = xsd->iri.max_exclusive;
    cowl_facet_iris[COWL_FACET_TOTAL_DIGITS] = xsd->iri.total_digits;
    cowl_facet_iris[COWL_FACET_FRAC_DIGITS] = xsd->iri.fraction_digits;
    cowl_facet_iris[COWL_FACET_LANG_RANGE] = rdf->iri.lang_range;
    return COWL_OK;
}

void cowl_facet_deinit(void) { /* No-op */ }

CowlFacet cowl_facet_from_iri(CowlIRI *iri) {
    cowl_facet_foreach(facet) { if (cowl_iri_equals(iri, cowl_facet_iris[facet])) return facet; }
    return COWL_FACET_NONE;
}

CowlIRI* cowl_facet_get_iri(CowlFacet facet) {
    return cowl_iri_retain(cowl_facet_iris[facet]);
}
