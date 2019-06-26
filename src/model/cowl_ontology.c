/// @author Ivano Bilenchi

#include "cowl_ontology_private.h"
#include "cowl_ontology_vec.h"
#include "cowl_private.h"

UHASH_MAP_IMPL(CowlAnnotPropAxiomMap, CowlAnnotProp*, CowlAxiomSet*,
               cowl_annot_prop_hash, cowl_annot_prop_equals)

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
static void cowl_ontology_free(CowlOntology *onto);

static bool cowl_ontology_entity_adder(void *ctx, CowlEntity entity);
static void cowl_ontology_add_axiom_for_entity(CowlOntology *onto, CowlAxiom *axiom,
                                               CowlEntity entity);

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

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        count += cowl_ontology_axiom_count(import);
    });

    return count;
}

cowl_uint_t cowl_ontology_imports_count(CowlOntology *onto) {
    cowl_uint_t count = vector_count(onto->imports);

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        count += cowl_ontology_imports_count(import);
    });

    return count;
}

cowl_uint_t cowl_ontology_axiom_count_for_annot_prop(CowlOntology *onto, CowlAnnotProp *prop) {
    CowlAxiomSet *axioms = uhmap_get(CowlAnnotPropAxiomMap, onto->annot_prop_refs, prop, NULL);
    cowl_uint_t count = uhash_count(axioms);

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        count += cowl_ontology_axiom_count_for_annot_prop(import, prop);
    });

    return count;
}

cowl_uint_t cowl_ontology_axiom_count_for_class(CowlOntology *onto, CowlClass *owl_class) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);
    cowl_uint_t count = uhash_count(axioms);

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        count += cowl_ontology_axiom_count_for_class(import, owl_class);
    });

    return count;
}

cowl_uint_t cowl_ontology_axiom_count_for_data_prop(CowlOntology *onto, CowlDataProp *prop) {
    CowlAxiomSet *axioms = uhmap_get(CowlDataPropAxiomMap, onto->data_prop_refs, prop, NULL);
    cowl_uint_t count = uhash_count(axioms);

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        count += cowl_ontology_axiom_count_for_data_prop(import, prop);
    });

    return count;
}

cowl_uint_t cowl_ontology_axiom_count_for_datatype(CowlOntology *onto, CowlDatatype *datatype) {
    CowlAxiomSet *axioms = uhmap_get(CowlDatatypeAxiomMap, onto->datatype_refs, datatype, NULL);
    cowl_uint_t count = uhash_count(axioms);

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        count += cowl_ontology_axiom_count_for_datatype(import, datatype);
    });

    return count;
}

cowl_uint_t cowl_ontology_axiom_count_for_obj_prop(CowlOntology *onto, CowlObjProp *prop) {
    CowlAxiomSet *axioms = uhmap_get(CowlObjPropAxiomMap, onto->obj_prop_refs, prop, NULL);
    cowl_uint_t count = uhash_count(axioms);

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        count += cowl_ontology_axiom_count_for_obj_prop(import, prop);
    });

    return count;
}

cowl_uint_t cowl_ontology_axiom_count_for_named_individual(CowlOntology *onto,
                                                           CowlNamedIndividual *ind) {
    CowlAxiomSet *axioms = uhmap_get(CowlNamedIndAxiomMap, onto->named_ind_refs, ind, NULL);
    cowl_uint_t count = uhash_count(axioms);

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        count += cowl_ontology_axiom_count_for_named_individual(import, ind);
    });

    return count;
}

bool cowl_ontology_iterate_signature(CowlOntology *onto, void *ctx, CowlEntityIterator iter) {
    uhash_foreach_key(CowlClassAxiomMap, onto->class_refs, cls, {
        if (!iter(ctx, cowl_entity_wrap_class(cls))) return false;
    });

    uhash_foreach_key(CowlNamedIndAxiomMap, onto->named_ind_refs, ind, {
        if (!iter(ctx, cowl_entity_wrap_named_individual(ind))) return false;
    });

    uhash_foreach_key(CowlDatatypeAxiomMap, onto->datatype_refs, datatype, {
        if (!iter(ctx, cowl_entity_wrap_datatype(datatype))) return false;
    });

    uhash_foreach_key(CowlObjPropAxiomMap, onto->obj_prop_refs, prop, {
        if (!iter(ctx, cowl_entity_wrap_obj_prop(prop))) return false;
    });

    uhash_foreach_key(CowlDataPropAxiomMap, onto->data_prop_refs, prop, {
        if (!iter(ctx, cowl_entity_wrap_data_prop(prop))) return false;
    });

    uhash_foreach_key(CowlAnnotPropAxiomMap, onto->annot_prop_refs, prop, {
        if (!iter(ctx, cowl_entity_wrap_annot_prop(prop))) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_signature(import, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_imports(CowlOntology *onto, void *ctx, CowlOntologyIterator iter) {
    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!iter(ctx, import)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_imports(import, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_classes(CowlOntology *onto, void *ctx, CowlClassIterator iter) {
    uhash_foreach_key(CowlClassAxiomMap, onto->class_refs, cls, {
        if (!iter(ctx, cls)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_classes(import, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_data_prop(CowlOntology *onto, void *ctx, CowlDataPropIterator iter) {
    uhash_foreach_key(CowlDataPropAxiomMap, onto->data_prop_refs, prop, {
        if (!iter(ctx, prop)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_data_prop(import, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_datatypes(CowlOntology *onto, void *ctx, CowlDatatypeIterator iter) {
    uhash_foreach_key(CowlDatatypeAxiomMap, onto->datatype_refs, datatype, {
        if (!iter(ctx, datatype)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_datatypes(import, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_obj_prop(CowlOntology *onto, void *ctx, CowlObjPropIterator iter) {
    uhash_foreach_key(CowlObjPropAxiomMap, onto->obj_prop_refs, prop, {
        if (!iter(ctx, prop)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_obj_prop(import, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_annot_prop(CowlOntology *onto, void *ctx, CowlAnnotPropIterator iter) {
    uhash_foreach_key(CowlAnnotPropAxiomMap, onto->annot_prop_refs, prop, {
        if (!iter(ctx, prop)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_annot_prop(import, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_named_individuals(CowlOntology *onto, void *ctx,
                                             CowlNamedIndividualIterator iter) {
    uhash_foreach_key(CowlNamedIndAxiomMap, onto->named_ind_refs, ind, {
        if (!iter(ctx, ind)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_named_individuals(import, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_anon_individuals(CowlOntology *onto, void *ctx,
                                            CowlAnonIndividualIterator iter) {
    uhash_foreach_key(CowlAnonIndAxiomMap, onto->anon_ind_refs, ind, {
        if (!iter(ctx, ind)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_anon_individuals(import, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms(CowlOntology *onto, void *ctx, CowlAxiomIterator iter) {
    for (CowlAxiomType type = CAT_FIRST; type < CAT_COUNT; ++type) {
        CowlAxiomSet *axioms = onto->axioms_by_type[type];
        uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return false; });
    }

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms(import, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = onto->axioms_by_type[type];
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return false; });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_of_type(import, type, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_for_annot_prop(CowlOntology *onto, CowlAnnotProp *prop,
                                                 void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlAnnotPropAxiomMap, onto->annot_prop_refs, prop, NULL);
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return false; });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_for_annot_prop(import, prop, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_for_class(CowlOntology *onto, CowlClass *owl_class,
                                            void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return false; });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_for_class(import, owl_class, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_for_data_prop(CowlOntology *onto, CowlDataProp *prop,
                                                void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlDataPropAxiomMap, onto->data_prop_refs, prop, NULL);
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return false; });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_for_data_prop(import, prop, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_for_datatype(CowlOntology *onto, CowlDatatype *datatype,
                                               void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlDatatypeAxiomMap, onto->datatype_refs, datatype, NULL);
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return false; });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_for_datatype(import, datatype, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_for_obj_prop(CowlOntology *onto, CowlObjProp *prop,
                                               void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlObjPropAxiomMap, onto->obj_prop_refs, prop, NULL);
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return false; });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_for_obj_prop(import, prop, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_for_named_individual(CowlOntology *onto,
                                                       CowlNamedIndividual *ind,
                                                       void *ctx, CowlAxiomIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlNamedIndAxiomMap, onto->named_ind_refs, ind, NULL);
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, { if (!iter(ctx, axiom)) return false; });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_for_named_individual(import, ind, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       void *ctx, CowlClsExpIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (cowl_axiom_flags_get_type(axiom->flags) == CAT_SUB_CLASS) {
            CowlSubClsAxiom *sub_axiom = (CowlSubClsAxiom *)axiom;

            if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->super_class)) {
                if (!iter(ctx, sub_axiom->sub_class)) return false;
            }
        }
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_sub_classes(import, owl_class, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         void *ctx, CowlClsExpIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (cowl_axiom_flags_get_type(axiom->flags) == CAT_SUB_CLASS) {
            CowlSubClsAxiom *sub_axiom = (CowlSubClsAxiom *)axiom;

            if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->sub_class)) {
                if (!iter(ctx, sub_axiom->super_class)) return false;
            }
        }
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_super_classes(import, owl_class, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      void *ctx, CowlClsExpIterator iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (cowl_axiom_flags_get_type(axiom->flags) == CAT_EQUIVALENT_CLASSES) {
            CowlClsExpSet *eq_classes = ((CowlNAryClsAxiom *)axiom)->classes;

            uhash_uint_t cls_idx = uhash_get(CowlClsExpSet, eq_classes, (CowlClsExp *)owl_class);
            if (cls_idx < uhash_end(eq_classes)) {
                for (uhash_uint_t i = uhash_begin(eq_classes); i != uhash_end(eq_classes); ++i) {
                    if (i != cls_idx && !iter(ctx, uhash_key(eq_classes, i))) return false;
                }
            }
        }
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_eq_classes(import, owl_class, ctx, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_types(CowlOntology *onto, CowlIndividual *ind,
                                 void *ctx, CowlClsExpIterator iter) {
    CowlAxiomSet *axioms;

    if (ind->is_named) {
        axioms = uhmap_get(CowlNamedIndAxiomMap, onto->named_ind_refs,
                           (CowlNamedIndividual *)ind, NULL);
    } else {
        axioms = uhmap_get(CowlAnonIndAxiomMap, onto->anon_ind_refs,
                           (CowlAnonIndividual *)ind, NULL);
    }

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (cowl_axiom_flags_get_type(axiom->flags) == CAT_CLASS_ASSERTION) {
            CowlClsAssertAxiom *assert_axiom = (CowlClsAssertAxiom *)axiom;
            if (!iter(ctx, assert_axiom->cls_exp)) return false;
        }
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_types(import, ind, ctx, iter)) return false;
    });

    return true;
}

CowlMutableOntology* cowl_ontology_get(void) {
    return cowl_ontology_alloc();
}

CowlMutableOntology* cowl_ontology_alloc(void) {
    CowlOntology init = COWL_ONTOLOGY_INIT;
    CowlMutableOntology *onto = malloc(sizeof(*onto));
    memcpy(onto, &init, sizeof(*onto));
    return onto;
}

void cowl_ontology_free(CowlOntology *onto) {
    if (!onto) return;

    cowl_ontology_id_free(onto->id);
    cowl_ontology_vec_free(onto->imports);
    cowl_annotation_vec_free(onto->annotations);

    for (CowlAxiomType type = CAT_FIRST; type < CAT_COUNT; type++) {
        cowl_axiom_set_free(onto->axioms_by_type[type]);
    }

    uhash_foreach_value(CowlAnnotPropAxiomMap, onto->annot_prop_refs, set,
                        uhash_free(CowlAxiomSet, set));
    uhash_foreach_value(CowlClassAxiomMap, onto->class_refs, set,
                        uhash_free(CowlAxiomSet, set));
    uhash_foreach_value(CowlDataPropAxiomMap, onto->data_prop_refs, set,
                        uhash_free(CowlAxiomSet, set));
    uhash_foreach_value(CowlDatatypeAxiomMap, onto->datatype_refs, set,
                        uhash_free(CowlAxiomSet, set));
    uhash_foreach_value(CowlObjPropAxiomMap, onto->obj_prop_refs, set,
                        uhash_free(CowlAxiomSet, set));
    uhash_foreach_value(CowlNamedIndAxiomMap, onto->named_ind_refs, set,
                        uhash_free(CowlAxiomSet, set));
    uhash_foreach_value(CowlAnonIndAxiomMap, onto->anon_ind_refs, set,
                        uhash_free(CowlAxiomSet, set));

    uhash_free(CowlAnnotPropAxiomMap, onto->annot_prop_refs);
    uhash_free(CowlClassAxiomMap, onto->class_refs);
    uhash_free(CowlDataPropAxiomMap, onto->data_prop_refs);
    uhash_free(CowlDatatypeAxiomMap, onto->datatype_refs);
    uhash_free(CowlObjPropAxiomMap, onto->obj_prop_refs);
    uhash_free(CowlNamedIndAxiomMap, onto->named_ind_refs);
    uhash_free(CowlAnonIndAxiomMap, onto->anon_ind_refs);

    free((void *)onto);
}

void cowl_ontology_set_id(CowlMutableOntology *onto, CowlOntologyId *id) {
    onto->id = id;
}

void cowl_ontology_set_annotations(CowlMutableOntology *onto, Vector(CowlAnnotationPtr) *annot) {
    onto->annotations = annot;
}

void cowl_ontology_set_imports(CowlMutableOntology *onto, Vector(CowlOntologyPtr) *imports) {
    onto->imports = imports;
}

void cowl_ontology_add_axiom(CowlMutableOntology *onto, CowlAxiom *axiom) {

    cowl_axiom_retain(axiom);
    CowlAxiomType type = cowl_axiom_flags_get_type(axiom->flags);
    cowl_add_axiom_to_set_in_array(onto->axioms_by_type, type, axiom);

    CowlAxiomEntityCtx c = { .onto = onto, .axiom = axiom };
    cowl_axiom_iterate_signature(axiom, &c, cowl_ontology_entity_adder);
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

        case CET_ANNOTATION_PROP:
            cowl_add_axiom_to_set_in_map(CowlAnnotPropAxiomMap, onto->annot_prop_refs,
                                         entity.annot_prop, axiom);
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
