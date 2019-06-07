/// @author Ivano Bilenchi

#include "cowl_anon_individual_private.h"
#include "cowl_string.h"

UHASH_MAP_INIT(CowlAnonIndividualMap, CowlString*, CowlAnonIndividual*,
               cowl_string_hash, cowl_string_equals)
static UHash(CowlAnonIndividualMap) *inst_map = NULL;

static CowlAnonIndividual* cowl_anon_individual_alloc(CowlString *id) {
    CowlAnonIndividual init = {
        .super = COWL_INDIVIDUAL_INIT(false),
        .id = cowl_string_retain(id)
    };
    cowl_struct(CowlAnonIndividual) *ind = malloc(sizeof(*ind));
    memcpy(ind, &init, sizeof(*ind));
    return ind;
}

static void cowl_anon_individual_free(CowlAnonIndividual *ind) {
    if (!ind) return;
    cowl_string_release(ind->id);
    free((void *)ind);
}

CowlAnonIndividual* cowl_anon_individual_get(CowlString *id) {
    if (!inst_map) inst_map = uhash_alloc(CowlAnonIndividualMap);

    CowlAnonIndividual *ind;
    uhash_ret_t ret;
    uhash_uint_t idx = uhash_put(CowlAnonIndividualMap, inst_map, id, &ret);

    if (ret == UHASH_INSERTED) {
        ind = cowl_anon_individual_alloc(id);
        uhash_value(inst_map, idx) = ind;
    } else {
        ind = uhash_value(inst_map, idx);
        cowl_object_retain(ind);
    }

    return ind;
}

CowlAnonIndividual* cowl_anon_individual_retain(CowlAnonIndividual *ind) {
    return cowl_object_retain(ind);
}

void cowl_anon_individual_release(CowlAnonIndividual *ind) {
    if (ind && !cowl_object_release(ind)) {
        uhmap_remove(CowlAnonIndividualMap, inst_map, ind->id);
        cowl_anon_individual_free(ind);
    }
}

CowlString* cowl_anon_individual_get_id(CowlAnonIndividual *ind) {
    return ind->id;
}

bool cowl_anon_individual_equals(CowlAnonIndividual *lhs, CowlAnonIndividual *rhs) {
    return lhs == rhs;
}

cowl_uint_t cowl_anon_individual_hash(CowlAnonIndividual *ind) {
    return uhash_ptr_hash(ind);
}
