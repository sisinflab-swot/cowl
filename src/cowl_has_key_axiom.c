/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2024 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_has_key_axiom.h"
#include "cowl_any.h"
#include "cowl_impl.h"
#include "cowl_object.h"
#include "cowl_object_type.h"
#include "cowl_vector.h"

CowlHasKeyAxiom *cowl_has_key_axiom(CowlAnyClsExp *cls_exp, CowlVector *obj_props,
                                    CowlVector *data_props, CowlVector *annot) {
    obj_props = obj_props ? cowl_retain(obj_props) : cowl_vector_empty();
    data_props = data_props ? cowl_retain(data_props) : cowl_vector_empty();
    CowlAny *ret = cowl_get_impl_3_annot(COWL_OT_A_HAS_KEY, cls_exp, obj_props, data_props, annot);
    cowl_release(obj_props);
    cowl_release(data_props);
    return ret;
}
