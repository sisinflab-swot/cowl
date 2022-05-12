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

COWL_END_DECLS

#endif // COWL_VECTOR_PRIVATE_H
