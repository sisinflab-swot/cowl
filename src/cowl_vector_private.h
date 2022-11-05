/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_VECTOR_PRIVATE_H
#define COWL_VECTOR_PRIVATE_H

#include "cowl_vector.h"
#include "cowl_object_private.h"

COWL_BEGIN_DECLS

struct CowlVector {
    CowlObject super;
    UVec(CowlObjectPtr) data;
};

void cowl_vector_release_ex(CowlVector *vec, bool release_elements);
cowl_ret cowl_vector_add(CowlVector *vec, CowlAny *object);
cowl_ret cowl_vector_push(CowlVector *vec, CowlAny *object);
bool cowl_vector_remove(CowlVector *vec, CowlAny *object);
cowl_ret cowl_vector_shrink(CowlVector *vec);

COWL_END_DECLS

#endif // COWL_VECTOR_PRIVATE_H
