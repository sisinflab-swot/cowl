/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_data_card.h"
#include "cowl_rdfs_vocab.h"

CowlDataCard *cowl_data_card(CowlCardType type, CowlAnyDataPropExp *prop, CowlAnyDataRange *range,
                             ulib_uint cardinality) {
    if (!cowl_enum_value_is_valid(CT, type)) return NULL;
    if (range == cowl_rdfs_vocab()->dt.literal) range = NULL;
    return cowl_get_impl_1_uint_opt(COWL_OT_CE_DATA_MIN_CARD + type, prop, cardinality, range);
}

CowlDataRange *cowl_data_card_get_range(CowlDataCard *restr) {
    CowlDataRange *range = cowl_get_opt_field(restr);
    return range ? range : (CowlDataRange *)cowl_rdfs_vocab()->dt.literal;
}
