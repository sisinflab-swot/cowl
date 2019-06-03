/// @author Ivano Bilenchi

#ifndef COWL_ANNOT_PROP_PRIVATE_H
#define COWL_ANNOT_PROP_PRIVATE_H

#include "cowl_annot_prop.h"

COWL_BEGIN_DECLS

cowl_struct(CowlAnnotProp) {
    cowl_uint_t ref_count;
    CowlIRI *iri;
};

#define COWL_ANNOT_PROP_INIT(IRI) { .ref_count = 1, .iri = (IRI) }

#define cowl_annot_prop_ref_get(i) (((cowl_struct(CowlAnnotProp) *)(i))->ref_count)
#define cowl_annot_prop_ref_incr(i) (++cowl_annot_prop_ref_get(i), (i))
#define cowl_annot_prop_ref_decr(i) (--cowl_annot_prop_ref_get(i))

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_PRIVATE_H
