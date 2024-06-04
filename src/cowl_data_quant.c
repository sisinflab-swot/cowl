/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_quant.h"
#include "cowl_any.h"
#include "cowl_impl.h"
#include "cowl_macros.h"
#include "cowl_object_type.h"
#include "cowl_quant_type.h"
#include "cowl_rdfs_vocab.h"
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
