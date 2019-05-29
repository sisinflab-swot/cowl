/// @author Ivano Bilenchi

#ifndef COWL_DATA_COMPL_PRIVATE_H
#define COWL_DATA_COMPL_PRIVATE_H

#include "cowl_data_compl.h"
#include "cowl_data_range_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlDataCompl) {
    CowlDataRange super;
    CowlDataRange *operand;
};

COWL_END_DECLS

#endif // COWL_DATA_COMPL_PRIVATE_H
