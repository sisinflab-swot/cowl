/// @author Ivano Bilenchi

#ifndef COWL_ANNOT_PROP_PRIVATE_H
#define COWL_ANNOT_PROP_PRIVATE_H

#include "cowl_annot_prop.h"
#include "cowl_object.h"

COWL_BEGIN_DECLS

cowl_struct(CowlAnnotProp) {
    CowlObject super;
    CowlIRI *iri;
};

#define COWL_ANNOT_PROP_INIT(IRI) { .super = COWL_OBJECT_INIT, .iri = (IRI) }

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_PRIVATE_H
