/// @author Ivano Bilenchi

#include "cowl_ontology_private.h"
#include "cowl_private.h"

UHASH_MAP_IMPL(CowlClassAxiomMap, CowlClass*, CowlAxiomSet*,
               cowl_class_hash, cowl_class_equals)

UHASH_MAP_IMPL(CowlDataPropAxiomMap, CowlDataProp*, CowlAxiomSet*,
               cowl_data_prop_hash, cowl_data_prop_equals)

UHASH_MAP_IMPL(CowlDatatypeAxiomMap, CowlDatatype*, CowlAxiomSet*,
               cowl_datatype_hash, cowl_datatype_equals)

UHASH_MAP_IMPL(CowlObjPropAxiomMap, CowlObjProp*, CowlAxiomSet*,
               cowl_obj_prop_hash, cowl_obj_prop_equals)

UHASH_MAP_IMPL(CowlNamedIndAxiomMap, CowlNamedIndividual*, CowlAxiomSet*,
               cowl_named_individual_hash, cowl_named_individual_equals)

UHASH_MAP_IMPL(CowlAnonIndAxiomMap, CowlAnonIndividual*, CowlAxiomSet*,
               cowl_anon_individual_hash, cowl_anon_individual_equals)

typedef cowl_struct(CowlAxiomEntityCtx) {
    CowlOntology *onto;
    CowlAxiom *axiom;
} CowlAxiomEntityCtx;

static CowlMutableOntology* cowl_ontology_alloc(void);
static void cowl_ontology_free(CowlOntology *ontology);

static bool cowl_ontology_entity_adder(void *ctx, CowlEntity entity);
static void cowl_ontology_add_axiom_for_entity(CowlOntology *onto, CowlAxiom *axiom,
                                               CowlEntity entity);
static void cowl_ontology_add_axiom_for_class(CowlOntology *onto, CowlAxiom *axiom, CowlClass *cls);
static void cowl_ontology_add_axiom_for_cls_exp(CowlOntology *onto, CowlAxiom *axiom,
                                                CowlClsExp *exp);
static void cowl_ontology_add_axiom_for_data_prop_exp(CowlOntology *onto, CowlAxiom *axiom,
                                                      CowlDataPropExp *prop_exp);
static void cowl_ontology_add_axiom_for_data_range(CowlOntology *onto, CowlAxiom *axiom,
                                                   CowlDataRange *range);
static void cowl_ontology_add_axiom_for_datatype(CowlOntology *onto, CowlAxiom *axiom,
                                                 CowlDatatype *datatype);
static void cowl_ontology_add_axiom_for_literal(CowlOntology *onto, CowlAxiom *axiom,
                                                CowlLiteral *literal);
static void cowl_ontology_add_axiom_for_obj_prop_exp(CowlOntology *onto, CowlAxiom *axiom,
                                                     CowlObjPropExp *prop_exp);
static void cowl_ontology_add_axiom_for_individual(CowlOntology *onto, CowlAxiom *axiom,
                                                   CowlIndividual *individual);

#define cowl_add_axiom_to_set_in_map(T, map, key, axiom) do {                                       \
    uhash_ret_t __cowl_ret;                                                                         \
    uhash_uint_t k = uhash_put(T, map, key, &__cowl_ret);                                           \
                                                                                                    \
    CowlAxiomSet *__cowl_axioms;                                                                    \
                                                                                                    \
    if (__cowl_ret == UHASH_INSERTED) {                                                             \
        __cowl_axioms = uhash_alloc(CowlAxiomSet);                                                  \
        uhash_value(map, k) = __cowl_axioms;                                                        \
    } else {                                                                                        \
        __cowl_axioms = uhash_value(map, k);                                                        \
    }                                                                                               \
                                                                                                    \
    uhset_insert(CowlAxiomSet, __cowl_axioms, axiom);                                               \
} while(0)

#define cowl_add_axiom_to_set_in_array(array, idx, axiom) do {                                      \
    CowlAxiomSet *__cowl_axioms = ((array))[idx];                                                   \
                                                                                                    \
    if (!__cowl_axioms) {                                                                           \
        __cowl_axioms = uhash_alloc(CowlAxiomSet);                                                  \
        ((array))[idx] = __cowl_axioms;                                                             \
    }                                                                                               \
                                                                                                    \
    uhset_insert(CowlAxiomSet, __cowl_axioms, axiom);                                               \
} while(0)

CowlOntology* cowl_ontology_retain(CowlOntology *onto) {
    return cowl_object_retain(onto);
}

void cowl_ontology_release(CowlOntology *onto) {
    if (onto && !cowl_object_release(onto)) {
        cowl_ontology_free(onto);
    }
}

CowlOntologyId* cowl_ontology_get_id(CowlOntology *onto) {
    return onto->id;
}

bool cowl_ontology_equals(CowlOntology *lhs, CowlOntology *rhs) {
    return cowl_ontology_id_equals(lhs->id, rhs->id);
}

cowl_uint_t cowl_ontology_hash(CowlOntology *onto) {
    return cowl_ontology_id_hash(onto->id);
}

cowl_uint_t cowl_ontology_axiom_count(CowlOntology *onto) {
    cowl_uint_t count = 0;

    for (CowlAxiomType type = CAT_FIRST; type < CAT_COUNT; ++type) {
        count += uhash_count(onto->axioms_by_type[type]);
    }

    return count;
}

cowl_uint_t cowl_ontology_axiom_count_for_class(CowlOntology *onto, CowlClass *owl_class) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);
    return uhash_count(axioms);
}

cowl_uint_t cowl_ontology_axiom_count_for_data_prop(CowlOntology *onto, CowlDataProp *data_prop) {
    CowlAxiomSet *axioms = uhmap_get(CowlDataPropAxiomMap, onto->data_prop_refs, data_prop, NULL);
    return uhash_count(axioms);
}

cowl_uint_t cowl_ontology_axiom_count_for_datatype(CowlOntology *onto, CowlDatatype *datatype) {
    CowlAxiomSet *axioms = uhmap_get(CowlDatatypeAxiomMap, onto->datatype_refs, datatype, NULL);
    return uhash_count(axioms);
}

cowl_uint_t cowl_ontology_axiom_count_for_obj_prop(CowlOntology *onto, CowlObjProp *obj_prop) {
    CowlAxiomSet *axioms = uhmap_get(CowlObjPropAxiomMap, onto->obj_prop_refs, obj_prop, NULL);
    return uhash_count(axioms);
}

cowl_uint_t cowl_ontology_axiom_count_for_named_individual(CowlOntology *onto,
                                                           CowlNamedIndividual *individual) {
    CowlAxiomSet *axioms = uhmap_get(CowlNamedIndAxiomMap, onto->named_ind_refs, individual, NULL);
    return uhash_count(axioms);
}

void cowl_ontology_iterate_signature(CowlOntology *onto, void *ctx, CowlEntityIterator iter) {
    uhash_foreach_key(CowlClassAxiomMap, onto->class_refs, cls, {
        if (!iter(ctx, cowl_entity_wrap_class(cls))) return;
    });

    uhash_foreach_key(CowlDataPropAxiomMap, onto->data_prop_refs, prop, {
        if (!iter(ctx, cowl_entity_wrap_data_prop(prop))) return;
    });

    uhash_foreach_key(CowlDatatypeAxiomMap, onto->datatype_refs, datatype, {
        if (!iter(ctx, cowl_entity_wrap_datatype(datatype))) return;
    });

    uhash_foreach_key(CowlObjPropAxiomMap, onto->obj_prop_refs, prop, {
        if (!iter(ctx, cowl_entity_wrap_obj_prop(prop))) return;
    });

    uhash_foreach_key(CowlNamedIndAxiomMap, onto->named_ind_refs, ind, {
        if (!iter(ctx, cowl_entity_wrap_named_individual(ind))) return;
    });
}

void cowl_ontology_iterate_classes(CowlOntology *onto, void *ctx, CowlClassIterator iter) {
    uhash_foreach_key(CowlClassAxiomMap, onto->class_refs, cls, {
        if (!iter(ctx, cls)) return;
    });
}

void cowl_ontology_iterate_data_prop(CowlOntology *onto, void *ctx, CowlDataPropIterator iter) {
    uhash_foreach_key(CowlDataPropAxiomMap, onto->data_prop_refs, prop, {
        if (!iter(ctx, prop)) return;
    });
}

void cowl_ontology_iterate_datatypes(CowlOntology *onto, void *ctx, CowlDatatypeIterator iter) {
    uhash_foreach_key(CowlDatatypeAxiomMap, onto->datatype_refs, datatype, {
        if (!iter(ctx, datatype)) return;
    });
}

void cowl_ontology_iterate_obj_prop(CowlOntology *onto, void *ctx, CowlObjPropIterator iter) {
    uhash_foreach_key(CowlObjPropAxiomMap, onto->obj_prop_refs, prop, {
        if (!iter(ctx, prop)) return;
    });
}

void cowl_ontology_iterate_named_individuals(CowlOntology *onto, void *ctx,
                                             CowlNamedIndividualIterator iter) {
    uhash_foreach_key(CowlNamedIndAxiomMap, onto->named_ind_refs, ind, {
        if (!iter(ctx, ind)) return;
    });
}

void cowl_ontology_iterate_anon_individuals(CowlOntology *onto, void *ctx,
                                            CowlAnonIndividualIterator iter) {
    uhash_foreach_key(CowlAnonIndAxiomMap, onto->anon_ind_refs, ind, {
        if (!iter(ctx, ind)) return;
    });
}

void cowl_ontology_iterate_axioms(CowlOntology *onto, void *ctx, CowlAxiomIterator iter) {
    for (CowlAxiomType type = CAT_FIRST; type < CAT_COUNT; ++type) {
        CowlAxiomSet *axioms = onto->axioms_by_type[type];
        uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return; });
    }
}

void cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = onto->axioms_by_type[type];
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return; });
}

void cowl_ontology_iterate_axioms_for_class(CowlOntology *onto, CowlClass *owl_class,
                                            void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return; });
}

void cowl_ontology_iterate_axioms_for_data_prop(CowlOntology *onto, CowlDataProp *data_prop,
                                                void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlDataPropAxiomMap, onto->data_prop_refs, data_prop, NULL);
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return; });
}

void cowl_ontology_iterate_axioms_for_datatype(CowlOntology *onto, CowlDatatype *datatype,
                                               void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlDatatypeAxiomMap, onto->datatype_refs, datatype, NULL);
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return; });
}

void cowl_ontology_iterate_axioms_for_obj_prop(CowlOntology *onto, CowlObjProp *obj_prop,
                                               void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlObjPropAxiomMap, onto->obj_prop_refs, obj_prop, NULL);
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return; });
}

void cowl_ontology_iterate_axioms_for_named_individual(CowlOntology *onto,
                                                       CowlNamedIndividual *individual,
                                                       void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlNamedIndAxiomMap, onto->named_ind_refs, individual, NULL);
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return; });
}

void cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       void *ctx, CowlClsExpIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (axiom->type == CAT_SUB_CLASS) {
            CowlSubClsAxiom *sub_axiom = (CowlSubClsAxiom *)axiom;

            if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->super_class)) {
                if (!iter(ctx, sub_axiom->sub_class)) return;
            }
        }
    });
}

void cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         void *ctx, CowlClsExpIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (axiom->type == CAT_SUB_CLASS) {
            CowlSubClsAxiom *sub_axiom = (CowlSubClsAxiom *)axiom;

            if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->sub_class)) {
                if (!iter(ctx, sub_axiom->super_class)) return;
            }
        }
    });
}

void cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      void *ctx, CowlClsExpIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (axiom->type == CAT_EQUIVALENT_CLASSES) {
            CowlClsExpSet *eq_classes = ((CowlNAryClsAxiom *)axiom)->classes;

            uhash_uint_t cls_idx = uhash_get(CowlClsExpSet, eq_classes, (CowlClsExp *)owl_class);
            if (cls_idx < uhash_end(eq_classes)) {
                for (uhash_uint_t i = uhash_begin(eq_classes); i != uhash_end(eq_classes); ++i) {
                    if (i != cls_idx && !iter(ctx, uhash_key(eq_classes, i))) return;
                }
            }
        }
    });
}

void cowl_ontology_iterate_types(CowlOntology *onto, CowlIndividual *individual,
                                 void *ctx, CowlClsExpIterator iter) {
    CowlAxiomSet *axioms;

    if (individual->is_named) {
        axioms = uhmap_get(CowlNamedIndAxiomMap, onto->named_ind_refs,
                           (CowlNamedIndividual *)individual, NULL);
    } else {
        axioms = uhmap_get(CowlAnonIndAxiomMap, onto->anon_ind_refs,
                           (CowlAnonIndividual *)individual, NULL);
    }

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (axiom->type == CAT_CLASS_ASSERTION) {
            CowlClsAssertAxiom *assert_axiom = (CowlClsAssertAxiom *)axiom;
            if (!iter(ctx, assert_axiom->cls_exp)) return;
        }
    });
}

CowlMutableOntology* cowl_ontology_get(void) {
    return cowl_ontology_alloc();
}

CowlMutableOntology* cowl_ontology_alloc(void) {
    CowlOntology init = COWL_ONTOLOGY_INIT;
    CowlMutableOntology *ontology = malloc(sizeof(*ontology));
    memcpy(ontology, &init, sizeof(*ontology));
    return ontology;
}

void cowl_ontology_free(CowlOntology *ontology) {
    if (!ontology) return;

    cowl_ontology_id_free(ontology->id);

    for (CowlAxiomType type = CAT_FIRST; type < CAT_COUNT; type++) {
        cowl_axiom_set_free(ontology->axioms_by_type[type]);
    }

    uhash_foreach_value(CowlClassAxiomMap, ontology->class_refs, set,
                        uhash_free(CowlAxiomSet, set));
    uhash_foreach_value(CowlDataPropAxiomMap, ontology->data_prop_refs, set,
                        uhash_free(CowlAxiomSet, set));
    uhash_foreach_value(CowlDatatypeAxiomMap, ontology->datatype_refs, set,
                        uhash_free(CowlAxiomSet, set));
    uhash_foreach_value(CowlObjPropAxiomMap, ontology->obj_prop_refs, set,
                        uhash_free(CowlAxiomSet, set));
    uhash_foreach_value(CowlNamedIndAxiomMap, ontology->named_ind_refs, set,
                        uhash_free(CowlAxiomSet, set));
    uhash_foreach_value(CowlAnonIndAxiomMap, ontology->anon_ind_refs, set,
                        uhash_free(CowlAxiomSet, set));

    uhash_free(CowlClassAxiomMap, ontology->class_refs);
    uhash_free(CowlDataPropAxiomMap, ontology->data_prop_refs);
    uhash_free(CowlDatatypeAxiomMap, ontology->datatype_refs);
    uhash_free(CowlObjPropAxiomMap, ontology->obj_prop_refs);
    uhash_free(CowlNamedIndAxiomMap, ontology->named_ind_refs);
    uhash_free(CowlAnonIndAxiomMap, ontology->anon_ind_refs);

    free((void *)ontology);
}

void cowl_ontology_set_id(CowlMutableOntology *ontology, CowlOntologyId *id) {
    if (ontology->id) cowl_ontology_id_free(id);
    ontology->id = id;
}

void cowl_ontology_add_axiom(CowlMutableOntology *ontology, CowlAxiom *axiom) {

    cowl_axiom_retain(axiom);
    cowl_add_axiom_to_set_in_array(ontology->axioms_by_type, axiom->type, axiom);

    switch (axiom->type) {

        case CAT_DECLARATION: {
            CowlDeclAxiom *d_axiom = (CowlDeclAxiom *)axiom;
            cowl_ontology_add_axiom_for_entity(ontology, axiom, d_axiom->entity);
            break;
        }

        case CAT_DATATYPE_DEFINITION: {
            CowlDatatypeDefAxiom *d_axiom = (CowlDatatypeDefAxiom *)axiom;
            cowl_ontology_add_axiom_for_datatype(ontology, axiom, d_axiom->datatype);
            cowl_ontology_add_axiom_for_data_range(ontology, axiom, d_axiom->range);
            break;
        }

        case CAT_CLASS_ASSERTION: {
            CowlClsAssertAxiom *a_axiom = (CowlClsAssertAxiom *)axiom;
            cowl_ontology_add_axiom_for_individual(ontology, axiom, a_axiom->individual);
            cowl_ontology_add_axiom_for_cls_exp(ontology, axiom, a_axiom->cls_exp);
            break;
        }

        case CAT_SAME_INDIVIDUAL:
        case CAT_DIFFERENT_INDIVIDUALS: {
            CowlNAryIndividualAxiom *n_axiom = (CowlNAryIndividualAxiom *)axiom;
            CowlAxiomEntityCtx c = { .onto = ontology, .axiom = axiom };
            cowl_nary_individual_axiom_iterate_signature(n_axiom, &c, cowl_ontology_entity_adder);
            break;
        }

        case CAT_SUB_CLASS: {
            CowlSubClsAxiom *s_axiom = (CowlSubClsAxiom *)axiom;
            cowl_ontology_add_axiom_for_cls_exp(ontology, axiom, s_axiom->super_class);
            cowl_ontology_add_axiom_for_cls_exp(ontology, axiom, s_axiom->sub_class);
            break;
        }

        case CAT_EQUIVALENT_CLASSES:
        case CAT_DISJOINT_CLASSES: {
            CowlNAryClsAxiom *n_axiom = (CowlNAryClsAxiom *)axiom;
            CowlAxiomEntityCtx c = { .onto = ontology, .axiom = axiom };
            cowl_nary_cls_axiom_iterate_signature(n_axiom, &c, cowl_ontology_entity_adder);
            break;
        }

        case CAT_DISJOINT_UNION: {
            CowlDisjUnionAxiom *d_axiom = (CowlDisjUnionAxiom *)axiom;
            CowlAxiomEntityCtx c = { .onto = ontology, .axiom = axiom };
            cowl_disj_union_axiom_iterate_signature(d_axiom, &c, cowl_ontology_entity_adder);
            break;
        }

        case CAT_OBJ_PROP_ASSERTION:
        case CAT_NEGATIVE_OBJ_PROP_ASSERTION: {
            CowlObjPropAssertAxiom *a_axiom = (CowlObjPropAssertAxiom *)axiom;
            cowl_ontology_add_axiom_for_individual(ontology, axiom, a_axiom->source);
            cowl_ontology_add_axiom_for_individual(ontology, axiom, a_axiom->target);
            cowl_ontology_add_axiom_for_obj_prop_exp(ontology, axiom, a_axiom->prop_exp);
            break;
        }

        case CAT_DATA_PROP_ASSERTION:
        case CAT_NEGATIVE_DATA_PROP_ASSERTION: {
            CowlDataPropAssertAxiom *a_axiom = (CowlDataPropAssertAxiom *)axiom;
            cowl_ontology_add_axiom_for_individual(ontology, axiom, a_axiom->source);
            cowl_ontology_add_axiom_for_literal(ontology, axiom, a_axiom->target);
            cowl_ontology_add_axiom_for_data_prop_exp(ontology, axiom, a_axiom->prop);
            break;
        }

        case CAT_SUB_OBJ_PROP: {
            CowlSubObjPropAxiom *s_axiom = (CowlSubObjPropAxiom *)axiom;
            cowl_ontology_add_axiom_for_obj_prop_exp(ontology, axiom, s_axiom->super_prop);
            cowl_ontology_add_axiom_for_obj_prop_exp(ontology, axiom, s_axiom->sub_prop);
            break;
        }

        case CAT_SUB_OBJ_PROP_CHAIN: {
            CowlSubObjPropChainAxiom *s_axiom = (CowlSubObjPropChainAxiom *)axiom;
            CowlAxiomEntityCtx c = { .onto = ontology, .axiom = axiom };
            cowl_sub_obj_prop_chain_axiom_iterate_signature(s_axiom, &c,
                                                            cowl_ontology_entity_adder);
            break;
        }

        case CAT_INVERSE_OBJ_PROP: {
            CowlInvObjPropAxiom *i_axiom = (CowlInvObjPropAxiom *)axiom;
            cowl_ontology_add_axiom_for_obj_prop_exp(ontology, axiom, i_axiom->first);
            cowl_ontology_add_axiom_for_obj_prop_exp(ontology, axiom, i_axiom->second);
            break;
        }

        case CAT_EQUIVALENT_OBJ_PROP:
        case CAT_DISJOINT_OBJ_PROP: {
            CowlNAryObjPropAxiom *n_axiom = (CowlNAryObjPropAxiom *)axiom;
            CowlAxiomEntityCtx c = { .onto = ontology, .axiom = axiom };
            cowl_nary_obj_prop_axiom_iterate_signature(n_axiom, &c, cowl_ontology_entity_adder);
            break;
        }

        case CAT_OBJ_PROP_DOMAIN: {
            CowlObjPropDomainAxiom *d_axiom = (CowlObjPropDomainAxiom *)axiom;
            cowl_ontology_add_axiom_for_obj_prop_exp(ontology, axiom, d_axiom->prop_exp);
            cowl_ontology_add_axiom_for_cls_exp(ontology, axiom, d_axiom->domain);
            break;
        }

        case CAT_OBJ_PROP_RANGE: {
            CowlObjPropRangeAxiom *r_axiom = (CowlObjPropRangeAxiom *)axiom;
            cowl_ontology_add_axiom_for_obj_prop_exp(ontology, axiom, r_axiom->prop_exp);
            cowl_ontology_add_axiom_for_cls_exp(ontology, axiom, r_axiom->range);
            break;
        }

        case CAT_FUNCTIONAL_OBJ_PROP:
        case CAT_INVERSE_FUNCTIONAL_OBJ_PROP:
        case CAT_SYMMETRIC_OBJ_PROP:
        case CAT_ASYMMETRIC_OBJ_PROP:
        case CAT_REFLEXIVE_OBJ_PROP:
        case CAT_IRREFLEXIVE_OBJ_PROP:
        case CAT_TRANSITIVE_OBJ_PROP: {
            CowlObjPropCharAxiom *c_axiom = (CowlObjPropCharAxiom *)axiom;
            cowl_ontology_add_axiom_for_obj_prop_exp(ontology, axiom, c_axiom->prop_exp);
            break;
        }

        case CAT_SUB_DATA_PROP: {
            CowlSubDataPropAxiom *d_axiom = (CowlSubDataPropAxiom *)axiom;
            cowl_ontology_add_axiom_for_data_prop_exp(ontology, axiom, d_axiom->super_prop);
            cowl_ontology_add_axiom_for_data_prop_exp(ontology, axiom, d_axiom->sub_prop);
            break;
        }

        case CAT_EQUIVALENT_DATA_PROP:
        case CAT_DISJOINT_DATA_PROP: {
            CowlNAryDataPropAxiom *n_axiom = (CowlNAryDataPropAxiom *)axiom;
            CowlAxiomEntityCtx c = { .onto = ontology, .axiom = axiom };
            cowl_nary_data_prop_axiom_iterate_signature(n_axiom, &c, cowl_ontology_entity_adder);
            break;
        }

        case CAT_DATA_PROP_DOMAIN: {
            CowlDataPropDomainAxiom *d_axiom = (CowlDataPropDomainAxiom *)axiom;
            cowl_ontology_add_axiom_for_data_prop_exp(ontology, axiom, d_axiom->prop_exp);
            cowl_ontology_add_axiom_for_cls_exp(ontology, axiom, d_axiom->domain);
            break;
        }

        case CAT_DATA_PROP_RANGE: {
            CowlDataPropRangeAxiom *r_axiom = (CowlDataPropRangeAxiom *)axiom;
            cowl_ontology_add_axiom_for_data_prop_exp(ontology, axiom, r_axiom->prop_exp);
            cowl_ontology_add_axiom_for_data_range(ontology, axiom, r_axiom->range);
            break;
        }

        case CAT_FUNCTIONAL_DATA_PROP: {
            CowlFuncDataPropAxiom *f_axiom = (CowlFuncDataPropAxiom *)axiom;
            cowl_ontology_add_axiom_for_data_prop_exp(ontology, axiom, f_axiom->prop);
            break;
        }

        case CAT_HAS_KEY: {
            CowlHasKeyAxiom *k_axiom = (CowlHasKeyAxiom *)axiom;
            CowlAxiomEntityCtx c = { .onto = ontology, .axiom = axiom };
            cowl_has_key_axiom_iterate_signature(k_axiom, &c, cowl_ontology_entity_adder);
            break;
        }

        default:
            break;
    }
}

static void cowl_ontology_add_axiom_for_entity(CowlOntology *onto, CowlAxiom *axiom,
                                               CowlEntity entity) {
    switch (entity.type) {

        case CET_CLASS:
            cowl_add_axiom_to_set_in_map(CowlClassAxiomMap, onto->class_refs,
                                         entity.owl_class, axiom);
            break;

        case CET_DATA_PROP:
            cowl_add_axiom_to_set_in_map(CowlDataPropAxiomMap, onto->data_prop_refs,
                                         entity.data_prop, axiom);
            break;

        case CET_DATATYPE:
            cowl_add_axiom_to_set_in_map(CowlDatatypeAxiomMap, onto->datatype_refs,
                                         entity.datatype, axiom);
            break;

        case CET_OBJ_PROP:
            cowl_add_axiom_to_set_in_map(CowlObjPropAxiomMap, onto->obj_prop_refs,
                                         entity.obj_prop, axiom);
            break;

        case CET_NAMED_INDIVIDUAL:
            cowl_add_axiom_to_set_in_map(CowlNamedIndAxiomMap, onto->named_ind_refs,
                                         entity.named_ind, axiom);
            break;

        default:
            break;
    }
}

static bool cowl_ontology_entity_adder(void *ctx, CowlEntity entity) {
    CowlAxiomEntityCtx *axiom_ctx = (CowlAxiomEntityCtx *)ctx;
    cowl_ontology_add_axiom_for_entity(axiom_ctx->onto, axiom_ctx->axiom, entity);
    return true;
}

static void cowl_ontology_add_axiom_for_class(CowlOntology *onto, CowlAxiom *axiom,
                                              CowlClass *cls) {
    cowl_add_axiom_to_set_in_map(CowlClassAxiomMap, onto->class_refs, cls, axiom);
}

static void cowl_ontology_add_axiom_for_cls_exp(CowlOntology *onto, CowlAxiom *axiom,
                                                CowlClsExp *exp) {
    if (exp->type == CCET_CLASS) {
        cowl_ontology_add_axiom_for_class(onto, axiom, (CowlClass *)exp);
    } else {
        CowlAxiomEntityCtx ctx = { .onto = onto, .axiom = axiom };
        cowl_cls_exp_iterate_signature(exp, &ctx, cowl_ontology_entity_adder);
    }
}

static void cowl_ontology_add_axiom_for_data_prop_exp(CowlOntology *onto, CowlAxiom *axiom,
                                                      CowlDataPropExp *prop_exp) {
    cowl_add_axiom_to_set_in_map(CowlDataPropAxiomMap, onto->data_prop_refs,
                                 (CowlDataProp *)prop_exp, axiom);
}

static void cowl_ontology_add_axiom_for_data_range(CowlOntology *onto, CowlAxiom *axiom,
                                                   CowlDataRange *range) {
    if (range->type == CDRT_DATATYPE) {
        cowl_ontology_add_axiom_for_datatype(onto, axiom, (CowlDatatype *)range);
    } else {
        CowlAxiomEntityCtx ctx = { .onto = onto, .axiom = axiom };
        cowl_data_range_iterate_signature(range, &ctx, cowl_ontology_entity_adder);
    }
}

static void cowl_ontology_add_axiom_for_datatype(CowlOntology *onto, CowlAxiom *axiom,
                                                 CowlDatatype *datatype) {
    cowl_add_axiom_to_set_in_map(CowlDatatypeAxiomMap, onto->datatype_refs, datatype, axiom);
}

static void cowl_ontology_add_axiom_for_literal(CowlOntology *onto, CowlAxiom *axiom,
                                                CowlLiteral *literal) {
    cowl_ontology_add_axiom_for_datatype(onto, axiom, literal->dt);
}

static void cowl_ontology_add_axiom_for_individual(CowlOntology *onto, CowlAxiom *axiom,
                                                   CowlIndividual *individual) {
    if (individual->is_named) {
        cowl_add_axiom_to_set_in_map(CowlNamedIndAxiomMap, onto->named_ind_refs,
                                     (CowlNamedIndividual *)individual, axiom);
    } else {
        cowl_add_axiom_to_set_in_map(CowlAnonIndAxiomMap, onto->anon_ind_refs,
                                     (CowlAnonIndividual *)individual, axiom);
    }
}

static void cowl_ontology_add_axiom_for_obj_prop_exp(CowlOntology *onto, CowlAxiom *axiom,
                                                     CowlObjPropExp *prop_exp) {
    if (!prop_exp->is_inverse) {
        cowl_add_axiom_to_set_in_map(CowlObjPropAxiomMap, onto->obj_prop_refs,
                                     (CowlObjProp *)prop_exp, axiom);
    }
}
