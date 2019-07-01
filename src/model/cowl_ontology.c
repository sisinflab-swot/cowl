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

UHASH_MAP_IMPL(CowlNamedIndAxiomMap, CowlNamedInd*, CowlAxiomSet*,
               cowl_named_ind_hash, cowl_named_ind_equals)

UHASH_MAP_IMPL(CowlAnonIndAxiomMap, CowlAnonInd*, CowlAxiomSet*,
               cowl_anon_ind_hash, cowl_anon_ind_equals)

typedef cowl_struct(CowlAxiomEntityCtx) {
    CowlOntology *onto;
    CowlAxiom *axiom;
} CowlAxiomEntityCtx;

static cowl_struct(CowlOntology)* cowl_ontology_alloc(void);
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
    return lhs == rhs || cowl_ontology_id_equals(lhs->id, rhs->id);
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

cowl_uint_t cowl_ontology_axiom_count_for_named_ind(CowlOntology *onto, CowlNamedInd *ind) {
    CowlAxiomSet *axioms = uhmap_get(CowlNamedIndAxiomMap, onto->named_ind_refs, ind, NULL);
    cowl_uint_t count = uhash_count(axioms);

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        count += cowl_ontology_axiom_count_for_named_ind(import, ind);
    });

    return count;
}

bool cowl_ontology_iterate_signature(CowlOntology *onto, CowlEntityIterator *iter) {
    uhash_foreach_key(CowlClassAxiomMap, onto->class_refs, cls, {
        if (!cowl_iterate(iter, cowl_entity_wrap_class(cls))) return false;
    });

    uhash_foreach_key(CowlNamedIndAxiomMap, onto->named_ind_refs, ind, {
        if (!cowl_iterate(iter, cowl_entity_wrap_named_ind(ind))) return false;
    });

    uhash_foreach_key(CowlDatatypeAxiomMap, onto->datatype_refs, datatype, {
        if (!cowl_iterate(iter, cowl_entity_wrap_datatype(datatype))) return false;
    });

    uhash_foreach_key(CowlObjPropAxiomMap, onto->obj_prop_refs, prop, {
        if (!cowl_iterate(iter, cowl_entity_wrap_obj_prop(prop))) return false;
    });

    uhash_foreach_key(CowlDataPropAxiomMap, onto->data_prop_refs, prop, {
        if (!cowl_iterate(iter, cowl_entity_wrap_data_prop(prop))) return false;
    });

    uhash_foreach_key(CowlAnnotPropAxiomMap, onto->annot_prop_refs, prop, {
        if (!cowl_iterate(iter, cowl_entity_wrap_annot_prop(prop))) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_signature(import, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_imports(CowlOntology *onto, CowlOntologyIterator *iter) {
    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_iterate(iter, import)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_imports(import, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_classes(CowlOntology *onto, CowlClassIterator *iter) {
    uhash_foreach_key(CowlClassAxiomMap, onto->class_refs, cls, {
        if (!cowl_iterate(iter, cls)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_classes(import, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_data_props(CowlOntology *onto, CowlDataPropIterator *iter) {
    uhash_foreach_key(CowlDataPropAxiomMap, onto->data_prop_refs, prop, {
        if (!cowl_iterate(iter, prop)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_data_props(import, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_datatypes(CowlOntology *onto, CowlDatatypeIterator *iter) {
    uhash_foreach_key(CowlDatatypeAxiomMap, onto->datatype_refs, datatype, {
        if (!cowl_iterate(iter, datatype)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_datatypes(import, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_obj_props(CowlOntology *onto, CowlObjPropIterator *iter) {
    uhash_foreach_key(CowlObjPropAxiomMap, onto->obj_prop_refs, prop, {
        if (!cowl_iterate(iter, prop)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_obj_props(import, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_annot_props(CowlOntology *onto, CowlAnnotPropIterator *iter) {
    uhash_foreach_key(CowlAnnotPropAxiomMap, onto->annot_prop_refs, prop, {
        if (!cowl_iterate(iter, prop)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_annot_props(import, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_named_inds(CowlOntology *onto, CowlNamedIndIterator *iter) {
    uhash_foreach_key(CowlNamedIndAxiomMap, onto->named_ind_refs, ind, {
        if (!cowl_iterate(iter, ind)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_named_inds(import, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_anon_inds(CowlOntology *onto, CowlAnonIndIterator *iter) {
    uhash_foreach_key(CowlAnonIndAxiomMap, onto->anon_ind_refs, ind, {
        if (!cowl_iterate(iter, ind)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_anon_inds(import, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms(CowlOntology *onto, CowlAxiomIterator *iter) {
    for (CowlAxiomType type = CAT_FIRST; type < CAT_COUNT; ++type) {
        CowlAxiomSet *axioms = onto->axioms_by_type[type];
        uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
            if (!cowl_iterate(iter, axiom)) return false;
        });
    }

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms(import, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          CowlAxiomIterator *iter) {
    CowlAxiomSet *axioms = onto->axioms_by_type[type];

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (!cowl_iterate(iter, axiom)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_of_type(import, type, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_for_annot_prop(CowlOntology *onto, CowlAnnotProp *prop,
                                                 CowlAxiomIterator *iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlAnnotPropAxiomMap, onto->annot_prop_refs, prop, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (!cowl_iterate(iter, axiom)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_for_annot_prop(import, prop, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_for_class(CowlOntology *onto, CowlClass *owl_class,
                                            CowlAxiomIterator *iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (!cowl_iterate(iter, axiom)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_for_class(import, owl_class, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_for_data_prop(CowlOntology *onto, CowlDataProp *prop,
                                                CowlAxiomIterator *iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlDataPropAxiomMap, onto->data_prop_refs, prop, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (!cowl_iterate(iter, axiom)) return false; }
    );

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_for_data_prop(import, prop, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_for_datatype(CowlOntology *onto, CowlDatatype *datatype,
                                               CowlAxiomIterator *iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlDatatypeAxiomMap, onto->datatype_refs, datatype, NULL);
    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (!cowl_iterate(iter, axiom)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_for_datatype(import, datatype, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_for_obj_prop(CowlOntology *onto, CowlObjProp *prop,
                                               CowlAxiomIterator *iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlObjPropAxiomMap, onto->obj_prop_refs, prop, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (!cowl_iterate(iter, axiom)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_for_obj_prop(import, prop, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms_for_named_ind(CowlOntology *onto, CowlNamedInd *ind,
                                                CowlAxiomIterator *iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlNamedIndAxiomMap, onto->named_ind_refs, ind, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (!cowl_iterate(iter, axiom)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_for_named_ind(import, ind, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       CowlClsExpIterator *iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (cowl_axiom_flags_get_type(axiom->flags) == CAT_SUB_CLASS) {
            CowlSubClsAxiom *sub_axiom = (CowlSubClsAxiom *)axiom;

            if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->super_class)) {
                if (!cowl_iterate(iter, sub_axiom->sub_class)) return false;
            }
        }
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_sub_classes(import, owl_class, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         CowlClsExpIterator *iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (cowl_axiom_flags_get_type(axiom->flags) == CAT_SUB_CLASS) {
            CowlSubClsAxiom *sub_axiom = (CowlSubClsAxiom *)axiom;

            if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->sub_class)) {
                if (!cowl_iterate(iter, sub_axiom->super_class)) return false;
            }
        }
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_super_classes(import, owl_class, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      CowlClsExpIterator *iter) {
    CowlAxiomSet *axioms = uhmap_get(CowlClassAxiomMap, onto->class_refs, owl_class, NULL);

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (cowl_axiom_flags_get_type(axiom->flags) == CAT_EQUIVALENT_CLASSES) {
            CowlClsExpSet *eq_classes = ((CowlNAryClsAxiom *)axiom)->classes;

            uhash_uint_t cls_idx = uhash_get(CowlClsExpSet, eq_classes, (CowlClsExp *)owl_class);
            if (cls_idx < uhash_end(eq_classes)) {
                for (uhash_uint_t i = uhash_begin(eq_classes); i != uhash_end(eq_classes); ++i) {
                    if (i != cls_idx && !cowl_iterate(iter, uhash_key(eq_classes, i))) return false;
                }
            }
        }
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_eq_classes(import, owl_class, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_types(CowlOntology *onto, CowlIndividual *ind,
                                 CowlClsExpIterator *iter) {
    CowlAxiomSet *axioms;

    if (ind->is_named) {
        axioms = uhmap_get(CowlNamedIndAxiomMap, onto->named_ind_refs, (CowlNamedInd *)ind, NULL);
    } else {
        axioms = uhmap_get(CowlAnonIndAxiomMap, onto->anon_ind_refs, (CowlAnonInd *)ind, NULL);
    }

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (cowl_axiom_flags_get_type(axiom->flags) == CAT_CLASS_ASSERTION) {
            CowlClsAssertAxiom *assert_axiom = (CowlClsAssertAxiom *)axiom;
            if (!cowl_iterate(iter, assert_axiom->cls_exp)) return false;
        }
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_types(import, ind, iter)) return false;
    });

    return true;
}

cowl_struct(CowlOntology)* cowl_ontology_get(void) {
    return cowl_ontology_alloc();
}

cowl_struct(CowlOntology)* cowl_ontology_alloc(void) {
    CowlOntology init = COWL_ONTOLOGY_INIT;
    cowl_struct(CowlOntology) *onto = malloc(sizeof(*onto));
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

void cowl_ontology_set_id(cowl_struct(CowlOntology) *onto, CowlOntologyId *id) {
    onto->id = id;
}

void cowl_ontology_set_annot(cowl_struct(CowlOntology) *onto,
                             Vector(CowlAnnotationPtr) *annot) {
    onto->annotations = annot;
}

void cowl_ontology_set_imports(cowl_struct(CowlOntology) *onto, Vector(CowlOntologyPtr) *imports) {
    onto->imports = imports;
}

void cowl_ontology_add_axiom(cowl_struct(CowlOntology) *onto, CowlAxiom *axiom) {

    cowl_axiom_retain(axiom);
    CowlAxiomType type = cowl_axiom_flags_get_type(axiom->flags);
    cowl_add_axiom_to_set_in_array(onto->axioms_by_type, type, axiom);

    CowlAxiomEntityCtx c = { .onto = onto, .axiom = axiom };
    CowlEntityIterator iter = cowl_iterator_init(CowlEntity, &c, cowl_ontology_entity_adder);
    cowl_axiom_iterate_signature(axiom, &iter);
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

        case CET_ANNOT_PROP:
            cowl_add_axiom_to_set_in_map(CowlAnnotPropAxiomMap, onto->annot_prop_refs,
                                         entity.annot_prop, axiom);
            break;

        case CET_NAMED_IND:
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
