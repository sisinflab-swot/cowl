/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <https://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_any.h"
#include "cowl_impl.h"
#include "cowl_iterator.h"
#include "cowl_obj_quant_private.h"
#include "cowl_object.h"
#include "cowl_object_type.h"
#include "cowl_owl_vocab.h"
#include "cowl_primitive_flags.h"
#include "cowl_quant_type.h"
#include "cowl_ret.h"
#include "cowl_utils.h"
#include <stddef.h>

CowlObjQuant *cowl_obj_quant(CowlQuantType type, CowlAnyObjPropExp *prop, CowlAnyClsExp *filler) {
    if (!cowl_enum_value_is_valid(QT, type)) return NULL;
    if (filler == cowl_owl_vocab()->cls.thing) filler = NULL;
    return cowl_get_impl_1_opt(COWL_OT_CE_OBJ_SOME + type, prop, filler);
}

CowlClsExp *cowl_obj_quant_get_filler(CowlObjQuant *restr) {
    CowlClsExp *filler = cowl_get_opt_field(restr);
    return filler ? filler : (CowlClsExp *)cowl_owl_vocab()->cls.thing;
}

cowl_ret cowl_obj_quant_iterate_primitives(CowlObjQuant *restr, CowlPrimitiveFlags flags,
                                           CowlIterator *iter) {
    cowl_ret ret = cowl_iterate_primitives(cowl_obj_quant_get_prop(restr), flags, iter);
    if (cowl_should_stop(ret)) return ret;
    return cowl_iterate_primitives(cowl_obj_quant_get_filler(restr), flags, iter);
}
