/// @author Ivano Bilenchi

#ifndef COWL_NAMED_IND_H
#define COWL_NAMED_IND_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);

cowl_struct_decl(CowlNamedInd);

CowlNamedInd* cowl_named_ind_get(CowlIRI *iri);
CowlNamedInd* cowl_named_ind_retain(CowlNamedInd *ind);
void cowl_named_ind_release(CowlNamedInd *ind);

CowlIRI* cowl_named_ind_get_iri(CowlNamedInd *ind);

bool cowl_named_ind_equals(CowlNamedInd *lhs, CowlNamedInd *rhs);
cowl_uint_t cowl_named_ind_hash(CowlNamedInd *ind);

bool cowl_named_ind_iterate_signature(CowlNamedInd *ind, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_NAMED_IND_H
