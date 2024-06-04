/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_sub_obj_prop_axiom.h"
#include "cowl_any.h"
#include "cowl_impl.h"
#include "cowl_object_type.h"
#include "cowl_vector_private.h"

CowlSubObjPropAxiom *
cowl_sub_obj_prop_chain_axiom(CowlVector *sub, CowlAnyObjPropExp *super, CowlVector *annot) {
    cowl_vector_set_ordered(sub);
    return (CowlSubObjPropAxiom *)cowl_get_impl_2_annot(COWL_OT_A_SUB_OBJ_PROP, sub, super, annot);
}
