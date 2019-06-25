/// @author Ivano Bilenchi

#ifndef COWL_SUB_DATA_PROP_AXIOM_H
#define COWL_SUB_DATA_PROP_AXIOM_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlDataPropExp);
cowl_vector_decl(CowlAnnotationPtr, CowlAnnotationVec);

cowl_struct_decl(CowlSubDataPropAxiom);

CowlSubDataPropAxiom* cowl_sub_data_prop_axiom_get(CowlDataPropExp *sub, CowlDataPropExp *super,
                                                   CowlAnnotationVec *annot);
CowlSubDataPropAxiom* cowl_sub_data_prop_axiom_retain(CowlSubDataPropAxiom *axiom);
void cowl_sub_data_prop_axiom_release(CowlSubDataPropAxiom *axiom);

CowlDataPropExp* cowl_sub_data_prop_axiom_get_super(CowlSubDataPropAxiom *axiom);
CowlDataPropExp* cowl_sub_data_prop_axiom_get_sub(CowlSubDataPropAxiom *axiom);
CowlAnnotationVec* cowl_sub_data_prop_axiom_get_annot(CowlSubDataPropAxiom *axiom);

bool cowl_sub_data_prop_axiom_equals(CowlSubDataPropAxiom *lhs, CowlSubDataPropAxiom *rhs);
cowl_uint_t cowl_sub_data_prop_axiom_hash(CowlSubDataPropAxiom *axiom);

bool cowl_sub_data_prop_axiom_iterate_signature(CowlSubDataPropAxiom *axiom,
                                                void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_SUB_DATA_PROP_AXIOM_H
