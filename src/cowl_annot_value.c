/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_annot_value.h"

CowlAnnotValueType cowl_annot_value_get_type(CowlAnyAnnotValue *value) {
    switch (cowl_get_type(value)) {
        case COWL_OT_IRI: return COWL_AVT_IRI;
        case COWL_OT_I_ANONYMOUS: return COWL_AVT_ANON_IND;
        default: return COWL_AVT_LITERAL;
    }
}
