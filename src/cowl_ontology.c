/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
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

static inline cowl_ret cowl_vector_ptr_add(CowlVector **vec, void *obj) {
    if (!(*vec || (*vec = cowl_vector_ordered_empty_get()))) return COWL_ERR_MEM;
    return cowl_vector_add(*vec, obj) ? COWL_ERR_MEM : COWL_OK;
}

void cowl_ontology_release(CowlOntology *onto) {
    if (!onto || cowl_object_decr_ref(onto)) return;

    cowl_iri_release(onto->id.ontology_iri);
    cowl_iri_release(onto->id.version_iri);

    cowl_vector_release(onto->annotations);
    cowl_vector_release(onto->imports);

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; type++) {
        cowl_vector_release(onto->axioms_by_type[type]);
    }

    UHash(CowlObjectTable) *tables[] = {
        &onto->annot_prop_refs, &onto->class_refs, &onto->data_prop_refs,
        &onto->datatype_refs, &onto->obj_prop_refs, &onto->named_ind_refs,
        &onto->anon_ind_refs
    };

    for (ulib_uint i = 0; i < ulib_array_count(tables); ++i) {
        uhash_foreach(CowlObjectTable, tables[i], vec) {
            cowl_vector_release_ex(*vec.val, false);
        }
        uhash_deinit(CowlObjectTable, tables[i]);
    }

    ulib_free(onto);
}

CowlOntologyId cowl_ontology_get_id(CowlOntology *onto) {
    return onto->id;
}

CowlVector* cowl_ontology_get_annot(CowlOntology *onto) {
    return onto->annotations;
}

bool cowl_ontology_equals(CowlOntology *lhs, CowlOntology *rhs) {
    if (lhs == rhs) return true;

    // If the ontology IRIs are both NULL, then both ontologies are anonymous.
    // If they were equal, they would have passed the pointer equality check.
    if (!(lhs->id.ontology_iri || rhs->id.ontology_iri)) return false;

    return cowl_ontology_id_equals(lhs->id, rhs->id);
}

ulib_uint cowl_ontology_hash(CowlOntology *onto) {
    return cowl_ontology_id_hash(onto->id);
}

ulib_uint cowl_ontology_axiom_count(CowlOntology *onto) {
    ulib_uint count = 0;

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        count += cowl_vector_count(onto->axioms_by_type[type]);
    }

    cowl_vector_foreach(onto->imports, import) {
        count += cowl_ontology_axiom_count(*import.item);
    }

    return count;
}

ulib_uint cowl_ontology_imports_count(CowlOntology *onto) {
    ulib_uint count = cowl_vector_count(onto->imports);

    cowl_vector_foreach(onto->imports, import) {
        count += cowl_ontology_imports_count(*import.item);
    }

    return count;
}

ulib_uint cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type) {
    ulib_uint count = cowl_vector_count(onto->axioms_by_type[type]);

    cowl_vector_foreach(onto->imports, import) {
        count += cowl_ontology_axiom_count_for_type(*import.item, type);
    }

    return count;
}

#define COWL_ONTOLOGY_ENTITY_QUERY_IMPL(T, SINGULAR, PLURAL)                                        \
                                                                                                    \
ulib_uint cowl_ontology_##PLURAL##_count(CowlOntology *onto) {                                      \
    return uhash_count(CowlObjectTable, &onto->SINGULAR##_refs);                                    \
}                                                                                                   \
                                                                                                    \
bool cowl_ontology_iterate_##PLURAL(CowlOntology *onto, CowlIterator *iter) {                       \
    uhash_foreach(CowlObjectTable, &onto->SINGULAR##_refs, SINGULAR) {                              \
        if (!cowl_iterate(iter, *(SINGULAR).key)) return false;                                     \
    }                                                                                               \
    return true;                                                                                    \
}                                                                                                   \
                                                                                                    \
ulib_uint cowl_ontology_axiom_count_for_##SINGULAR(CowlOntology *onto, T *entity) {                 \
    CowlVector *axioms = uhmap_get(CowlObjectTable, &onto->SINGULAR##_refs, entity, NULL);          \
    ulib_uint count = cowl_vector_count(axioms);                                                    \
                                                                                                    \
    cowl_vector_foreach(onto->imports, import) {                                                    \
        count += cowl_ontology_axiom_count_for_##SINGULAR(*import.item, entity);                    \
    }                                                                                               \
                                                                                                    \
    return count;                                                                                   \
}                                                                                                   \
                                                                                                    \
bool cowl_ontology_iterate_axioms_for_##SINGULAR(CowlOntology *onto, T *entity,                     \
                                                 CowlIterator *iter) {                              \
    CowlVector *axioms = uhmap_get(CowlObjectTable, &onto->SINGULAR##_refs, entity, NULL);          \
                                                                                                    \
    cowl_vector_foreach(axioms, axiom) {                                                            \
        if (!cowl_iterate(iter, *axiom.item)) return false;                                         \
    }                                                                                               \
                                                                                                    \
    cowl_vector_foreach(onto->imports, import) {                                                    \
        if (!cowl_ontology_iterate_axioms_for_##SINGULAR(*import.item, entity, iter)) {             \
            return false;                                                                           \
        }                                                                                           \
    }                                                                                               \
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
        case COWL_ET_CLASS: table = &onto->class_refs; break;
        case COWL_ET_DATATYPE: table = &onto->datatype_refs; break;
        case COWL_ET_NAMED_IND: table = &onto->named_ind_refs; break;
        case COWL_ET_OBJ_PROP: table = &onto->obj_prop_refs; break;
        case COWL_ET_DATA_PROP: table = &onto->data_prop_refs; break;
        case COWL_ET_ANNOT_PROP: table = &onto->annot_prop_refs; break;
        default: break;
    }

    return table && uhash_contains(CowlObjectTable, table, entity);
}

bool cowl_ontology_iterate_primitives(CowlOntology *onto, CowlPrimitiveFlags flags,
                                      CowlIterator *iter) {
    if (uflags_is_set(COWL_PF, flags, COWL_PF_CLASS)) {
        uhash_foreach(CowlObjectTable, &onto->class_refs, cls) {
            if (!cowl_class_iterate_primitives(*cls.key, flags, iter)) return false;
        }
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_DATATYPE)) {
        uhash_foreach(CowlObjectTable, &onto->datatype_refs, dt) {
            if (!cowl_datatype_iterate_primitives(*dt.key, flags, iter)) return false;
        }
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_OBJ_PROP)) {
        uhash_foreach(CowlObjectTable, &onto->obj_prop_refs, prop) {
            if (!cowl_obj_prop_iterate_primitives(*prop.key, flags, iter)) return false;
        }
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_DATA_PROP)) {
        uhash_foreach(CowlObjectTable, &onto->data_prop_refs, prop) {
            if (!cowl_data_prop_iterate_primitives(*prop.key, flags, iter)) return false;
        }
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_ANNOT_PROP)) {
        uhash_foreach(CowlObjectTable, &onto->annot_prop_refs, prop) {
            if (!cowl_annot_prop_iterate_primitives(*prop.key, flags, iter)) return false;
        }
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_NAMED_IND)) {
        uhash_foreach(CowlObjectTable, &onto->named_ind_refs, ind) {
            if (!cowl_named_ind_iterate_primitives(*ind.key, flags, iter)) return false;
        }
    }

    if (uflags_is_set(COWL_PF, flags, COWL_PF_ANON_IND)) {
        uhash_foreach(CowlObjectTable, &onto->anon_ind_refs, ind) {
            if (!cowl_anon_ind_iterate_primitives(*ind.key, flags, iter)) return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_imports(CowlOntology *onto, CowlIterator *iter) {
    cowl_vector_foreach(onto->imports, import) {
        if (!cowl_iterate(iter, *import.item)) return false;
    }

    cowl_vector_foreach(onto->imports, import) {
        if (!cowl_ontology_iterate_imports(*import.item, iter)) return false;
    }

    return true;
}

bool cowl_ontology_iterate_axioms(CowlOntology *onto, CowlIterator *iter) {
    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        cowl_vector_foreach(onto->axioms_by_type[type], axiom) {
            if (!cowl_iterate(iter, *axiom.item)) return false;
        }
    }

    cowl_vector_foreach(onto->imports, import) {
        if (!cowl_ontology_iterate_axioms(*import.item, iter)) {
            return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          CowlIterator *iter) {
    cowl_vector_foreach(onto->axioms_by_type[type], axiom) {
        if (!cowl_iterate(iter, *axiom.item)) return false;
    }

    cowl_vector_foreach(onto->imports, import) {
        if (!cowl_ontology_iterate_axioms_of_type(*import.item, type, iter)) {
            return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_sub_classes(CowlOntology *onto, CowlClass *owl_class,
                                       CowlIterator *iter) {
    CowlVector *axioms = uhmap_get(CowlObjectTable, &onto->class_refs, owl_class, NULL);

    cowl_vector_foreach(axioms, axiom) {
        if (cowl_axiom_get_type(*axiom.item) != COWL_AT_SUB_CLASS) continue;
        CowlSubClsAxiom *sub_axiom = *axiom.item;

        if (cowl_cls_exp_equals((CowlClsExp *)owl_class, cowl_sub_cls_axiom_get_super(sub_axiom))) {
            if (!cowl_iterate(iter, cowl_sub_cls_axiom_get_sub(sub_axiom))) return false;
        }
    }

    cowl_vector_foreach(onto->imports, import) {
        if (!cowl_ontology_iterate_sub_classes(*import.item, owl_class, iter)) {
            return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_super_classes(CowlOntology *onto, CowlClass *owl_class,
                                         CowlIterator *iter) {
    CowlVector *axioms = uhmap_get(CowlObjectTable, &onto->class_refs, owl_class, NULL);

    cowl_vector_foreach(axioms, axiom) {
        if (cowl_axiom_get_type(*axiom.item) != COWL_AT_SUB_CLASS) continue;
        CowlSubClsAxiom *sub_axiom = *axiom.item;

        if (cowl_cls_exp_equals((CowlClsExp *)owl_class, cowl_sub_cls_axiom_get_sub(sub_axiom))) {
            if (!cowl_iterate(iter, cowl_sub_cls_axiom_get_super(sub_axiom))) return false;
        }
    }

    cowl_vector_foreach(onto->imports, import) {
        if (!cowl_ontology_iterate_super_classes(*import.item, owl_class, iter)) {
            return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_eq_classes(CowlOntology *onto, CowlClass *owl_class,
                                      CowlIterator *iter) {
    CowlVector *axioms = uhmap_get(CowlObjectTable, &onto->class_refs, owl_class, NULL);

    cowl_vector_foreach(axioms, axiom) {
        if (cowl_axiom_get_type(*axiom.item) != COWL_AT_EQUIV_CLASSES) continue;
        CowlVector *eq_classes = cowl_nary_cls_axiom_get_classes((CowlNAryClsAxiom *)*axiom.item);

        if (uvec_contains(CowlObjectPtr, &eq_classes->data, owl_class)) {
            uvec_foreach(CowlObjectPtr, &eq_classes->data, ce) {
                void *cls_exp = *ce.item;
                if (cls_exp != owl_class && !cowl_iterate(iter, cls_exp)) return false;
            }
        }
    }

    cowl_vector_foreach(onto->imports, import) {
        if (!cowl_ontology_iterate_eq_classes(*import.item, owl_class, iter)) {
            return false;
        }
    }

    return true;
}

bool cowl_ontology_iterate_types(CowlOntology *onto, CowlIndividual *ind, CowlIterator *iter) {
    CowlVector *axioms;

    if (cowl_individual_is_named(ind)) {
        axioms = uhmap_get(CowlObjectTable, &onto->named_ind_refs, ind, NULL);
    } else {
        axioms = uhmap_get(CowlObjectTable, &onto->anon_ind_refs, ind, NULL);
    }

    cowl_vector_foreach(axioms, axiom) {
        if (cowl_axiom_get_type(*axiom.item) != COWL_AT_CLASS_ASSERT) continue;
        CowlClsAssertAxiom *assert_axiom = *axiom.item;
        if (!cowl_iterate(iter, cowl_cls_assert_axiom_get_cls_exp(assert_axiom))) return false;
    }

    cowl_vector_foreach(onto->imports, import) {
        if (!cowl_ontology_iterate_types(*import.item, ind, iter)) return false;
    }

    return true;
}

CowlOntology* cowl_ontology_get(void) {
    CowlOntology *onto = ulib_alloc(onto);
    if (!onto) return NULL;
    *onto = (CowlOntology) {
        .super = COWL_OBJECT_INIT(COWL_OT_ONTOLOGY),
        .annot_prop_refs = cowl_annot_prop_map_init(),
        .class_refs = cowl_class_map_init(),
        .data_prop_refs = cowl_data_prop_map_init(),
        .datatype_refs = cowl_datatype_map_init(),
        .obj_prop_refs = cowl_obj_prop_map_init(),
        .named_ind_refs = cowl_named_ind_map_init(),
        .anon_ind_refs = cowl_anon_ind_map_init()
    };
    return onto;
}

void cowl_ontology_set_iri(CowlOntology *onto, CowlIRI *iri) {
    cowl_iri_release(onto->id.ontology_iri);
    onto->id.ontology_iri = cowl_iri_retain(iri);
}

void cowl_ontology_set_version(CowlOntology *onto, CowlIRI *version) {
    cowl_iri_release(onto->id.version_iri);
    onto->id.version_iri = cowl_iri_retain(version);
}

static cowl_ret cowl_add_primitive_to_map(CowlObject *entity, UHash(CowlObjectTable) *map) {
    ulib_uint idx;
    uhash_ret ret = uhash_put(CowlObjectTable, map, entity, &idx);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    if (ret == UHASH_INSERTED) {
        uhash_value(CowlObjectTable, map, idx) = NULL;
    }

    return COWL_OK;
}

static cowl_ret cowl_ontology_add_primitive(CowlOntology *onto, CowlObject *obj) {
    switch (cowl_get_type(obj)) {
        case COWL_OT_CE_CLASS: return cowl_add_primitive_to_map(obj, &onto->class_refs);
        case COWL_OT_DPE_DATA_PROP: return cowl_add_primitive_to_map(obj, &onto->data_prop_refs);
        case COWL_OT_DR_DATATYPE: return cowl_add_primitive_to_map(obj, &onto->datatype_refs);
        case COWL_OT_OPE_OBJ_PROP: return cowl_add_primitive_to_map(obj, &onto->obj_prop_refs);
        case COWL_OT_ANNOT_PROP: return cowl_add_primitive_to_map(obj, &onto->annot_prop_refs);
        case COWL_OT_I_NAMED: return cowl_add_primitive_to_map(obj, &onto->named_ind_refs);
        case COWL_OT_I_ANONYMOUS: return cowl_add_primitive_to_map(obj, &onto->anon_ind_refs);
        default: return COWL_ERR;
    }
}

static bool cowl_ontology_primitive_adder(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    cowl_ret ret = cowl_ontology_add_primitive(axiom_ctx->onto, obj);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}

cowl_ret cowl_ontology_add_annot(CowlOntology *onto, CowlAnnotation *annot) {
    if (cowl_vector_ptr_add(&onto->annotations, annot)) return COWL_ERR_MEM;
    CowlAxiomCtx ctx = { .onto = onto };
    CowlIterator iter = cowl_iterator_init(&ctx, cowl_ontology_primitive_adder);
    cowl_annotation_iterate_primitives(annot, COWL_PF_ALL, &iter);
    return ctx.ret;
}

cowl_ret cowl_ontology_add_import(CowlOntology *onto, CowlOntology *import) {
    if (cowl_vector_ptr_add(&onto->imports, import)) return COWL_ERR_MEM;
    CowlAxiomCtx ctx = { .onto = onto };
    CowlIterator iter = cowl_iterator_init(&ctx, cowl_ontology_primitive_adder);
    cowl_ontology_iterate_primitives(import, COWL_PF_ALL, &iter);
    return ctx.ret;
}

static cowl_ret cowl_add_axiom_to_map(CowlObject *entity, CowlAxiom *axiom,
                                      UHash(CowlObjectTable) *map) {
    ulib_uint idx;
    uhash_ret ret = uhash_put(CowlObjectTable, map, entity, &idx);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    CowlVector *vec = uhash_value(CowlObjectTable, map, idx);

    if (ret == UHASH_INSERTED || !vec) {
        vec = cowl_vector_ordered_empty_get();
        uhash_value(CowlObjectTable, map, idx) = vec;
        if (!vec) return COWL_ERR_MEM;
    }

    if (cowl_vector_push(vec, axiom)) {
        return COWL_ERR_MEM;
    }

    return COWL_OK;
}

static cowl_ret cowl_ontology_add_axiom_for_primitive(CowlOntology *onto, CowlAxiom *axiom,
                                                      CowlObject *obj) {
    switch (cowl_get_type(obj)) {
        case COWL_OT_CE_CLASS: return cowl_add_axiom_to_map(obj, axiom, &onto->class_refs);
        case COWL_OT_DPE_DATA_PROP: return cowl_add_axiom_to_map(obj, axiom, &onto->data_prop_refs);
        case COWL_OT_DR_DATATYPE: return cowl_add_axiom_to_map(obj, axiom, &onto->datatype_refs);
        case COWL_OT_OPE_OBJ_PROP: return cowl_add_axiom_to_map(obj, axiom, &onto->obj_prop_refs);
        case COWL_OT_ANNOT_PROP: return cowl_add_axiom_to_map(obj, axiom, &onto->annot_prop_refs);
        case COWL_OT_I_NAMED: return cowl_add_axiom_to_map(obj, axiom, &onto->named_ind_refs);
        case COWL_OT_I_ANONYMOUS: return cowl_add_axiom_to_map(obj, axiom, &onto->anon_ind_refs);
        default: return COWL_ERR;
    }
}

static bool cowl_ontology_primitive_axiom_adder(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    cowl_ret ret = cowl_ontology_add_axiom_for_primitive(axiom_ctx->onto, axiom_ctx->axiom, obj);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}

cowl_ret cowl_ontology_add_axiom(CowlOntology *onto, CowlAxiom *axiom) {
    CowlAxiomType type = cowl_axiom_get_type(axiom);
    if (cowl_vector_ptr_add(&onto->axioms_by_type[type], axiom)) return COWL_ERR_MEM;

    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = cowl_iterator_init(&ctx, cowl_ontology_primitive_axiom_adder);
    if (!cowl_axiom_iterate_primitives(axiom, COWL_PF_ALL, &iter) && ctx.ret) return COWL_ERR_MEM;

    return COWL_OK;
}

cowl_ret cowl_ontology_finalize(CowlOntology *onto) {
    if (cowl_vector_shrink(onto->imports)) return COWL_ERR_MEM;
    if (cowl_vector_shrink(onto->annotations)) return COWL_ERR_MEM;

    for (CowlAxiomType i = COWL_AT_FIRST; i < COWL_AT_COUNT; ++i) {
        if (cowl_vector_shrink(onto->axioms_by_type[i])) return COWL_ERR_MEM;
    }

    UHash(CowlObjectTable) *tables[] = {
        &onto->annot_prop_refs, &onto->class_refs, &onto->data_prop_refs, &onto->datatype_refs,
        &onto->obj_prop_refs, &onto->named_ind_refs, &onto->anon_ind_refs
    };

    for (ulib_uint i = 0; i < ulib_array_count(tables); ++i) {
        uhash_foreach(CowlObjectTable, tables[i], item) {
            if (cowl_vector_shrink(*item.val)) return COWL_ERR_MEM;
        }
    }

    return COWL_OK;
}
