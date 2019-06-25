/// @author Ivano Bilenchi

#ifndef COWL_ANNOT_ASSERT_AXIOM_PRIVATE_H
#define COWL_ANNOT_ASSERT_AXIOM_PRIVATE_H

#include "cowl_annot_assert_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlAnnotAssertAxiom,
    CowlAnnotValue subject;
    CowlAnnotValue value;
    CowlAnnotProp *prop;
);

COWL_END_DECLS

#endif // COWL_ANNOT_ASSERT_AXIOM_PRIVATE_H
