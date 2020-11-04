/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATATYPE_RESTR_PRIVATE_H
#define COWL_DATATYPE_RESTR_PRIVATE_H

#include "cowl_datatype_restr.h"
#include "cowl_data_range_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlDatatypeRestr) {
    CowlDataRange super;
    CowlDatatype *datatype;
    CowlFacetRestrSet *restrictions;
};

COWL_END_DECLS

#endif // COWL_DATATYPE_RESTR_PRIVATE_H
