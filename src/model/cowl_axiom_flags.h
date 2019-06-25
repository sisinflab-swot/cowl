/// @author Ivano Bilenchi

#ifndef COWL_AXIOM_FLAGS_H
#define COWL_AXIOM_FLAGS_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef CowlFlags8 CowlAxiomFlags;

#define COWL_AXIOM_FLAGS_ANNOT_BIT (CowlAxiomFlags)((1u << 7u))

#define cowl_axiom_flags_get(TYPE, HAS_ANNOT) \
    ((CowlAxiomFlags)(TYPE) | (CowlAxiomFlags)((HAS_ANNOT) ? COWL_AXIOM_FLAGS_ANNOT_BIT : 0u))

#define cowl_axiom_flags_has_annot(FLAGS) cowl_flags_is_set(FLAGS, COWL_AXIOM_FLAGS_ANNOT_BIT)

#define cowl_axiom_flags_get_type(FLAGS) \
    ((CowlAxiomType)((FLAGS) & (CowlAxiomFlags)(~(COWL_AXIOM_FLAGS_ANNOT_BIT))))

COWL_END_DECLS

#endif // COWL_AXIOM_FLAGS_H
