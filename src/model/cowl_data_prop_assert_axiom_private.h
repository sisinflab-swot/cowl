/// @author Ivano Bilenchi

#ifndef COWL_DATA_PROP_ASSERT_AXIOM_PRIVATE_H
#define COWL_DATA_PROP_ASSERT_AXIOM_PRIVATE_H

#include "cowl_data_prop_assert_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlDataPropAssertAxiom,
    CowlIndividual *source;
    CowlDataPropExp *prop;
    CowlLiteral *target;
);

COWL_END_DECLS

#endif // COWL_DATA_PROP_ASSERT_AXIOM_PRIVATE_H
