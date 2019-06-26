/// @author Ivano Bilenchi

#ifndef COWL_ANON_INDIVIDUAL_H
#define COWL_ANON_INDIVIDUAL_H

#include "cowl_node_id.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlString);

cowl_struct_decl(CowlAnonIndividual);

CowlAnonIndividual* cowl_anon_individual_get(CowlNodeID id);
CowlAnonIndividual* cowl_anon_individual_retain(CowlAnonIndividual *ind);
void cowl_anon_individual_release(CowlAnonIndividual *ind);

CowlNodeID cowl_anon_individual_get_id(CowlAnonIndividual *ind);

CowlString* cowl_anon_individual_to_string(CowlAnonIndividual *ind);
bool cowl_anon_individual_equals(CowlAnonIndividual *lhs, CowlAnonIndividual *rhs);
cowl_uint_t cowl_anon_individual_hash(CowlAnonIndividual *ind);

COWL_END_DECLS

#endif // COWL_ANON_INDIVIDUAL_H
