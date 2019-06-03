/// @author Ivano Bilenchi

#ifndef COWL_FUNC_DATA_PROP_AXIOM_PRIVATE_H
#define COWL_FUNC_DATA_PROP_AXIOM_PRIVATE_H

#include "cowl_func_data_prop_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_struct(CowlFuncDataPropAxiom) {
    CowlAxiom super;
    CowlDataPropExp *prop;
};

COWL_END_DECLS

#endif // COWL_FUNC_DATA_PROP_AXIOM_PRIVATE_H
