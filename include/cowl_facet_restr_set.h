/// @author Ivano Bilenchi

#ifndef COWL_FACET_RESTR_SET_H
#define COWL_FACET_RESTR_SET_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlFacetRestr);

UHASH_SET_DECL(CowlFacetRestrSet, CowlFacetRestr*)
cowl_hash_decl(CowlFacetRestrSet);

void cowl_facet_restr_set_free(CowlFacetRestrSet *set);

COWL_END_DECLS

#endif // COWL_FACET_RESTR_SET_H
