/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJECT_VEC_PRIVATE_H
#define COWL_OBJECT_VEC_PRIVATE_H

#include "cowl_object_vec.h"

COWL_BEGIN_DECLS

#define cowl_object_vec_free_spec(T, vec) do {                                                      \
    if (vec) {                                                                                      \
        uvec_foreach(CowlObjectPtr, vec, obj, cowl_##T##_release(obj));                             \
        uvec_free(CowlObjectPtr, (UVec(CowlObjectPtr)*)(vec));                                      \
    }                                                                                               \
} while(0)

COWL_END_DECLS

#endif // COWL_OBJECT_VEC_PRIVATE_H
