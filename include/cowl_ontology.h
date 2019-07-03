/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_H
#define COWL_ONTOLOGY_H

#include "cowl_axiom_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAnonInd);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataProp);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlNamedInd);
cowl_struct_decl(CowlObjProp);
cowl_struct_decl(CowlOntologyID);

cowl_struct_decl(CowlOntology);

CowlOntology* cowl_ontology_retain(CowlOntology *onto);
void cowl_ontology_release(CowlOntology *onto);

CowlOntologyID* cowl_ontology_get_id(CowlOntology *onto);

bool cowl_ontology_equals(CowlOntology *lhs, CowlOntology *rhs);
cowl_uint_t cowl_ontology_hash(CowlOntology *onto);

cowl_uint_t cowl_ontology_axiom_count(CowlOntology *onto);
cowl_uint_t cowl_ontology_imports_count(CowlOntology *onto);

cowl_uint_t cowl_ontology_axiom_count_for_annot_prop(CowlOntology *onto, CowlAnnotProp *prop);
cowl_uint_t cowl_ontology_axiom_count_for_class(CowlOntology *onto, CowlClass *owl_class);
cowl_uint_t cowl_ontology_axiom_count_for_data_prop(CowlOntology *onto, CowlDataProp *prop);
cowl_uint_t cowl_ontology_axiom_count_for_datatype(CowlOntology *onto, CowlDatatype *datatype);
cowl_uint_t cowl_ontology_axiom_count_for_obj_prop(CowlOntology *onto, CowlObjProp *prop);
cowl_uint_t cowl_ontology_axiom_count_for_named_ind(CowlOntology *onto, CowlNamedInd *ind);

bool cowl_ontology_iterate_signature(CowlOntology *onto, CowlEntityIterator *iter);

bool cowl_ontology_iterate_imports(CowlOntology *onto, CowlOntologyIterator *iter);

bool cowl_ontology_iterate_classes(CowlOntology *onto, CowlClassIterator *iter);

bool cowl_ontology_iterate_data_props(CowlOntology *onto, CowlDataPropIterator *iter);

bool cowl_ontology_iterate_datatypes(CowlOntology *onto, CowlDatatypeIterator *iter);

bool cowl_ontology_iterate_obj_props(CowlOntology *onto, CowlObjPropIterator *iter);

bool cowl_ontology_iterate_annot_props(CowlOntology *onto, CowlAnnotPropIterator *iter);

bool cowl_ontology_iterate_named_inds(CowlOntology *onto, CowlNamedIndIterator *iter);

bool cowl_ontology_iterate_anon_inds(CowlOntology *onto, CowlAnonIndIterator *iter);

bool cowl_ontology_iterate_axioms(CowlOntology *onto, CowlAxiomIterator *iter);

bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          CowlAxiomIterator *iter);

bool cowl_ontology_iterate_axioms_for_annot_prop(CowlOntology *onto, CowlAnnotProp *prop,
                                                 CowlAxiomIterator *iter);

bool cowl_ontology_iterate_axioms_for_class(CowlOntology *onto, CowlClass *owl_class,
                                            CowlAxiomIterator *iter);

bool cowl_ontology_iterate_axioms_for_data_prop(CowlOntology *onto, CowlDataProp *prop,
                                                CowlAxiomIterator *iter);

bool cowl_ontology_iterate_axioms_for_datatype(CowlOntology *onto, CowlDatatype *datatype,
                                               CowlAxiomIterator *iter);

bool cowl_ontology_iterate_axioms_for_obj_prop(CowlOntology *onto, CowlObjProp *prop,
                                               CowlAxiomIterator *iter);

bool cowl_ontology_iterate_axioms_for_named_ind(CowlOntology *onto, CowlNamedInd *ind,
                                                CowlAxiomIterator *iter);

bool cowl_ontology_iterate_axioms_for_anon_ind(CowlOntology *onto, CowlAnonInd *ind,
                                               CowlAxiomIterator *iter);

bool cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       CowlClsExpIterator *iter);

bool cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         CowlClsExpIterator *iter);

bool cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      CowlClsExpIterator *iter);

bool cowl_ontology_iterate_disjoint_classes(CowlOntology *onto, CowlClass *owl_class,
                                            CowlClsExpIterator *iter);

bool cowl_ontology_iterate_types(CowlOntology *onto, CowlIndividual *ind, CowlClsExpIterator *iter);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_H
