/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ontology_private.h"
#include "cowl_private.h"

#define cowl_ontology_foreach_import(ONTO, IMPORT, CODE)                                           \
    do {                                                                                           \
        cowl_table_foreach ((ONTO)->imports, p_##IMPORT##_var) {                                   \
            if (!*p_##IMPORT##_var.val) continue;                                                  \
            CowlOntology *IMPORT = *p_##IMPORT##_var.val;                                          \
            CODE;                                                                                  \
        }                                                                                          \
    } while (0)

CowlOntology *cowl_ontology(CowlManager *manager) {
    CowlOntology *onto = ulib_alloc(onto);
    if (!onto) return NULL;

    CowlSymTable *st = cowl_sym_table();
    if (!st || cowl_manager_add_ontology(manager, onto)) goto err;

    *onto = (CowlOntology){ 0 };
    onto->super = COWL_OBJECT_INIT(COWL_OT_ONTOLOGY);
    onto->st = st;
    onto->manager = cowl_retain(manager);

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        onto->refs[i] = cowl_primitive_map();
    }

    return onto;

err:
    cowl_release(st);
    ulib_free(onto);
    return NULL;
}

void cowl_ontology_free(CowlOntology *onto) {
    cowl_manager_remove_ontology(onto->manager, onto);
    cowl_release(onto->manager);
    cowl_release(onto->st);

    cowl_release(onto->id.iri);
    cowl_release(onto->id.version);

    cowl_release(onto->imports);
    cowl_release(onto->annot);

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; type++) {
        cowl_release(onto->axioms_by_type[type]);
    }

    for (ulib_uint i = 0; i < ulib_array_count(onto->refs); ++i) {
        uhash_foreach (CowlObjectTable, &onto->refs[i], vec) {
            cowl_vector_release_ex(*vec.val, false);
        }
        uhash_deinit(CowlObjectTable, &onto->refs[i]);
    }

    ulib_free(onto);
}

CowlManager *cowl_ontology_get_manager(CowlOntology *onto) {
    return onto->manager;
}

CowlSymTable *cowl_ontology_get_sym_table(CowlOntology *onto) {
    return onto->st;
}

CowlOntologyId cowl_ontology_get_id(CowlOntology *onto) {
    return onto->id;
}

CowlVector *cowl_ontology_get_annot(CowlOntology *onto) {
    return onto->annot ? onto->annot : (onto->annot = cowl_vector_ordered_empty());
}

bool cowl_ontology_equals(CowlOntology *lhs, CowlOntology *rhs) {
    if (lhs == rhs) return true;

    // If the ontology IRIs are both NULL, then both ontologies are anonymous.
    // If they were equal, they would have passed the pointer equality check.
    if (!(lhs->id.iri || rhs->id.iri)) return false;

    return cowl_ontology_id_equals(lhs->id, rhs->id);
}

ulib_uint cowl_ontology_hash(CowlOntology *onto) {
    return cowl_ontology_id_hash(onto->id);
}

ulib_uint cowl_ontology_axiom_count(CowlOntology *onto, bool imports) {
    ulib_uint count = 0;

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        count += cowl_vector_count(onto->axioms_by_type[type]);
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            count += cowl_ontology_axiom_count(import, true);
        });
    }

    return count;
}

ulib_uint cowl_ontology_imports_count(CowlOntology *onto, bool imports) {
    ulib_uint count = cowl_table_count(onto->imports);

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            count += cowl_ontology_imports_count(import, true);
        });
    }

    return count;
}

ulib_uint cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type, bool imports) {
    ulib_uint count = cowl_vector_count(onto->axioms_by_type[type]);

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            count += cowl_ontology_axiom_count_for_type(import, type, true);
        });
    }

    return count;
}

ulib_uint
cowl_ontology_axiom_count_for_types(CowlOntology *onto, CowlAxiomFlags types, bool imports) {
    ulib_uint count = 0;
    cowl_axiom_flags_foreach_type (types, type) {
        count += cowl_ontology_axiom_count_for_type(onto, type, imports);
    }
    return count;
}

ulib_uint cowl_ontology_axiom_count_for_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive,
                                                  bool imports) {
    CowlPrimitiveType type = cowl_primitive_get_type(primitive);
    UHash(CowlObjectTable) *table = &onto->refs[type];
    ulib_uint count = cowl_vector_count(uhmap_get(CowlObjectTable, table, primitive, NULL));

    if (cowl_primitive_type_is_entity(type)) {
        CowlIRI *iri = cowl_entity_get_iri(primitive);
        count += cowl_vector_count(uhmap_get(CowlObjectTable, &onto->refs[COWL_PT_IRI], iri, NULL));
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            count += cowl_ontology_axiom_count_for_primitive(import, primitive, true);
        });
    }

    return count;
}

ulib_uint
cowl_ontology_primitives_count(CowlOntology *onto, CowlPrimitiveFlags flags, bool imports) {
    ulib_uint count = 0;

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        if (cowl_primitive_flags_has_type(flags, i)) {
            count += uhash_count(CowlObjectTable, &onto->refs[i]);
        }
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            count += cowl_ontology_primitives_count(import, flags, true);
        });
    }

    return count;
}

bool cowl_ontology_has_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive, bool imports) {
    CowlPrimitiveType type = cowl_primitive_get_type(primitive);
    if (uhash_contains(CowlObjectTable, &onto->refs[type], primitive)) return true;

    if (cowl_primitive_type_is_entity(type)) {
        CowlIRI *iri = cowl_entity_get_iri(primitive);
        if (uhash_contains(CowlObjectTable, &onto->refs[COWL_PT_IRI], iri)) return true;
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (cowl_ontology_has_primitive(import, primitive, true)) return true;
        });
    }

    return false;
}

bool cowl_ontology_has_axiom(CowlOntology *onto, CowlAnyAxiom *axiom, bool imports) {
    CowlVector *vec = onto->axioms_by_type[cowl_axiom_get_type(axiom)];
    if (vec && cowl_vector_contains(vec, axiom)) return true;

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (cowl_ontology_has_axiom(import, axiom, true)) return true;
        });
    }

    return false;
}

bool cowl_ontology_iterate_primitives(CowlOntology *onto, CowlPrimitiveFlags flags,
                                      CowlIterator *iter, bool imports) {
    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        if (!cowl_primitive_flags_has_type(flags, i)) continue;
        uhash_foreach (CowlObjectTable, &onto->refs[i], p) {
            if (!cowl_iterate_primitives(*p.key, flags, iter)) return false;
        }
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_primitives(import, flags, iter, true)) return false;
        });
    }

    return true;
}

bool cowl_ontology_iterate_imports(CowlOntology *onto, CowlIterator *iter, bool imports) {
    cowl_ontology_foreach_import(onto, import, {
        if (!cowl_iterate(iter, import)) return false;
    });

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_imports(import, iter, true)) return false;
        });
    }

    return true;
}

bool cowl_ontology_iterate_import_iris(CowlOntology *onto, CowlIterator *iter, bool imports) {
    cowl_table_foreach (onto->imports, import) {
        if (!cowl_iterate(iter, *import.key)) return false;
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_import_iris(import, iter, true)) return false;
        });
    }

    return true;
}

bool cowl_ontology_iterate_axioms(CowlOntology *onto, CowlIterator *iter, bool imports) {
    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        cowl_vector_foreach (onto->axioms_by_type[type], axiom) {
            if (!cowl_iterate(iter, *axiom.item)) return false;
        }
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_axioms(import, iter, true)) return false;
        });
    }

    return true;
}

bool cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type,
                                          CowlIterator *iter, bool imports) {
    cowl_vector_foreach (onto->axioms_by_type[type], axiom) {
        if (!cowl_iterate(iter, *axiom.item)) return false;
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_axioms_of_type(import, type, iter, true)) return false;
        });
    }

    return true;
}

bool cowl_ontology_iterate_axioms_of_types(CowlOntology *onto, CowlAxiomFlags types,
                                           CowlIterator *iter, bool imports) {
    cowl_axiom_flags_foreach_type (types, type) {
        if (!cowl_ontology_iterate_axioms_of_type(onto, type, iter, imports)) return false;
    }
    return true;
}

bool cowl_ontology_iterate_axioms_for_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive,
                                                CowlIterator *iter, bool imports) {
    CowlPrimitiveType type = cowl_primitive_get_type(primitive);
    UHash(CowlObjectTable) *table = &onto->refs[type];

    cowl_vector_foreach (uhmap_get(CowlObjectTable, table, primitive, NULL), a) {
        if (!cowl_iterate(iter, *a.item)) return false;
    }

    if (cowl_primitive_type_is_entity(type)) {
        CowlIRI *iri = cowl_entity_get_iri(primitive);
        cowl_vector_foreach (uhmap_get(CowlObjectTable, &onto->refs[COWL_PT_IRI], iri, NULL), a) {
            if (!cowl_iterate(iter, *a.item)) return false;
        }
    }

    if (imports) {
        cowl_ontology_foreach_import(onto, import, {
            if (!cowl_ontology_iterate_axioms_for_primitive(import, primitive, iter, true)) {
                return false;
            }
        });
    }
    return true;
}

static CowlAnyPrimitive *
cowl_ontology_best_primitive_for_filter(CowlOntology *onto, CowlAxiomFilter *filter, bool imports) {
    if (cowl_axiom_flags_has_no_types(filter->types)) {
        // No types specified in the filter.
        filter->types = COWL_AF_NONE;
        return NULL;
    }

    CowlAnyPrimitive *best = NULL;
    ulib_uint count = ULIB_UINT_MAX;

    uvec_foreach (CowlObjectPtr, &filter->primitives, p) {
        ulib_uint c = cowl_ontology_axiom_count_for_primitive(onto, *p.item, true);
        if (c < count) {
            best = *p.item;
            count = c;
        }
    }

    if (cowl_axiom_flags_has_all_types(filter->types)) {
        filter->types = COWL_AF_ALL;
    } else {
        ulib_uint c = cowl_ontology_axiom_count_for_types(onto, filter->types, imports);
        if (c < count) best = NULL;
    }

    if (!count) {
        // Index matches an empty set of axioms.
        filter->types = COWL_AF_NONE;
        return NULL;
    }

    return best;
}

struct MatchingCtx {
    CowlAxiomFilter *filter;
    CowlIterator *iter;
};

static bool for_each_filter(void *ctx, CowlAnyAxiom *axiom) {
    struct MatchingCtx *mctx = ctx;
    if (!cowl_axiom_filter_matches(mctx->filter, axiom)) return true;
    return cowl_iterate(mctx->iter, axiom);
}

bool cowl_ontology_iterate_axioms_matching(CowlOntology *onto, CowlAxiomFilter *filter,
                                           CowlIterator *iter, bool imports) {
    bool ret = true;
    CowlAxiomFilter f = cowl_axiom_filter_move(filter);

    struct MatchingCtx ctx = {
        .filter = &f,
        .iter = iter,
    };

    CowlAnyPrimitive *best = cowl_ontology_best_primitive_for_filter(onto, &f, imports);
    if (f.types == COWL_AF_NONE) goto end;

    UBit(8) const NONE = ubit_none(8);
    UBit(8) const TYPES = ubit_bit(8, 0);
    UBit(8) const PRIMITIVES = ubit_bit(8, 1);
    UBit(8) const FILTER = ubit_bit(8, 2);
    UBit(8) check = NONE;

    if (f.types != COWL_AF_ALL) check = ubit_set(8, check, TYPES);
    if (uvec_count(CowlObjectPtr, &f.primitives)) check = ubit_set(8, check, PRIMITIVES);
    if (f.closure.filter) check = ubit_set(8, check, FILTER);

    if (best) {
        // We will be iterating only over axioms that reference this primitive.
        cowl_axiom_filter_remove_primitive(filter, best);
        if (check) {
            CowlIterator l_iter = { .ctx = &ctx, .for_each = for_each_filter };
            ret = cowl_ontology_iterate_axioms_for_primitive(onto, best, &l_iter, imports);
        } else {
            ret = cowl_ontology_iterate_axioms_for_primitive(onto, best, iter, imports);
        }
    } else {
        // We will be iterating only over axioms of the specified types.
        CowlAxiomFlags types = f.types;
        f.types = COWL_AF_ALL;
        if (check == NONE) {
            ret = cowl_ontology_iterate_axioms(onto, iter, imports);
        } else if (check == TYPES) {
            ret = cowl_ontology_iterate_axioms_of_types(onto, types, iter, imports);
        } else if (ubit_is_set(8, check, TYPES)) {
            CowlIterator l_iter = { .ctx = &ctx, .for_each = for_each_filter };
            ret = cowl_ontology_iterate_axioms_of_types(onto, types, &l_iter, imports);
        } else {
            CowlIterator l_iter = { .ctx = &ctx, .for_each = for_each_filter };
            ret = cowl_ontology_iterate_axioms(onto, &l_iter, imports);
        }
    }

end:
    cowl_axiom_filter_deinit(&f);
    return ret;
}

struct RelatedCtx {
    CowlAxiomType type;
    CowlPosition position;
    CowlAnyPrimitive *primitive;
    CowlIterator *iter;
};

static bool for_each_related_operand(void *ctx, CowlAny *op) {
    struct RelatedCtx *c = ctx;
    return c->primitive == op || cowl_iterate(c->iter, op);
}

static bool for_each_related(void *ctx, CowlAny *axiom) {
    struct RelatedCtx *c = ctx;
    if (cowl_axiom_get_type(axiom) != c->type) return true;
    if (!cowl_axiom_has_operand(axiom, c->primitive, COWL_PS_ANY)) return true;
    CowlIterator iter = { .ctx = ctx, .for_each = for_each_related_operand };
    return cowl_axiom_iterate_operands(axiom, c->position, &iter);
}

bool cowl_ontology_iterate_related(CowlOntology *onto, CowlAnyPrimitive *primitive,
                                   CowlAxiomType type, CowlPosition position, CowlIterator *iter,
                                   bool imports) {
    struct RelatedCtx ctx = {
        .type = type,
        .position = position,
        .primitive = primitive,
        .iter = iter,
    };
    CowlIterator l_iter = { .ctx = &ctx, .for_each = for_each_related };

    // Iterate over the smallest possible set of axioms.
    CowlPrimitiveType pt = cowl_primitive_get_type(primitive);
    CowlVector *ar = uhmap_get(CowlObjectTable, &onto->refs[pt], primitive, NULL);
    CowlVector *at = onto->axioms_by_type[type];

    if (cowl_vector_count(at) < cowl_vector_count(ar)) {
        return cowl_ontology_iterate_axioms_of_type(onto, type, iter, imports);
    } else {
        return cowl_ontology_iterate_axioms_for_primitive(onto, primitive, &l_iter, imports);
    }
}

void cowl_ontology_set_iri(CowlOntology *onto, CowlIRI *iri) {
    cowl_release(onto->id.iri);
    onto->id.iri = iri ? cowl_retain(iri) : NULL;
}

void cowl_ontology_set_version(CowlOntology *onto, CowlIRI *version) {
    cowl_release(onto->id.version);
    onto->id.version = version ? cowl_retain(version) : NULL;
}

typedef struct CowlAxiomCtx {
    cowl_ret ret;
    CowlOntology *onto;
    CowlAxiom *axiom;
} CowlAxiomCtx;

static cowl_ret cowl_add_primitive_to_map(CowlObject *primitive, UHash(CowlObjectTable) *map) {
    ulib_uint idx;
    uhash_ret ret = uhash_put(CowlObjectTable, map, primitive, &idx);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    if (ret == UHASH_INSERTED) {
        uhash_value(CowlObjectTable, map, idx) = NULL;
    }

    return COWL_OK;
}

static bool cowl_ontology_primitive_adder(void *ctx, CowlAny *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    UHash(CowlObjectTable) *map = &axiom_ctx->onto->refs[cowl_primitive_get_type(obj)];
    cowl_ret ret = cowl_add_primitive_to_map(obj, map);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}

static inline cowl_ret cowl_vector_ptr_add(CowlVector **vec, CowlAny *obj) {
    if (!(*vec || (*vec = cowl_vector_ordered_empty()))) return COWL_ERR_MEM;
    return cowl_vector_add(*vec, obj) ? COWL_ERR_MEM : COWL_OK;
}

cowl_ret cowl_ontology_add_annot(CowlOntology *onto, CowlAnnotation *annot) {
    cowl_ret ret;
    CowlAxiomCtx ctx = { .onto = onto };
    CowlIterator iter = { &ctx, cowl_ontology_primitive_adder };
    cowl_iterate_primitives(annot, COWL_PF_ALL, &iter);
    if (!(ret = ctx.ret)) ret = cowl_vector_ptr_add(&onto->annot, annot);
    if (ret) cowl_handle_error_code(ret, onto);
    return ret;
}

bool cowl_ontology_remove_annot(CowlOntology *onto, CowlAnnotation *annot) {
    if (!onto->annot) return false;
    return cowl_vector_remove(onto->annot, annot);
}

CowlOntology *cowl_ontology_get_import(CowlOntology *onto, CowlIRI *iri) {
    return onto->imports ? cowl_table_get_value(onto->imports, iri) : NULL;
}

CowlIRI *cowl_ontology_get_import_iri(CowlOntology *onto, CowlOntology *import) {
    if (!onto->imports) return NULL;
    cowl_table_foreach (onto->imports, e) {
        if (*e.val && cowl_ontology_equals(import, *e.val)) return *e.key;
    }
    return NULL;
}

cowl_ret cowl_ontology_add_import(CowlOntology *onto, CowlIRI *iri) {
    ulib_uint idx = UHASH_INDEX_MISSING;
    UHash(CowlObjectTable) map = uhmap_pi(CowlObjectTable, cowl_primitive_hash,
                                          cowl_primitive_equals);
    if (!onto->imports && !(onto->imports = cowl_table(&map))) goto err;

    UHash(CowlObjectTable) *tbl = &onto->imports->data;
    uhash_ret hret = uhash_put(CowlObjectTable, tbl, iri, &idx);

    if (hret == UHASH_INSERTED) {
        cowl_retain(iri);
    } else if (hret == UHASH_PRESENT) {
        return COWL_OK;
    } else {
        goto err;
    }

    CowlOntology *import = NULL;
    CowlImportLoader loader = cowl_manager_get_import_loader(onto->manager);
    if (loader.load_ontology && !(import = loader.load_ontology(loader.ctx, iri))) goto err;
    uhash_value(CowlObjectTable, tbl, idx) = import;

    return COWL_OK;

err:
    if (onto->imports && idx < uhash_size(CowlObjectTable, &onto->imports->data)) {
        uhash_delete(CowlObjectTable, &onto->imports->data, idx);
    }
    cowl_handle_error_code(COWL_ERR_IMPORT, onto);
    return COWL_ERR_IMPORT;
}

bool cowl_ontology_remove_import(CowlOntology *onto, CowlIRI *iri) {
    if (!onto->imports) return false;

    UHash(CowlObjectTable) *tbl = &onto->imports->data;
    ulib_uint idx = uhash_get(CowlObjectTable, tbl, iri);
    if (idx == UHASH_INDEX_MISSING) return false;

    uhash_delete(CowlObjectTable, tbl, idx);
    cowl_release(iri);
    cowl_release(uhash_value(CowlObjectTable, tbl, idx));
    return true;
}

COWL_INLINE cowl_ret cowl_add_axiom_to_map(CowlObject *primitive, CowlAxiom *axiom,
                                           UHash(CowlObjectTable) *map) {
    ulib_uint idx;
    uhash_ret ret = uhash_put(CowlObjectTable, map, primitive, &idx);
    if (ret == UHASH_ERR) return COWL_ERR_MEM;

    CowlVector *vec = uhash_value(CowlObjectTable, map, idx);

    if (ret == UHASH_INSERTED || !vec) {
        vec = cowl_vector_ordered_empty();
        uhash_value(CowlObjectTable, map, idx) = vec;
        if (!vec) return COWL_ERR_MEM;
    }

    if (cowl_vector_push(vec, axiom)) {
        return COWL_ERR_MEM;
    }

    return COWL_OK;
}

static bool cowl_ontology_primitive_axiom_adder(void *ctx, CowlAny *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    UHash(CowlObjectTable) *map = &axiom_ctx->onto->refs[cowl_primitive_get_type(obj)];
    cowl_ret ret = cowl_add_axiom_to_map(obj, axiom_ctx->axiom, map);
    axiom_ctx->ret = ret;
    return ret == COWL_OK;
}

cowl_ret cowl_ontology_add_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    cowl_ret ret;
    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = { &ctx, cowl_ontology_primitive_axiom_adder };

    cowl_iterate_primitives(axiom, COWL_PF_ALL, &iter);
    if ((ret = ctx.ret)) goto end;

    ret = cowl_vector_ptr_add(&onto->axioms_by_type[cowl_axiom_get_type(axiom)], axiom);

end:
    if (ret) cowl_handle_error_code(ret, onto);
    return ret;
}

COWL_INLINE void
cowl_remove_axiom_from_map(CowlObject *primitive, CowlAxiom *axiom, UHash(CowlObjectTable) *map) {
    CowlVector *vec = uhmap_get(CowlObjectTable, map, primitive, NULL);
    if (!vec) return;
    uvec_foreach_reverse (CowlObjectPtr, &vec->data, a) {
        if (*a.item == axiom) {
            uvec_unordered_remove_at(CowlObjectPtr, &vec->data, a.i);
            break;
        }
    }
}

static bool cowl_ontology_primitive_axiom_remover(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    UHash(CowlObjectTable) *map = &axiom_ctx->onto->refs[cowl_primitive_get_type(obj)];
    cowl_remove_axiom_from_map(obj, axiom_ctx->axiom, map);
    axiom_ctx->ret = COWL_OK;
    return true;
}

static void cowl_ontology_remove_axiom_ptr(CowlOntology *onto, CowlAnyAxiom *axiom) {
    // We could just use uvec_unordered_remove, though looking for axioms to remove in reverse
    // is desirable as recently added axioms are likely to be at the top of the vector.
    UVec(CowlObjectPtr) *vec = &onto->axioms_by_type[cowl_axiom_get_type(axiom)]->data;
    uvec_foreach_reverse (CowlObjectPtr, vec, a) {
        if (*a.item == axiom) {
            uvec_unordered_remove_at(CowlObjectPtr, vec, a.i);
            break;
        }
    }

    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = { &ctx, cowl_ontology_primitive_axiom_remover };
    cowl_iterate_primitives(axiom, COWL_PF_ALL, &iter);
    cowl_release(axiom);
}

bool cowl_ontology_remove_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    CowlAxiomType type = cowl_axiom_get_type(axiom);
    if (!onto->axioms_by_type[type]) return false;

    // Iterate in reverse to match the element removed by cowl_ontology_remove_axiom_ptr.
    // TODO: this can be optimized by finding the best index for the axiom.
    UVec(CowlObjectPtr) *vec = &onto->axioms_by_type[type]->data;
    uvec_foreach_reverse (CowlObjectPtr, vec, a) {
        if (cowl_equals(axiom, *a.item)) {
            cowl_ontology_remove_axiom_ptr(onto, axiom);
            return true;
        }
    }

    return false;
}

ulib_uint cowl_ontology_remove_axioms_matching(CowlOntology *onto, CowlAxiomFilter *filter) {
    ulib_uint count = 0;
    CowlAxiomFilter f = cowl_axiom_filter_move(filter);
    if (f.types == COWL_AF_NONE) goto end;

    CowlAnyPrimitive *best = cowl_ontology_best_primitive_for_filter(onto, &f, false);
    if (best) {
        // Iterate over axioms referencing the primitive.
        cowl_axiom_filter_remove_primitive(filter, best);
        UHash(CowlObjectTable) *table = &onto->refs[cowl_primitive_get_type(best)];
        CowlVector *vec = uhmap_get(CowlObjectTable, table, best, NULL);
        uvec_foreach_reverse (CowlObjectPtr, &vec->data, axiom) {
            CowlAnyAxiom *a = *axiom.item;
            if (!cowl_axiom_filter_matches(&f, a)) continue;
            cowl_ontology_remove_axiom_ptr(onto, a);
            count++;
        }
    } else {
        // Iterate over axioms of the specified types.
        CowlAxiomFlags types = f.types;
        f.types = COWL_AF_ALL;
        cowl_axiom_flags_foreach_type (types, type) {
            CowlVector *vec = onto->axioms_by_type[type];
            if (!vec) continue;
            uvec_foreach_reverse (CowlObjectPtr, &vec->data, axiom) {
                CowlAnyAxiom *a = *axiom.item;
                if (!cowl_axiom_filter_matches(&f, a)) continue;
                cowl_ontology_remove_axiom_ptr(onto, a);
                count++;
            }
        }
    }

end:
    cowl_axiom_filter_deinit(&f);
    return count;
}

cowl_ret cowl_ontology_finalize(CowlOntology *onto) {
    cowl_ret ret = COWL_ERR_MEM;
    if (onto->annot && cowl_vector_shrink(onto->annot)) goto end;

    for (CowlAxiomType t = COWL_AT_FIRST; t < COWL_AT_COUNT; ++t) {
        CowlVector *axioms = onto->axioms_by_type[t];
        if (axioms && cowl_vector_shrink(axioms)) goto end;
    }

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        uhash_foreach (CowlObjectTable, &onto->refs[i], item) {
            CowlVector *primitives = *item.val;
            if (primitives && cowl_vector_shrink(primitives)) goto end;
        }
    }

    ret = COWL_OK;

end:
    if (ret) cowl_handle_error_code(ret, onto);
    return ret;
}
