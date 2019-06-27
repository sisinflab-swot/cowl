/// @author Ivano Bilenchi

#ifndef COWL_ANNOT_PROP_H
#define COWL_ANNOT_PROP_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);

cowl_struct_decl(CowlAnnotProp);

CowlAnnotProp* cowl_annot_prop_get(CowlIRI *iri);
CowlAnnotProp* cowl_annot_prop_retain(CowlAnnotProp *prop);
void cowl_annot_prop_release(CowlAnnotProp *prop);

CowlIRI* cowl_annot_prop_get_iri(CowlAnnotProp *prop);

bool cowl_annot_prop_equals(CowlAnnotProp *lhs, CowlAnnotProp *rhs);
cowl_uint_t cowl_annot_prop_hash(CowlAnnotProp *prop);

bool cowl_annot_prop_iterate_signature(CowlAnnotProp *prop, CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_ANNOT_PROP_H
