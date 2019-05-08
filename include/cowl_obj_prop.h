/// @author Ivano Bilenchi

#ifndef COWL_OBJ_PROP_H
#define COWL_OBJ_PROP_H

#include "cowl_std.h"
#include "cowl_iterator.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);

cowl_struct_decl(CowlObjProp);

CowlObjProp* cowl_obj_prop_get(CowlIRI *iri);
CowlObjProp* cowl_obj_prop_retain(CowlObjProp *prop);
void cowl_obj_prop_release(CowlObjProp *prop);

CowlIRI* cowl_obj_prop_get_iri(CowlObjProp *prop);

bool cowl_obj_prop_equals(CowlObjProp *lhs, CowlObjProp *rhs);
cowl_uint_t cowl_obj_prop_hash(CowlObjProp *prop);

bool cowl_obj_prop_iterate_signature(CowlObjProp *prop, void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_H
