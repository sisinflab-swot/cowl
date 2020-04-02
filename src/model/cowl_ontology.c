/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ontology_private.h"
#include "cowl_ontology_vec.h"
#include "cowl_private.h"

UHASH_IMPL(CowlAnnotPropAxiomMap, cowl_annot_prop_hash, cowl_annot_prop_equals)
UHASH_IMPL(CowlClassAxiomMap, cowl_class_hash, cowl_class_equals)
UHASH_IMPL(CowlDataPropAxiomMap, cowl_data_prop_hash, cowl_data_prop_equals)
UHASH_IMPL(CowlDatatypeAxiomMap, cowl_datatype_hash, cowl_datatype_equals)
UHASH_IMPL(CowlObjPropAxiomMap, cowl_obj_prop_hash, cowl_obj_prop_equals)
UHASH_IMPL(CowlNamedIndAxiomMap, cowl_named_ind_hash, cowl_named_ind_equals)
UHASH_IMPL(CowlAnonIndAxiomMap, cowl_anon_ind_hash, cowl_anon_ind_equals)

typedef cowl_struct(CowlAxiomCtx) {
    CowlOntology *onto;
    CowlAxiom *axiom;
} CowlAxiomCtx;

// Private prototypes

static CowlOntology* cowl_ontology_alloc(void);
static void cowl_ontology_free(CowlOntology *onto);

static inline UHash(CowlAnonIndAxiomMap)* cowl_ontology_get_anon_ind_refs(CowlOntology *onto);
void cowl_ontology_anon_ind_refs_init(CowlOntology *onto);

#define cowl_ontology_get_class_refs(ONTO) ((ONTO)->class_refs)
#define cowl_ontology_get_datatype_refs(ONTO) ((ONTO)->datatype_refs)
#define cowl_ontology_get_obj_prop_refs(ONTO) ((ONTO)->obj_prop_refs)
#define cowl_ontology_get_data_prop_refs(ONTO) ((ONTO)->data_prop_refs)
#define cowl_ontology_get_annot_prop_refs(ONTO) ((ONTO)->annot_prop_refs)
#define cowl_ontology_get_named_ind_refs(ONTO) ((ONTO)->named_ind_refs)

static void cowl_ontology_add_axiom_for_entity(CowlOntology *onto, CowlAxiom *axiom,
                                               CowlEntity entity);
static void cowl_ontology_add_axiom_for_anon_ind(CowlOntology *onto, CowlAxiom *axiom,
                                                 CowlAnonInd *ind);

static bool cowl_ontology_entity_adder(void *ctx, CowlEntity entity);
static bool cowl_ontology_anon_ind_adder(void *ctx, CowlAnonInd *ind);
static bool cowl_ontology_lazy_anon_ind_init(void *ctx, CowlAxiom *axiom);

// Utils

#define cowl_add_axiom_to_vec_in_map(T, map, key, axiom) do {                                       \
    uhash_uint_t k;                                                                                 \
    uhash_ret_t ret = uhash_put(T, map, key, &k);                                                   \
                                                                                                    \
    if (ret == UHASH_INSERTED) {                                                                    \
        uhash_value(map, k) = vector_alloc(CowlAxiomPtr);                                           \
    }                                                                                               \
                                                                                                    \
    if (axiom) vector_push(CowlAxiomPtr, uhash_value(map, k), axiom);                               \
} while(0)

// Public API

CowlOntology* cowl_ontology_retain(CowlOntology *onto) {
    return cowl_object_retain(onto);
}

void cowl_ontology_release(CowlOntology *onto) {
    if (onto && !cowl_object_release(onto)) {
        cowl_ontology_free(onto);
    }
}

CowlOntologyID* cowl_ontology_get_id(CowlOntology *onto) {
    return onto->id;
}

CowlAnnotationVec* cowl_ontology_get_annot(CowlOntology *onto) {
    return onto->annotations;
}

bool cowl_ontology_equals(CowlOntology *lhs, CowlOntology *rhs) {
    return lhs == rhs || cowl_ontology_id_equals(lhs->id, rhs->id);
}

cowl_uint_t cowl_ontology_hash(CowlOntology *onto) {
    return cowl_ontology_id_hash(onto->id);
}

cowl_uint_t cowl_ontology_axiom_count(CowlOntology *onto) {
    cowl_uint_t count = 0;

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
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

cowl_uint_t cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type) {
    cowl_uint_t count = uhash_count(onto->axioms_by_type[type]);

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        count += cowl_ontology_axiom_count_for_type(import, type);
    });

    return count;
}

#define COWL_ONTOLOGY_ENTITY_QUERY_IMPL(T, SINGULAR, PLURAL)                                        \
                                                                                                    \
static void cowl_ontology_get_imported_##PLURAL(CowlOntology *onto, UHash(T##AxiomMap) *set) {      \
    vector_foreach(CowlOntologyPtr, onto->imports, import, {                                        \
        uhset_union(T##AxiomMap, set, cowl_ontology_get_##SINGULAR##_refs(import));                 \
        cowl_ontology_get_imported_##PLURAL(import, set);                                           \
    });                                                                                             \
}                                                                                                   \
                                                                                                    \
static UHash(T##AxiomMap)* cowl_ontology_get_all_##PLURAL(CowlOntology *onto, bool *should_free) {  \
    UHash(T##AxiomMap) *set = cowl_ontology_get_##SINGULAR##_refs(onto);                            \
                                                                                                    \
    if (vector_count(onto->imports)) {                                                              \
        set = uhash_copy_as_set(T##AxiomMap, set);                                                  \
        cowl_ontology_get_imported_##PLURAL(onto, set);                                             \
        *should_free = true;                                                                        \
    } else {                                                                                        \
        *should_free = false;                                                                       \
    }                                                                                               \
                                                                                                    \
    return set;                                                                                     \
}                                                                                                   \
                                                                                                    \
cowl_uint_t cowl_ontology_##PLURAL##_count(CowlOntology *onto) {                                    \
    bool should_free;                                                                               \
    UHash(T##AxiomMap) *set = cowl_ontology_get_all_##PLURAL(onto, &should_free);                   \
    cowl_uint_t count = uhash_count(set);                                                           \
    if (should_free) uhash_free(T##AxiomMap, set);                                                  \
    return count;                                                                                   \
}                                                                                                   \
                                                                                                    \
bool cowl_ontology_iterate_##PLURAL(CowlOntology *onto, T##Iterator *iter) {                        \
    cowl_ontology_foreach(T, SINGULAR, PLURAL, {                                                    \
        if (!cowl_iterate(iter, SINGULAR)) return false;                                            \
    });                                                                                             \
    return true;                                                                                    \
}                                                                                                   \
                                                                                                    \
cowl_uint_t cowl_ontology_axiom_count_for_##SINGULAR(CowlOntology *onto, T *entity) {               \
    UHash(T##AxiomMap) *map = cowl_ontology_get_##SINGULAR##_refs(onto);                            \
    Vector(CowlAxiomPtr) *axioms = uhmap_get(T##AxiomMap, map, entity, NULL);                       \
    cowl_uint_t count = vector_count(axioms);                                                       \
                                                                                                    \
    vector_foreach(CowlOntologyPtr, onto->imports, import, {                                        \
        count += cowl_ontology_axiom_count_for_##SINGULAR(import, entity);                          \
    });                                                                                             \
                                                                                                    \
    return count;                                                                                   \
}                                                                                                   \
                                                                                                    \
bool cowl_ontology_iterate_axioms_for_##SINGULAR(CowlOntology *onto, T *entity,                     \
                                                 CowlAxiomIterator *iter) {                         \
    UHash(T##AxiomMap) *map = cowl_ontology_get_##SINGULAR##_refs(onto);                            \
    Vector(CowlAxiomPtr) *axioms = uhmap_get(T##AxiomMap, map, entity, NULL);                       \
                                                                                                    \
    vector_foreach(CowlAxiomPtr, axioms, axiom, {                                                   \
        if (!cowl_iterate(iter, axiom)) return false;                                               \
    });                                                                                             \
                                                                                                    \
    vector_foreach(CowlOntologyPtr, onto->imports, import, {                                        \
        if (!cowl_ontology_iterate_axioms_for_##SINGULAR(import, entity, iter)) return false;       \
    });                                                                                             \
                                                                                                    \
    return true;                                                                                    \
}

#define cowl_ontology_foreach(T, SINGULAR, PLURAL, CODE) do {                                       \
    bool should_free = false;                                                                       \
    UHash(T##AxiomMap) *SINGULAR##_set;                                                             \
    SINGULAR##_set = cowl_ontology_get_all_##PLURAL(onto, &should_free);                            \
    uhash_foreach_key(T##AxiomMap, SINGULAR##_set, SINGULAR, CODE);                                 \
    if (should_free) uhash_free(T##AxiomMap, SINGULAR##_set);                                       \
} while(0)

COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlClass, class, classes)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlDatatype, datatype, datatypes)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlObjProp, obj_prop, obj_props)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlDataProp, data_prop, data_props)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlAnnotProp, annot_prop, annot_props)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlNamedInd, named_ind, named_inds)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlAnonInd, anon_ind, anon_inds)

bool cowl_ontology_iterate_signature(CowlOntology *onto, CowlEntityIterator *iter) {

    cowl_ontology_foreach(CowlClass, class, classes, {
        if (!cowl_iterate(iter, cowl_entity_wrap_class(class))) return false;
    });

    cowl_ontology_foreach(CowlDatatype, datatype, datatypes, {
        if (!cowl_iterate(iter, cowl_entity_wrap_datatype(datatype))) return false;
    });

    cowl_ontology_foreach(CowlObjProp, obj_prop, obj_props, {
        if (!cowl_iterate(iter, cowl_entity_wrap_obj_prop(obj_prop))) return false;
    });

    cowl_ontology_foreach(CowlDataProp, data_prop, data_props, {
        if (!cowl_iterate(iter, cowl_entity_wrap_data_prop(data_prop))) return false;
    });

    cowl_ontology_foreach(CowlAnnotProp, annot_prop, annot_props, {
        if (!cowl_iterate(iter, cowl_entity_wrap_annot_prop(annot_prop))) return false;
    });

    cowl_ontology_foreach(CowlNamedInd, named_ind, named_inds, {
        if (!cowl_iterate(iter, cowl_entity_wrap_named_ind(named_ind))) return false;
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

bool cowl_ontology_iterate_axioms(CowlOntology *onto, CowlAxiomIterator *iter) {
    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        UHash(CowlAxiomSet) *axioms = onto->axioms_by_type[type];
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
    UHash(CowlAxiomSet) *axioms = onto->axioms_by_type[type];

    uhash_foreach_key(CowlAxiomSet, axioms, axiom, {
        if (!cowl_iterate(iter, axiom)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_of_type(import, type, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       CowlClsExpIterator *iter) {
    UHash(CowlClassAxiomMap) *map = cowl_ontology_get_class_refs(onto);
    Vector(CowlAxiomPtr) *axioms = uhmap_get(CowlClassAxiomMap, map, owl_class, NULL);

    vector_foreach(CowlAxiomPtr, axioms, axiom, {
        if (cowl_axiom_flags_get_type(axiom->flags) != COWL_AT_SUB_CLASS) continue;
        CowlSubClsAxiom *sub_axiom = (CowlSubClsAxiom *)axiom;

        if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->super_class)) {
            if (!cowl_iterate(iter, sub_axiom->sub_class)) return false;
        }
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_sub_classes(import, owl_class, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         CowlClsExpIterator *iter) {
    UHash(CowlClassAxiomMap) *map = cowl_ontology_get_class_refs(onto);
    Vector(CowlAxiomPtr) *axioms = uhmap_get(CowlClassAxiomMap, map, owl_class, NULL);

    vector_foreach(CowlAxiomPtr, axioms, axiom, {
        if (cowl_axiom_flags_get_type(axiom->flags) != COWL_AT_SUB_CLASS) continue;
        CowlSubClsAxiom *sub_axiom = (CowlSubClsAxiom *)axiom;

        if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->sub_class)) {
            if (!cowl_iterate(iter, sub_axiom->super_class)) return false;
        }
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_super_classes(import, owl_class, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      CowlClsExpIterator *iter) {
    UHash(CowlClassAxiomMap) *map = cowl_ontology_get_class_refs(onto);
    Vector(CowlAxiomPtr) *axioms = uhmap_get(CowlClassAxiomMap, map, owl_class, NULL);

    vector_foreach(CowlAxiomPtr, axioms, axiom, {
        if (cowl_axiom_flags_get_type(axiom->flags) != COWL_AT_EQUIV_CLASSES) continue;
        CowlClsExpSet *eq_classes = ((CowlNAryClsAxiom *)axiom)->classes;

        uhash_uint_t cls_idx = uhash_get(CowlClsExpSet, eq_classes, (CowlClsExp *)owl_class);
        if (cls_idx < uhash_end(eq_classes)) {
            for (uhash_uint_t i = uhash_begin(eq_classes); i != uhash_end(eq_classes); ++i) {
                if (i != cls_idx && !cowl_iterate(iter, uhash_key(eq_classes, i))) return false;
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
    Vector(CowlAxiomPtr) *axioms;

    if (ind->is_named) {
        UHash(CowlNamedIndAxiomMap) *map = cowl_ontology_get_named_ind_refs(onto);
        axioms = uhmap_get(CowlNamedIndAxiomMap, map, (CowlNamedInd *)ind, NULL);
    } else {
        UHash(CowlAnonIndAxiomMap) *map = cowl_ontology_get_anon_ind_refs(onto);
        axioms = uhmap_get(CowlAnonIndAxiomMap, map, (CowlAnonInd *)ind, NULL);
    }

    vector_foreach(CowlAxiomPtr, axioms, axiom, {
        if (cowl_axiom_flags_get_type(axiom->flags) != COWL_AT_CLASS_ASSERT) continue;
        CowlClsAssertAxiom *assert_axiom = (CowlClsAssertAxiom *)axiom;
        if (!cowl_iterate(iter, assert_axiom->cls_exp)) return false;
    });

    vector_foreach(CowlOntologyPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_types(import, ind, iter)) return false;
    });

    return true;
}

// Private API

CowlOntology* cowl_ontology_get(void) {
    return cowl_ontology_alloc();
}

CowlOntology* cowl_ontology_alloc(void) {
    CowlOntology *onto = cowl_alloc(onto);
    if (onto) *onto = COWL_ONTOLOGY_INIT;
    return onto;
}

void cowl_ontology_free(CowlOntology *onto) {
    if (!onto) return;

    cowl_ontology_id_free(onto->id);
    cowl_ontology_vec_free(onto->imports);
    cowl_annotation_vec_free(onto->annotations);

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; type++) {
        cowl_axiom_set_free(onto->axioms_by_type[type]);
    }

    uhash_foreach_value(CowlAnnotPropAxiomMap, onto->annot_prop_refs, vec,
                        vector_free(CowlAxiomPtr, vec));
    uhash_foreach_value(CowlClassAxiomMap, onto->class_refs, vec,
                        vector_free(CowlAxiomPtr, vec));
    uhash_foreach_value(CowlDataPropAxiomMap, onto->data_prop_refs, vec,
                        vector_free(CowlAxiomPtr, vec));
    uhash_foreach_value(CowlDatatypeAxiomMap, onto->datatype_refs, vec,
                        vector_free(CowlAxiomPtr, vec));
    uhash_foreach_value(CowlObjPropAxiomMap, onto->obj_prop_refs, vec,
                        vector_free(CowlAxiomPtr, vec));
    uhash_foreach_value(CowlNamedIndAxiomMap, onto->named_ind_refs, vec,
                        vector_free(CowlAxiomPtr, vec));
    uhash_foreach_value(CowlAnonIndAxiomMap, onto->anon_ind_refs, vec,
                        vector_free(CowlAxiomPtr, vec));

    uhash_free(CowlAnnotPropAxiomMap, onto->annot_prop_refs);
    uhash_free(CowlClassAxiomMap, onto->class_refs);
    uhash_free(CowlDataPropAxiomMap, onto->data_prop_refs);
    uhash_free(CowlDatatypeAxiomMap, onto->datatype_refs);
    uhash_free(CowlObjPropAxiomMap, onto->obj_prop_refs);
    uhash_free(CowlNamedIndAxiomMap, onto->named_ind_refs);
    uhash_free(CowlAnonIndAxiomMap, onto->anon_ind_refs);

    cowl_free(onto);
}

void cowl_ontology_anon_ind_refs_init(CowlOntology *onto) {
    if (onto->anon_ind_refs) return;

    onto->anon_ind_refs = uhmap_alloc(CowlAnonIndAxiomMap);
    CowlAxiomIterator a_iter = cowl_iterator_init(onto, cowl_ontology_lazy_anon_ind_init);
    cowl_ontology_iterate_axioms(onto, &a_iter);

    if (onto->annotations) {
        CowlAxiomCtx c = { .onto = onto };
        CowlAnonIndIterator i_iter = cowl_iterator_init(&c, cowl_ontology_anon_ind_adder);
        cowl_annotation_vec_iterate_anon_inds(onto->annotations, &i_iter);
    }
}

UHash(CowlAnonIndAxiomMap)* cowl_ontology_get_anon_ind_refs(CowlOntology *onto) {
    if (!onto->anon_ind_refs) cowl_ontology_anon_ind_refs_init(onto);
    return onto->anon_ind_refs;
}

void cowl_ontology_set_id(CowlOntology *onto, CowlOntologyID *id) {
    onto->id = id;
}

void cowl_ontology_set_annot(CowlOntology *onto, Vector(CowlAnnotationPtr) *annot) {
    onto->annotations = annot;

    CowlAxiomCtx c = { .onto = onto };
    CowlEntityIterator iter = cowl_iterator_init(&c, cowl_ontology_entity_adder);
    cowl_annotation_vec_iterate_signature(annot, &iter);
}

void cowl_ontology_set_imports(CowlOntology *onto, Vector(CowlOntologyPtr) *imports) {
    onto->imports = imports;
}

void cowl_ontology_add_axiom(CowlOntology *onto, CowlAxiom *axiom) {
    CowlAxiomType type = cowl_axiom_flags_get_type(axiom->flags);
    UHash(CowlAxiomSet) *axioms = onto->axioms_by_type[type];

    if (!axioms) {
        axioms = uhset_alloc(CowlAxiomSet);
        onto->axioms_by_type[type] = axioms;
    }

    uhash_ret_t ret = uhset_insert(CowlAxiomSet, axioms, axiom);
    if (ret != UHASH_INSERTED) return;

    cowl_axiom_retain(axiom);
    CowlAxiomCtx c = { .onto = onto, .axiom = axiom };
    CowlEntityIterator iter = cowl_iterator_init(&c, cowl_ontology_entity_adder);
    cowl_axiom_iterate_signature(axiom, &iter);
}

void cowl_ontology_add_axiom_for_entity(CowlOntology *onto, CowlAxiom *axiom, CowlEntity entity) {
    switch (entity.type) {

        case COWL_ET_CLASS:
            cowl_add_axiom_to_vec_in_map(CowlClassAxiomMap, onto->class_refs,
                                         entity.owl_class, axiom);
            break;

        case COWL_ET_DATA_PROP:
            cowl_add_axiom_to_vec_in_map(CowlDataPropAxiomMap, onto->data_prop_refs,
                                         entity.data_prop, axiom);
            break;

        case COWL_ET_DATATYPE:
            cowl_add_axiom_to_vec_in_map(CowlDatatypeAxiomMap, onto->datatype_refs,
                                         entity.datatype, axiom);
            break;

        case COWL_ET_OBJ_PROP:
            cowl_add_axiom_to_vec_in_map(CowlObjPropAxiomMap, onto->obj_prop_refs,
                                         entity.obj_prop, axiom);
            break;

        case COWL_ET_ANNOT_PROP:
            cowl_add_axiom_to_vec_in_map(CowlAnnotPropAxiomMap, onto->annot_prop_refs,
                                         entity.annot_prop, axiom);
            break;

        case COWL_ET_NAMED_IND:
            cowl_add_axiom_to_vec_in_map(CowlNamedIndAxiomMap, onto->named_ind_refs,
                                         entity.named_ind, axiom);
            break;

        default:
            break;
    }
}

void cowl_ontology_add_axiom_for_anon_ind(CowlOntology *onto, CowlAxiom *axiom, CowlAnonInd *ind) {
    cowl_add_axiom_to_vec_in_map(CowlAnonIndAxiomMap, onto->anon_ind_refs, ind, axiom);
}

// Iterator functions

bool cowl_ontology_entity_adder(void *ctx, CowlEntity entity) {
    CowlAxiomCtx *axiom_ctx = (CowlAxiomCtx *)ctx;
    cowl_ontology_add_axiom_for_entity(axiom_ctx->onto, axiom_ctx->axiom, entity);
    return true;
}

bool cowl_ontology_anon_ind_adder(void *ctx, CowlAnonInd *ind) {
    CowlAxiomCtx *axiom_ctx = (CowlAxiomCtx *)ctx;
    cowl_ontology_add_axiom_for_anon_ind(axiom_ctx->onto, axiom_ctx->axiom, ind);
    return true;
}

bool cowl_ontology_lazy_anon_ind_init(void *ctx, CowlAxiom *axiom) {
    CowlAxiomCtx c = { .onto = ctx, .axiom = axiom };
    CowlAnonIndIterator iter = cowl_iterator_init(&c, cowl_ontology_anon_ind_adder);
    cowl_axiom_iterate_anon_inds(axiom, &iter);
    return true;
}
