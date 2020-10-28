/**
 * Declares CowlObjPropExpVec and its API.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_OBJ_PROP_EXP_VEC_H
#define COWL_OBJ_PROP_EXP_VEC_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlObjPropExp);

typedef CowlObjPropExp* CowlObjPropExpPtr;
VECTOR_DECL_EQUATABLE_SPEC(CowlObjPropExpPtr, COWL_PUBLIC)
cowl_vector_decl(CowlObjPropExpPtr, CowlObjPropExpVec);
/// @endcond

/**
 * Vector of CowlObjPropExp * elements.
 *
 * @struct CowlObjPropExpVec
 * @extends Vector
 */

/**
 * Deallocates the specified vector, releasing its elements.
 *
 * @param vec The vector.
 *
 * @public @memberof CowlObjPropExpVec
 */
COWL_PUBLIC
void cowl_obj_prop_exp_vec_free(CowlObjPropExpVec *vec);

/**
 * Equality function.
 *
 * @param lhs LHS of the equality relation.
 * @param rhs RHS of the equality relation.
 * @return True if the equality relation holds, false otherwise.
 *
 * @public @memberof CowlObjPropExpVec
 */
COWL_PUBLIC
bool cowl_obj_prop_exp_vec_equals(CowlObjPropExpVec *lhs, CowlObjPropExpVec *rhs);

/**
 * Hash function.
 *
 * @param vec The vector.
 * @return The hash value.
 *
 * @public @memberof CowlObjPropExpVec
 */
COWL_PUBLIC
cowl_uint_t cowl_obj_prop_exp_vec_hash(CowlObjPropExpVec *vec);

/**
 * Iterates over the objects referenced by the specified vector.
 *
 * @param vec The vector.
 * @param iter The iterator.
 * @return True if the iteration was completed, false if it was stopped.
 *
 * @public @memberof CowlObjPropExpVec
 */
COWL_PUBLIC
bool cowl_obj_prop_exp_vec_iterate(CowlObjPropExpVec *vec, CowlIterator *iter);

COWL_END_DECLS

#endif // COWL_OBJ_PROP_EXP_VEC_H
