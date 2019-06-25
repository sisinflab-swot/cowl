/// @author Ivano Bilenchi

#ifndef COWL_FACET_H
#define COWL_FACET_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);

typedef enum CowlFacet {
    CF_NONE,
    CF_LENGTH,
    CF_MIN_LENGTH,
    CF_MAX_LENGTH,
    CF_PATTERN,
    CF_MIN_INCLUSIVE,
    CF_MIN_EXCLUSIVE,
    CF_MAX_INCLUSIVE,
    CF_MAX_EXCLUSIVE,
    CF_TOTAL_DIGITS,
    CF_FRACTION_DIGITS,
    CF_LANG_RANGE,

    // Markers
    CF_COUNT,
    CF_FIRST = CF_NONE
} CowlFacet;

CowlFacet cowl_facet_from_iri(CowlIRI *iri);
CowlIRI* cowl_facet_get_iri(CowlFacet facet);

#define cowl_facet_foreach(var_name) \
    for (CowlFacet var_name = CF_FIRST; (var_name) < CF_COUNT; ++(var_name))

COWL_END_DECLS

#endif // COWL_FACET_H
