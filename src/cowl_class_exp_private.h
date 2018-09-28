/// @author Ivano Bilenchi

#ifndef COWL_CLASS_EXPRESSION_PRIVATE_H
#define COWL_CLASS_EXPRESSION_PRIVATE_H

#include "cowl_class_exp.h"

COWL_BEGIN_DECLS

typedef struct CowlClassExp {
    CowlClassExpType type;

    union {
        // Class
        CowlEntity const *owl_class;

        // objectComplementOf
        CowlClassExp const *operand;

        // objectIntersectionOf
        // objectUnionOf
        khash_t(CowlClassExpSet) const *operands;

        // objectAllValuesFrom
        // objectSomeValuesFrom
        struct {
            CowlObjPropExp const *restr_prop;
            CowlClassExp const *restr_filler;
        };

        // objectMinCardinality
        // objectMaxCardinality
        // objectExactCardinality
        struct {
            uint32_t cardinality;
            CowlObjPropExp const *card_prop;
            CowlClassExp const *card_filler;
        };
    };
} CowlClassExp;

COWL_END_DECLS

#endif // COWL_CLASS_EXPRESSION_PRIVATE_H
