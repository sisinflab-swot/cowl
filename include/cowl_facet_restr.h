/// @author Ivano Bilenchi

#ifndef COWL_FACET_RESTR_H
#define COWL_FACET_RESTR_H

#include "cowl_facet.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlLiteral);

cowl_struct_decl(CowlFacetRestr);

CowlFacetRestr* cowl_facet_restr_get(CowlFacet facet, CowlLiteral *value);
CowlFacetRestr* cowl_facet_restr_retain(CowlFacetRestr *restr);
void cowl_facet_restr_release(CowlFacetRestr *restr);

CowlFacet cowl_facet_restr_get_facet(CowlFacetRestr *restr);
CowlLiteral* cowl_facet_restr_get_value(CowlFacetRestr *restr);

bool cowl_facet_restr_equals(CowlFacetRestr *lhs, CowlFacetRestr *rhs);
cowl_uint_t cowl_facet_restr_hash(CowlFacetRestr *restr);

bool cowl_facet_restr_iterate_signature(CowlFacetRestr *restr, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_FACET_RESTR_H
