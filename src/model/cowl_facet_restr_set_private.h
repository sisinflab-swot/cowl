/// @author Ivano Bilenchi

#ifndef COWL_FACET_RESTR_SET_PRIVATE_H
#define COWL_FACET_RESTR_SET_PRIVATE_H

#include "cowl_facet_restr_set.h"

COWL_BEGIN_DECLS

cowl_hash_decl_mutable(CowlFacetRestrSet, CowlMutableFacetRestrSet);

bool cowl_facet_restr_set_insert(CowlMutableFacetRestrSet *set, CowlFacetRestr *restr);

COWL_END_DECLS

#endif // COWL_FACET_RESTR_SET_PRIVATE_H
