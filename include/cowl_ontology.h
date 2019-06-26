/// @author Ivano Bilenchi

#ifndef COWL_ONTOLOGY_H
#define COWL_ONTOLOGY_H

#include "cowl_axiom_type.h"
#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlAnnotation);
cowl_struct_decl(CowlAnonIndividual);
cowl_struct_decl(CowlAxiom);
cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlClsExp);
cowl_struct_decl(CowlDataProp);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlIndividual);
cowl_struct_decl(CowlNamedIndividual);
cowl_struct_decl(CowlObjProp);
cowl_struct_decl(CowlOntologyId);

cowl_struct_decl(CowlOntology);

CowlOntology* cowl_ontology_retain(CowlOntology *onto);
void cowl_ontology_release(CowlOntology *onto);

CowlOntologyId* cowl_ontology_get_id(CowlOntology *onto);

bool cowl_ontology_equals(CowlOntology *lhs, CowlOntology *rhs);
cowl_uint_t cowl_ontology_hash(CowlOntology *onto);

cowl_uint_t cowl_ontology_axiom_count(CowlOntology *onto);
cowl_uint_t cowl_ontology_imports_count(CowlOntology *onto);

cowl_uint_t cowl_ontology_axiom_count_for_annot_prop(CowlOntology *onto, CowlAnnotProp *prop);
cowl_uint_t cowl_ontology_axiom_count_for_class(CowlOntology *onto, CowlClass *owl_class);
cowl_uint_t cowl_ontology_axiom_count_for_data_prop(CowlOntology *onto, CowlDataProp *prop);
cowl_uint_t cowl_ontology_axiom_count_for_datatype(CowlOntology *onto, CowlDatatype *datatype);
cowl_uint_t cowl_ontology_axiom_count_for_obj_prop(CowlOntology *onto, CowlObjProp *prop);
cowl_uint_t cowl_ontology_axiom_count_for_named_individual(CowlOntology *onto,
                                                           CowlNamedIndividual *ind);

bool cowl_ontology_iterate_signature(CowlOntology *onto, void *ctx, CowlEntityIterator iter);

bool cowl_ontology_iterate_imports(CowlOntology *onto, void *ctx, CowlOntologyIterator iter);

bool cowl_ontology_iterate_classes(CowlOntology *onto, void *ctx, CowlClassIterator iter);

bool cowl_ontology_iterate_data_prop(CowlOntology *onto, void *ctx, CowlDataPropIterator iter);

bool cowl_ontology_iterate_datatypes(CowlOntology *onto, void *ctx, CowlDatatypeIterator iter);

bool cowl_ontology_iterate_obj_prop(CowlOntology *onto, void *ctx, CowlObjPropIterator iter);

bool cowl_ontology_iterate_annot_prop(CowlOntology *onto, void *ctx, CowlAnnotPropIterator iter);

bool cowl_ontology_iterate_named_individuals(CowlOntology *onto, void *ctx,
                                             CowlNamedIndividualIterator iter);

bool cowl_ontology_iterate_anon_individuals(CowlOntology *onto, void *ctx,
                                            CowlAnonIndividualIterator iter);

bool cowl_ontology_iterate_axioms(CowlOntology *onto, void *ctx, CowlAxiomIterator iter);

bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          void *ctx, CowlAxiomIterator iter);

bool cowl_ontology_iterate_axioms_for_annot_prop(CowlOntology *onto, CowlAnnotProp *prop,
                                                 void *ctx, CowlAxiomIterator iter);

bool cowl_ontology_iterate_axioms_for_class(CowlOntology *onto, CowlClass *owl_class,
                                            void *ctx, CowlAxiomIterator iter);

bool cowl_ontology_iterate_axioms_for_data_prop(CowlOntology *onto, CowlDataProp *prop,
                                                void *ctx, CowlAxiomIterator iter);

bool cowl_ontology_iterate_axioms_for_datatype(CowlOntology *onto, CowlDatatype *datatype,
                                               void *ctx, CowlAxiomIterator iter);

bool cowl_ontology_iterate_axioms_for_obj_prop(CowlOntology *onto, CowlObjProp *prop,
                                               void *ctx, CowlAxiomIterator iter);

bool cowl_ontology_iterate_axioms_for_named_individual(CowlOntology *onto, CowlNamedIndividual *ind,
                                                       void *ctx, CowlAxiomIterator iter);

bool cowl_ontology_iterate_axioms_for_anon_individual(CowlOntology *onto, CowlAnonIndividual *ind,
                                                      void *ctx, CowlAxiomIterator iter);

bool cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       void *ctx, CowlClsExpIterator iter);

bool cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         void *ctx, CowlClsExpIterator iter);

bool cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      void *ctx, CowlClsExpIterator iter);

bool cowl_ontology_iterate_disjoint_classes(CowlOntology *onto, CowlClass *owl_class,
                                            void *ctx, CowlClsExpIterator iter);

bool cowl_ontology_iterate_types(CowlOntology *onto, CowlIndividual *ind,
                                 void *ctx, CowlClsExpIterator iter);

COWL_END_DECLS

#endif // COWL_ONTOLOGY_H
