/// @author Ivano Bilenchi

#ifndef COWL_FACET_H
#define COWL_FACET_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);

typedef enum CowlFacet {
    COWL_FACET_NONE,
    COWL_FACET_LENGTH,
    COWL_FACET_MIN_LENGTH,
    COWL_FACET_MAX_LENGTH,
    COWL_FACET_PATTERN,
    COWL_FACET_MIN_INCL,
    COWL_FACET_MIN_EXCL,
    COWL_FACET_MAX_INCL,
    COWL_FACET_MAX_EXCL,
    COWL_FACET_TOTAL_DIGITS,
    COWL_FACET_FRAC_DIGITS,
    COWL_FACET_LANG_RANGE,

    // Markers
    COWL_FACET_COUNT,
    COWL_FACET_FIRST = COWL_FACET_NONE
} CowlFacet;

CowlFacet cowl_facet_from_iri(CowlIRI *iri);
CowlIRI* cowl_facet_get_iri(CowlFacet facet);

#define cowl_facet_foreach(var_name) \
    for (CowlFacet var_name = COWL_FACET_FIRST; (var_name) < COWL_FACET_COUNT; ++(var_name))

COWL_END_DECLS

#endif // COWL_FACET_H
