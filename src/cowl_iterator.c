/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_iterator_private.h"
#include "cowl_object.h"
#include "cowl_object_table.h"
#include "cowl_object_vec.h"

static bool cowl_store_vec(void *vec, void *obj) {
    return cowl_object_vec_push(vec, obj) == COWL_OK;
}

static bool cowl_store_set(void *set, void *obj) {
    return cowl_object_set_insert(set, obj) == COWL_OK;
}

CowlIterator cowl_iterator_vec_init(UVec(CowlObjectPtr) *vec) {
    if (!vec) vec = uvec_alloc(CowlObjectPtr);
    return (CowlIterator) { .ctx = vec, .for_each = cowl_store_vec };
}

CowlIterator cowl_iterator_set_init(UHash(CowlObjectTable) *set) {
    if (!set) set = uhset_alloc(CowlObjectTable);
    return (CowlIterator) { .ctx = set, .for_each = cowl_store_set };
}
