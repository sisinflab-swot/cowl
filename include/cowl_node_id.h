/// @author Ivano Bilenchi

#ifndef COWL_NODE_ID_H
#define COWL_NODE_ID_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlString);

typedef cowl_uint_t CowlNodeID;

CowlNodeID cowl_node_id_get_next(void);
CowlString* cowl_node_id_to_string(CowlNodeID id);

#define cowl_node_id_equals(lhs, rhs) ((lhs) == (rhs))
#define cowl_node_id_hash(id) (id)

COWL_END_DECLS

#endif // COWL_NODE_ID_H
