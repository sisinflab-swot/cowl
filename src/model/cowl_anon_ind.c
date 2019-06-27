/// @author Ivano Bilenchi

#include "cowl_anon_ind_private.h"
#include "cowl_string.h"

UHASH_MAP_INIT(CowlAnonIndMap, CowlNodeID, CowlAnonInd*,
               cowl_node_id_hash, cowl_node_id_equals)
static UHash(CowlAnonIndMap) *inst_map = NULL;

static CowlAnonInd* cowl_anon_ind_alloc(CowlNodeID id) {
    CowlAnonInd init = {
        .super = COWL_INDIVIDUAL_INIT(false),
        .id = id
    };
    cowl_struct(CowlAnonInd) *ind = malloc(sizeof(*ind));
    memcpy(ind, &init, sizeof(*ind));
    return ind;
}

static void cowl_anon_ind_free(CowlAnonInd *ind) {
    if (!ind) return;
    free((void *)ind);
}

CowlAnonInd* cowl_anon_ind_get(CowlNodeID id) {
    if (!inst_map) inst_map = uhash_alloc(CowlAnonIndMap);

    CowlAnonInd *ind;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlAnonIndMap, inst_map, id, &ret);

    if (ret == UHASH_INSERTED) {
        ind = cowl_anon_ind_alloc(id);
        uhash_value(inst_map, idx) = ind;
    } else {
        ind = uhash_value(inst_map, idx);
        cowl_object_retain(ind);
    }

    return ind;
}

CowlAnonInd* cowl_anon_ind_retain(CowlAnonInd *ind) {
    return cowl_object_retain(ind);
}

void cowl_anon_ind_release(CowlAnonInd *ind) {
    if (ind && !cowl_object_release(ind)) {
        uhmap_remove(CowlAnonIndMap, inst_map, ind->id);
        cowl_anon_ind_free(ind);
    }
}

CowlNodeID cowl_anon_ind_get_id(CowlAnonInd *ind) {
    return ind->id;
}

CowlString* cowl_anon_ind_to_string(CowlAnonInd *ind) {
    return cowl_node_id_to_string(ind->id);
}

bool cowl_anon_ind_equals(CowlAnonInd *lhs, CowlAnonInd *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_anon_ind_hash(CowlAnonInd *ind) {
    return uhash_ptr_hash(ind);
}
