/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_any.h"
#include "cowl_data_quant_private.h"
#include "cowl_impl.h"
#include "cowl_iterator.h"
#include "cowl_object.h"
#include "cowl_object_type.h"
#include "cowl_primitive_flags.h"
#include "cowl_quant_type.h"
#include "cowl_rdfs_vocab.h"
#include "cowl_ret.h"
#include "cowl_utils.h"
#include <stddef.h>

CowlDataQuant *
cowl_data_quant(CowlQuantType type, CowlAnyDataPropExp *prop, CowlAnyDataRange *range) {
    if (!cowl_enum_value_is_valid(QT, type)) return NULL;
    if (range == cowl_rdfs_vocab()->dt.literal) range = NULL;
    return cowl_get_impl_1_opt(COWL_OT_CE_DATA_SOME + type, prop, range);
}

CowlDataRange *cowl_data_quant_get_range(CowlDataQuant *restr) {
    CowlDataRange *range = cowl_get_opt_field(restr);
    return range ? range : (CowlDataRange *)cowl_rdfs_vocab()->dt.literal;
}

cowl_ret cowl_data_quant_iterate_primitives(CowlDataQuant *restr, CowlPrimitiveFlags flags,
                                            CowlIterator *iter) {
    cowl_ret ret = cowl_iterate_primitives(cowl_data_quant_get_prop(restr), flags, iter);
    if (cowl_should_stop(ret)) return ret;
    return cowl_iterate_primitives(cowl_data_quant_get_range(restr), flags, iter);
}
