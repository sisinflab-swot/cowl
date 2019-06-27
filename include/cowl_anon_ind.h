/// @author Ivano Bilenchi

#ifndef COWL_ANON_IND_H
#define COWL_ANON_IND_H

#include "cowl_node_id.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlString);

cowl_struct_decl(CowlAnonInd);

CowlAnonInd* cowl_anon_ind_get(CowlNodeID id);
CowlAnonInd* cowl_anon_ind_retain(CowlAnonInd *ind);
void cowl_anon_ind_release(CowlAnonInd *ind);

CowlNodeID cowl_anon_ind_get_id(CowlAnonInd *ind);

CowlString* cowl_anon_ind_to_string(CowlAnonInd *ind);
bool cowl_anon_ind_equals(CowlAnonInd *lhs, CowlAnonInd *rhs);
cowl_uint_t cowl_anon_ind_hash(CowlAnonInd *ind);

COWL_END_DECLS

#endif // COWL_ANON_IND_H
