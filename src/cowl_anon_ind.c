/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_anon_ind_private.h"
#include "cowl_string_private.h"
#include "cowl_table.h"

static ulib_uint const rand_id_len = P_USTRING_SMALL_SIZE - 1;

static UHash(CowlObjectTable) inst_tbl;

static ulib_uint inst_tbl_hash(CowlAny *key) {
    return cowl_string_hash(cowl_anon_ind_get_id(key));
}

static bool inst_tbl_eq(CowlAny *lhs, CowlAny *rhs) {
    return cowl_string_equals(cowl_anon_ind_get_id(lhs), cowl_anon_ind_get_id(rhs));
}

cowl_ret cowl_anon_ind_api_init(void) {
    inst_tbl = uhset_pi(CowlObjectTable, inst_tbl_hash, inst_tbl_eq);
    return COWL_OK;
}

void cowl_anon_ind_api_deinit(void) {
    uhash_deinit(CowlObjectTable, &inst_tbl);
}

static UString generate_id(void) {
    return urand_string(rand_id_len, NULL);
}

static CowlAnonInd *anon_ind_alloc(CowlString *id) {
    CowlAnonInd *ind = ulib_alloc(ind);
    if (!ind) return NULL;
    *ind = (CowlAnonInd){
        .super = COWL_OBJECT_INIT(COWL_OT_I_ANONYMOUS),
        .id = cowl_string_retain(id),
    };
    return ind;
}

static CowlAnonInd *anon_ind(CowlString *id, bool copy_id) {
    ulib_uint idx;
    CowlAnonInd key = { .id = id };
    uhash_ret ret = uhash_put(CowlObjectTable, &inst_tbl, &key, &idx);

    CowlAnonInd *val = NULL;

    if (ret == UHASH_INSERTED) {
        if (copy_id) {
            val = anon_ind_alloc(id = cowl_string_copy(id));
            cowl_string_release(id);
        } else {
            val = anon_ind_alloc(id);
        }

        if (val) {
            uhash_key(CowlObjectTable, &inst_tbl, idx) = val;
        } else {
            uhash_delete(CowlObjectTable, &inst_tbl, idx);
        }
    } else if (ret == UHASH_PRESENT) {
        val = uhash_key(CowlObjectTable, &inst_tbl, idx);
        (void)cowl_object_incr_ref(val);
    }

    return val;
}

static CowlAnonInd *anon_ind_generate(void) {
    UString id = generate_id();
    if (ustring_is_null(id)) return NULL;

    ulib_uint i;
    uhash_ret ret;
    CowlString id_str = cowl_string_init(id);
    CowlAnonInd key = { .id = &id_str };

    while ((ret = uhash_put(CowlObjectTable, &inst_tbl, &key, &i)) == UHASH_PRESENT) {
        ustring_deinit(&id);
        id = generate_id();
        if (ustring_is_null(id)) return NULL;
        id_str = cowl_string_init(id);
    }

    if (ret == UHASH_ERR) {
        ustring_deinit(&id);
        return NULL;
    }

    CowlString *id_str_new = cowl_string(id);
    if (!id_str_new) goto err;

    CowlAnonInd *ind = anon_ind_alloc(id_str_new);
    cowl_string_release(id_str_new);
    if (!ind) goto err;

    uhash_key(CowlObjectTable, &inst_tbl, i) = ind;

    return ind;

err:
    uhash_delete(CowlObjectTable, &inst_tbl, i);
    return NULL;
}

CowlAnonInd *cowl_anon_ind(CowlString *id) {
    return id ? anon_ind(id, false) : anon_ind_generate();
}

CowlAnonInd *cowl_anon_ind_from_string(UString string) {
    CowlString id = cowl_string_init(string);
    return anon_ind(&id, true);
}

void cowl_anon_ind_release(CowlAnonInd *ind) {
    if (ind && !cowl_object_decr_ref(ind)) {
        uhset_remove(CowlObjectTable, &inst_tbl, ind);
        cowl_string_release(ind->id);
        ulib_free(ind);
    }
}

CowlString *cowl_anon_ind_get_id(CowlAnonInd *ind) {
    return ind->id;
}
