/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ontology_private.h"
#include "cowl_private.h"

typedef struct CowlAxiomCtx {
    cowl_ret ret;
    CowlOntology *onto;
    CowlAxiom *axiom;
} CowlAxiomCtx;

// Private prototypes

static CowlOntology* cowl_ontology_alloc(void);
static void cowl_ontology_free(CowlOntology *onto);
static cowl_ret cowl_ontology_add_primitive(CowlOntology *onto, CowlObject *obj);
static cowl_ret cowl_ontology_add_axiom_for_primitive(CowlOntology *onto, CowlAxiom *axiom,
                                                      CowlObject *obj);
static bool cowl_ontology_primitive_axiom_adder(void *ctx, void *obj);
static bool cowl_ontology_primitive_adder(void *ctx, void *obj);

// Public API

CowlOntology* cowl_ontology_retain(CowlOntology *onto) {
    return cowl_object_incr_ref(onto);
}

void cowl_ontology_release(CowlOntology *onto) {
    if (onto && !cowl_object_decr_ref(onto)) {
        cowl_ontology_free(onto);
    }
}

CowlOntologyId cowl_ontology_get_id(CowlOntology *onto) {
    return onto->id;
}

CowlObjectVec* cowl_ontology_get_annot(CowlOntology *onto) {
    return onto->annotations;
}

CowlString* cowl_ontology_to_string(CowlOntology *onto)
    COWL_TO_STRING_IMPL(ontology, onto)

bool cowl_ontology_equals(CowlOntology *lhs, CowlOntology *rhs) {
    if (lhs == rhs) return true;

    // If the ontology IRIs are both NULL, then both ontologies are anonymous.
    // If they were equal, they would have passed the pointer equality check.
    if (!(lhs->id.ontology_iri || rhs->id.ontology_iri)) return false;

    return cowl_ontology_id_equals(lhs->id, rhs->id);
}

ulib_uint cowl_ontology_hash(CowlOntology *onto) {
    return cowl_hash_1(COWL_HASH_INIT_ONTO, cowl_ontology_id_hash(onto->id));
}

ulib_uint cowl_ontology_axiom_count(CowlOntology *onto) {
    ulib_uint count = 0;

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        count += uhash_count(onto->axioms_by_type[type]);
    }

    uvec_foreach(CowlObjectPtr, onto->imports, import, {
        count += cowl_ontology_axiom_count(import);
    });

    return count;
}

ulib_uint cowl_ontology_imports_count(CowlOntology *onto) {
    ulib_uint count = uvec_count(onto->imports);

    uvec_foreach(CowlObjectPtr, onto->imports, import, {
        count += cowl_ontology_imports_count(import);
    });

    return count;
}

ulib_uint cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type) {
    ulib_uint count = uhash_count(onto->axioms_by_type[type]);

    uvec_foreach(CowlObjectPtr, onto->imports, import, {
        count += cowl_ontology_axiom_count_for_type(import, type);
    });

    return count;
}

static cowl_ret cowl_ontology_add_axiom_to_map(CowlObject *entity, CowlAxiom *axiom,
                                               UHash(CowlObjectTable) *map) {

    ulib_uint idx;
    uhash_ret ret = uhash_put(CowlObjectTable, map, entity, &idx);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    UVec(CowlObjectPtr) *vec = uhash_value(map, idx);

    if (ret == UHASH_INSERTED || !vec) {
        vec = uvec_alloc(CowlObjectPtr);
        uhash_value(map, idx) = vec;
    }

    if (uvec_push(CowlObjectPtr, vec, axiom)) {
        return COWL_ERR_MEM;
    }

    return COWL_OK;
}

static cowl_ret cowl_ontology_add_primitive_to_map(CowlObject *entity,
                                                   UHash(CowlObjectTable) *map) {
    ulib_uint idx;
    uhash_ret ret = uhash_put(CowlObjectTable, map, entity, &idx);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    if (ret == UHASH_INSERTED) {
        uhash_value(map, idx) = NULL;
    }

    return COWL_OK;
}

#define COWL_ONTOLOGY_ENTITY_QUERY_IMPL(T, SINGULAR, PLURAL)                                        \
                                                                                                    \
ulib_uint cowl_ontology_##PLURAL##_count(CowlOntology *onto) {                                      \
    return (ulib_uint)uhash_count(onto->SINGULAR##_refs);                                           \
}                                                                                                   \
                                                                                                    \
bool cowl_ontology_iterate_##PLURAL(CowlOntology *onto, CowlIterator *iter) {                       \
    uhash_foreach_key(CowlObjectTable, onto->SINGULAR##_refs, SINGULAR, {                           \
        if (!cowl_iterate(iter, SINGULAR)) return false;                                            \
    });                                                                                             \
    return true;                                                                                    \
}                                                                                                   \
                                                                                                    \
ulib_uint cowl_ontology_axiom_count_for_##SINGULAR(CowlOntology *onto, T *entity) {                 \
    UHash(CowlObjectTable) *map = onto->SINGULAR##_refs;                                            \
    UVec(CowlObjectPtr) *axioms = uhmap_get(CowlObjectTable, map, entity, NULL);                    \
    ulib_uint count = uvec_count(axioms);                                                           \
                                                                                                    \
    uvec_foreach(CowlObjectPtr, onto->imports, import, {                                            \
        count += cowl_ontology_axiom_count_for_##SINGULAR(import, entity);                          \
    });                                                                                             \
                                                                                                    \
    return count;                                                                                   \
}                                                                                                   \
                                                                                                    \
bool cowl_ontology_iterate_axioms_for_##SINGULAR(CowlOntology *onto, T *entity,                     \
                                                 CowlIterator *iter) {                              \
    UHash(CowlObjectTable) *map = onto->SINGULAR##_refs;                                            \
    UVec(CowlObjectPtr) *axioms = uhmap_get(CowlObjectTable, map, entity, NULL);                    \
                                                                                                    \
    uvec_foreach(CowlObjectPtr, axioms, axiom, {                                                    \
        if (!cowl_iterate(iter, axiom)) return false;                                               \
    });                                                                                             \
                                                                                                    \
    uvec_foreach(CowlObjectPtr, onto->imports, import, {                                            \
        if (!cowl_ontology_iterate_axioms_for_##SINGULAR(import, entity, iter)) {                   \
            return false;                                                                           \
        }                                                                                           \
    });                                                                                             \
                                                                                                    \
    return true;                                                                                    \
}

COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlClass, class, classes)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlDatatype, datatype, datatypes)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlObjProp, obj_prop, obj_props)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlDataProp, data_prop, data_props)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlAnnotProp, annot_prop, annot_props)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlNamedInd, named_ind, named_inds)
COWL_ONTOLOGY_ENTITY_QUERY_IMPL(CowlAnonInd, anon_ind, anon_inds)

bool cowl_ontology_has_entity(CowlOntology *onto, CowlEntity *entity) {
    UHash(CowlObjectTable) *table = NULL;

    switch (cowl_entity_get_type(entity)) {
        case COWL_ET_CLASS: table = onto->class_refs; break;
        case COWL_ET_DATATYPE: table = onto->datatype_refs; break;
        case COWL_ET_NAMED_IND: table = onto->named_ind_refs; break;
        case COWL_ET_OBJ_PROP: table = onto->obj_prop_refs; break;
        case COWL_ET_DATA_PROP: table = onto->data_prop_refs; break;
        case COWL_ET_ANNOT_PROP: table = onto->annot_prop_refs; break;
        default: break;
    }

    return table && uhash_contains(CowlObjectTable, table, entity);
}

bool cowl_ontology_iterate_primitives(CowlOntology *onto, CowlPrimitiveFlags flags,
                                      CowlIterator *iter) {
    if (uflags_is_set(COWL_PF, flags, COWL_PF_CLASS)) {
        uhash_foreach_key(CowlObjectTable, onto->class_refs, cls, {
            if (!cowl_class_iterate_primitives(cls, flags, iter)) return false;
        });
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_DATATYPE)) {
        uhash_foreach_key(CowlObjectTable, onto->datatype_refs, dt, {
            if (!cowl_datatype_iterate_primitives(dt, flags, iter)) return false;
        });
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_OBJ_PROP)) {
        uhash_foreach_key(CowlObjectTable, onto->obj_prop_refs, prop, {
            if (!cowl_obj_prop_iterate_primitives(prop, flags, iter)) return false;
        });
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_DATA_PROP)) {
        uhash_foreach_key(CowlObjectTable, onto->data_prop_refs, prop, {
            if (!cowl_data_prop_iterate_primitives(prop, flags, iter)) return false;
        });
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_ANNOT_PROP)) {
        uhash_foreach_key(CowlObjectTable, onto->annot_prop_refs, prop, {
            if (!cowl_annot_prop_iterate_primitives(prop, flags, iter)) return false;
        });
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_NAMED_IND)) {
        uhash_foreach_key(CowlObjectTable, onto->named_ind_refs, ind, {
            if (!cowl_named_ind_iterate_primitives(ind, flags, iter)) return false;
        });
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_ANON_IND)) {
        uhash_foreach_key(CowlObjectTable, onto->anon_ind_refs, ind, {
            if (!cowl_anon_ind_iterate_primitives(ind, flags, iter)) return false;
        });
    }

    return true;
}

bool cowl_ontology_iterate_imports(CowlOntology *onto, CowlIterator *iter) {
    uvec_foreach(CowlObjectPtr, onto->imports, import, {
        if (!cowl_iterate(iter, import)) return false;
    });

    uvec_foreach(CowlObjectPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_imports(import, iter)) return false;
    });

    return true;
}

bool cowl_ontology_iterate_axioms(CowlOntology *onto, CowlIterator *iter) {
    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        UHash(CowlObjectTable) *axioms = onto->axioms_by_type[type];
        uhash_foreach_key(CowlObjectTable, axioms, axiom, {
            if (!cowl_iterate(iter, axiom)) return false;
        });
    }

    uvec_foreach(CowlObjectPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms(import, iter)) {
            return false;
        }
    });

    return true;
}

bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          CowlIterator *iter) {
    UHash(CowlObjectTable) *axioms = onto->axioms_by_type[type];

    uhash_foreach_key(CowlObjectTable, axioms, axiom, {
        if (!cowl_iterate(iter, axiom)) return false;
    });

    uvec_foreach(CowlObjectPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_axioms_of_type(import, type, iter)) {
            return false;
        }
    });

    return true;
}

bool cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       CowlIterator *iter) {
    UHash(CowlObjectTable) *map = onto->class_refs;
    UVec(CowlObjectPtr) *axioms = uhmap_get(CowlObjectTable, map, owl_class, NULL);

    uvec_foreach(CowlObjectPtr, axioms, axiom, {
        if (cowl_axiom_get_type(axiom) != COWL_AT_SUB_CLASS) continue;
        CowlSubClsAxiom *sub_axiom = axiom;

        if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->super_class)) {
            if (!cowl_iterate(iter, sub_axiom->sub_class)) return false;
        }
    });

    uvec_foreach(CowlObjectPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_sub_classes(import, owl_class, iter)) {
            return false;
        }
    });

    return true;
}

bool cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         CowlIterator *iter) {
    UHash(CowlObjectTable) *map = onto->class_refs;
    UVec(CowlObjectPtr) *axioms = uhmap_get(CowlObjectTable, map, owl_class, NULL);

    uvec_foreach(CowlObjectPtr, axioms, axiom, {
        if (cowl_axiom_get_type(axiom) != COWL_AT_SUB_CLASS) continue;
        CowlSubClsAxiom *sub_axiom = axiom;

        if (cowl_cls_exp_equals((CowlClsExp *)owl_class, sub_axiom->sub_class)) {
            if (!cowl_iterate(iter, sub_axiom->super_class)) return false;
        }
    });

    uvec_foreach(CowlObjectPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_super_classes(import, owl_class, iter)) {
            return false;
        }
    });

    return true;
}

bool cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      CowlIterator *iter) {
    UHash(CowlObjectTable) *map = onto->class_refs;
    UVec(CowlObjectPtr) *axioms = uhmap_get(CowlObjectTable, map, owl_class, NULL);

    uvec_foreach(CowlObjectPtr, axioms, axiom, {
        if (cowl_axiom_get_type(axiom) != COWL_AT_EQUIV_CLASSES) continue;
        CowlObjectTable *eq_classes = ((CowlNAryClsAxiom *)axiom)->classes;

        if (uhash_contains(CowlObjectTable, eq_classes, owl_class)) {
            uhash_foreach_key(CowlObjectTable, eq_classes, cls_exp, {
                if (cls_exp != owl_class && !cowl_iterate(iter, cls_exp)) return false;
            });
        }
    });

    uvec_foreach(CowlObjectPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_eq_classes(import, owl_class, iter)) {
            return false;
        }
    });

    return true;
}

bool cowl_ontology_iterate_types(CowlOntology *onto, CowlIndividual *ind, CowlIterator *iter) {
    UVec(CowlObjectPtr) *axioms;

    if (cowl_individual_is_named(ind)) {
        UHash(CowlObjectTable) *map = onto->named_ind_refs;
        axioms = uhmap_get(CowlObjectTable, map, ind, NULL);
    } else {
        UHash(CowlObjectTable) *map = onto->anon_ind_refs;
        axioms = uhmap_get(CowlObjectTable, map, ind, NULL);
    }

    uvec_foreach(CowlObjectPtr, axioms, axiom, {
        if (cowl_axiom_get_type(axiom) != COWL_AT_CLASS_ASSERT) continue;
        CowlClsAssertAxiom *assert_axiom = axiom;
        if (!cowl_iterate(iter, assert_axiom->cls_exp)) return false;
    });

    uvec_foreach(CowlObjectPtr, onto->imports, import, {
        if (!cowl_ontology_iterate_types(import, ind, iter)) return false;
    });

    return true;
}

// Private API

CowlOntology* cowl_ontology_get(void) {
    return cowl_ontology_alloc();
}

CowlOntology* cowl_ontology_alloc(void) {
    CowlOntology *onto = ulib_alloc(onto);
    if (onto) *onto = COWL_ONTOLOGY_INIT;
    return onto;
}

void cowl_ontology_free(CowlOntology *onto) {
    cowl_iri_release(onto->id.ontology_iri);
    cowl_iri_release(onto->id.version_iri);
    cowl_object_vec_free_spec(ontology, onto->imports);
    cowl_object_vec_free_spec(annotation, onto->annotations);

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; type++) {
        cowl_object_set_free(onto->axioms_by_type[type]);
    }

    uhash_foreach_value(CowlObjectTable, onto->annot_prop_refs, vec, uvec_free(CowlObjectPtr, vec));
    uhash_foreach_value(CowlObjectTable, onto->class_refs, vec, uvec_free(CowlObjectPtr, vec));
    uhash_foreach_value(CowlObjectTable, onto->data_prop_refs, vec, uvec_free(CowlObjectPtr, vec));
    uhash_foreach_value(CowlObjectTable, onto->datatype_refs, vec, uvec_free(CowlObjectPtr, vec));
    uhash_foreach_value(CowlObjectTable, onto->obj_prop_refs, vec, uvec_free(CowlObjectPtr, vec));
    uhash_foreach_value(CowlObjectTable, onto->named_ind_refs, vec, uvec_free(CowlObjectPtr, vec));
    uhash_foreach_value(CowlObjectTable, onto->anon_ind_refs, vec, uvec_free(CowlObjectPtr, vec));

    uhash_free(CowlObjectTable, onto->annot_prop_refs);
    uhash_free(CowlObjectTable, onto->class_refs);
    uhash_free(CowlObjectTable, onto->data_prop_refs);
    uhash_free(CowlObjectTable, onto->datatype_refs);
    uhash_free(CowlObjectTable, onto->obj_prop_refs);
    uhash_free(CowlObjectTable, onto->named_ind_refs);
    uhash_free(CowlObjectTable, onto->anon_ind_refs);

    ulib_free(onto);
}

void cowl_ontology_set_iri(CowlOntology *onto, CowlIRI *iri) {
    cowl_iri_release(onto->id.ontology_iri);
    onto->id.ontology_iri = cowl_iri_retain(iri);
}

void cowl_ontology_set_version(CowlOntology *onto, CowlIRI *version) {
    cowl_iri_release(onto->id.version_iri);
    onto->id.version_iri = cowl_iri_retain(version);
}

cowl_ret cowl_ontology_add_annot(CowlOntology *onto, CowlAnnotation *annot) {
    if (!onto->annotations) {
        onto->annotations = uvec_alloc(CowlObjectPtr);
        if (!onto->annotations) return COWL_ERR_MEM;
    }

    if (uvec_push(CowlObjectPtr, onto->annotations, annot) != UVEC_OK) return COWL_ERR_MEM;
    cowl_annotation_retain(annot);

    CowlAxiomCtx ctx = { .onto = onto };
    CowlIterator iter = cowl_iterator_init(&ctx, cowl_ontology_primitive_adder);
    cowl_annotation_iterate_primitives(annot, COWL_PF_ALL, &iter);
    return ctx.ret;
}

cowl_ret cowl_ontology_add_import(CowlOntology *onto, CowlOntology *import) {
    if (!onto->imports) {
        onto->imports = uvec_alloc(CowlObjectPtr);
        if (!onto->imports) return COWL_ERR_MEM;
    }

    if (uvec_push(CowlObjectPtr, onto->imports, import) != UVEC_OK) return COWL_ERR_MEM;
    cowl_ontology_retain(import);

    CowlAxiomCtx ctx = { .onto = onto };
    CowlIterator iter = cowl_iterator_init(&ctx, cowl_ontology_primitive_adder);
    cowl_ontology_iterate_primitives(import, COWL_PF_ALL, &iter);
    return ctx.ret;
}

cowl_ret cowl_ontology_add_primitive(CowlOntology *onto, CowlObject *obj) {
    switch (cowl_object_get_type(obj)) {
        case COWL_OT_CE_CLASS: return cowl_ontology_add_primitive_to_map(obj, onto->class_refs);
        case COWL_OT_DPE_DATA_PROP: return cowl_ontology_add_primitive_to_map(obj, onto->data_prop_refs);
        case COWL_OT_DR_DATATYPE: return cowl_ontology_add_primitive_to_map(obj, onto->datatype_refs);
        case COWL_OT_OPE_OBJ_PROP: return cowl_ontology_add_primitive_to_map(obj, onto->obj_prop_refs);
        case COWL_OT_ANNOT_PROP: return cowl_ontology_add_primitive_to_map(obj, onto->annot_prop_refs);
        case COWL_OT_I_NAMED: return cowl_ontology_add_primitive_to_map(obj, onto->named_ind_refs);
        case COWL_OT_I_ANONYMOUS: return cowl_ontology_add_primitive_to_map(obj, onto->anon_ind_refs);
        default: return COWL_ERR;
    }
}

cowl_ret cowl_ontology_add_axiom(CowlOntology *onto, CowlAxiom *axiom) {
    CowlAxiomType type = cowl_axiom_get_type(axiom);
    UHash(CowlObjectTable) *axioms = onto->axioms_by_type[type];

    if (!axioms) {
        axioms = cowl_axiom_set_alloc();
        if (!axioms) return COWL_ERR_MEM;
        onto->axioms_by_type[type] = axioms;
    }

    uhash_ret ret = uhset_insert(CowlObjectTable, axioms, axiom);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;
    if (ret == UHASH_PRESENT) return COWL_OK;

    cowl_axiom_retain(axiom);
    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = cowl_iterator_init(&ctx, cowl_ontology_primitive_axiom_adder);
    if (!cowl_axiom_iterate_primitives(axiom, COWL_PF_ALL, &iter) && ctx.ret) return COWL_ERR_MEM;

    return COWL_OK;
}

cowl_ret cowl_ontology_add_axiom_for_primitive(CowlOntology *onto, CowlAxiom *axiom,
                                               CowlObject *obj) {
    switch (cowl_object_get_type(obj)) {

        case COWL_OT_CE_CLASS:
            return cowl_ontology_add_axiom_to_map(obj, axiom, onto->class_refs);

        case COWL_OT_DPE_DATA_PROP:
            return cowl_ontology_add_axiom_to_map(obj, axiom, onto->data_prop_refs);

        case COWL_OT_DR_DATATYPE:
            return cowl_ontology_add_axiom_to_map(obj, axiom, onto->datatype_refs);

        case COWL_OT_OPE_OBJ_PROP:
            return cowl_ontology_add_axiom_to_map(obj, axiom, onto->obj_prop_refs);

        case COWL_OT_ANNOT_PROP:
            return cowl_ontology_add_axiom_to_map(obj, axiom, onto->annot_prop_refs);

        case COWL_OT_I_NAMED:
            return cowl_ontology_add_axiom_to_map(obj, axiom, onto->named_ind_refs);

        case COWL_OT_I_ANONYMOUS:
            return cowl_ontology_add_axiom_to_map(obj, axiom, onto->anon_ind_refs);

        default:
            return COWL_ERR;
    }
}

// Iterator functions

bool cowl_ontology_primitive_axiom_adder(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    cowl_ret ret = cowl_ontology_add_axiom_for_primitive(axiom_ctx->onto, axiom_ctx->axiom, obj);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}

bool cowl_ontology_primitive_adder(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    cowl_ret ret = cowl_ontology_add_primitive(axiom_ctx->onto, obj);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}
