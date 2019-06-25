/// @author Ivano Bilenchi

#ifndef COWL_FACET_RESTR_SET_H
#define COWL_FACET_RESTR_SET_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlFacetRestr);

UHASH_SET_DECL(CowlFacetRestrSet, CowlFacetRestr*)
cowl_hash_decl(CowlFacetRestrSet);

void cowl_facet_restr_set_free(CowlFacetRestrSet *set);

bool cowl_facet_restr_set_equals(CowlFacetRestrSet *lhs, CowlFacetRestrSet *rhs);
cowl_uint_t cowl_facet_restr_set_hash(CowlFacetRestrSet *set);

bool cowl_facet_restr_set_iterate_signature(CowlFacetRestrSet *set, void *ctx,
                                            CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_FACET_RESTR_SET_H
