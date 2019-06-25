/// @author Ivano Bilenchi

#ifndef COWL_DISJ_UNION_AXIOM_PRIVATE_H
#define COWL_DISJ_UNION_AXIOM_PRIVATE_H

#include "cowl_disj_union_axiom.h"
#include "cowl_axiom_private.h"

COWL_BEGIN_DECLS

cowl_axiom_struct(CowlDisjUnionAxiom,
    CowlClass *cls;
    CowlClsExpSet *disjoints;
);

COWL_END_DECLS

#endif // COWL_DISJ_UNION_AXIOM_PRIVATE_H
