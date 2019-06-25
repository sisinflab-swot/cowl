/// @author Ivano Bilenchi

#ifndef COWL_ANNOT_PROP_RANGE_AXIOM_PRIVATE_H
#define COWL_ANNOT_PROP_RANGE_AXIOM_PRIVATE_H

#include "cowl_annot_prop_range_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlAnnotPropRangeAxiom,
    CowlAnnotProp *prop;
    CowlIRI *range;
);

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_RANGE_AXIOM_PRIVATE_H
