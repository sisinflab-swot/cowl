/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_DATATYPE_RESTR_PRIVATE_H
#define COWL_DATATYPE_RESTR_PRIVATE_H

#include "cowl_datatype_restr.h"
#include "cowl_data_range_private.h"

COWL_BEGIN_DECLS

struct CowlDatatypeRestr {
    CowlDataRange super;
    CowlDatatype *datatype;
    CowlObjectTable *restrictions;
};

COWL_END_DECLS

#endif // COWL_DATATYPE_RESTR_PRIVATE_H
