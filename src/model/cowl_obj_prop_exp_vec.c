/// @author Ivano Bilenchi

#include "cowl_obj_prop_exp_vec_private.h"
#include "cowl_hash_utils.h"
#include "cowl_obj_prop_exp.h"

VECTOR_IMPL_EQUATABLE(CowlObjPropExpPtr, cowl_obj_prop_exp_equals)

void cowl_obj_prop_exp_vec_free(CowlObjPropExpVec *vec) {
    vector_deep_free(CowlObjPropExpPtr, (Vector(CowlObjPropExpPtr)*)vec, cowl_obj_prop_exp_release);
}

void cowl_obj_prop_exp_vec_push(CowlMutableObjPropExpVec *vec, CowlObjPropExp *exp) {
    vector_push(CowlObjPropExpPtr, vec, cowl_obj_prop_exp_retain(exp));
}

bool cowl_obj_prop_exp_vec_equals(CowlObjPropExpVec *lhs, CowlObjPropExpVec *rhs) {
    return vector_equals(CowlObjPropExpPtr, lhs, rhs);
}

cowl_uint_t cowl_obj_prop_exp_vec_hash(CowlObjPropExpVec *vec) {
    cowl_uint_t hash = 0;

    vector_foreach(CowlObjPropExpPtr, vec, prop, {
        hash = cowl_hash_iter(hash, cowl_obj_prop_exp_hash(prop));
    });

    return hash;
}

bool cowl_obj_prop_exp_vec_iterate_signature(CowlObjPropExpVec *vec, void *ctx,
                                             CowlEntityIterator iter) {
    vector_foreach(CowlObjPropExpPtr, vec, prop, {
        if (!cowl_obj_prop_exp_iterate_signature(prop, ctx, iter)) return false;
    });
    return true;
}
