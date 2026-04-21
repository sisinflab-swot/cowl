/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_ontology.h"
#include "cowl_any.h"
#include "cowl_axiom.h"
#include "cowl_axiom_filter_private.h"
#include "cowl_axiom_flags.h"
#include "cowl_axiom_type.h"
#include "cowl_change.h"
#include "cowl_config.h"
#include "cowl_entity.h"
#include "cowl_iterator.h"
#include "cowl_object_private.h"
#include "cowl_object_type.h"
#include "cowl_ontology_private.h"
#include "cowl_position.h"
#include "cowl_prefix_map_private.h"
#include "cowl_primitive_flags.h"
#include "cowl_primitive_private.h"
#include "cowl_primitive_type.h"
#include "cowl_reader.h"
#include "cowl_ret.h"
#include "cowl_table_private.h"
#include "cowl_vector_private.h"
#include "cowl_writer.h"
#include "ulib.h"
#include <assert.h>
#include <stddef.h>

CowlOntology *cowl_ontology(void) {
    CowlOntology *onto = ulib_alloc(onto);
    if (!onto) return NULL;
    *onto = (CowlOntology){ .super = COWL_OBJECT_INIT(COWL_OT_ONTOLOGY) };
    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        onto->refs[i] = cowl_primitive_map();
    }
    return onto;
}

void cowl_ontology_free(CowlOntology *onto) {
    cowl_release(onto->pm);
    cowl_release(onto->iri);
    cowl_release(onto->version);
    cowl_release(onto->imports);
    cowl_release(onto->annot);

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; type++) {
        cowl_release(onto->axioms_by_type[type]);
    }

    for (ulib_uint i = 0; i < ulib_array_count(onto->refs); ++i) {
        uhash_foreach (CowlObjectPtr, &onto->refs[i], vec) {
            cowl_vector_release_ex(*vec.val, false);
        }
        uhash_deinit(CowlObjectPtr, &onto->refs[i]);
    }

    ulib_free(onto);
}

static inline bool indexing_enabled(CowlOntology *onto) {
    return !cowl_object_bit_get(onto);
}

void cowl_ontology_disable_indexing(CowlOntology *onto) {
    cowl_object_bit_set(onto);
}

// Primitive index: maps primitives to the axioms that reference them.
static inline CowlVector *pindex(CowlOntology *onto, CowlAnyPrimitive *primitive) {
    CowlPrimitiveType pt = cowl_primitive_get_type(primitive);
    return uhmap_get(CowlObjectPtr, &onto->refs[pt], primitive, NULL);
}

// Type index: maps axiom types to the axioms of that type.
static inline CowlVector *tindex(CowlOntology *onto, CowlAxiomType type) {
    return onto->axioms_by_type[type];
}

struct BestPrimitiveCtx {
    CowlOntology *onto;
    CowlPrimitive *best;
    CowlVector *best_index;
    ulib_uint *count;
};

static cowl_ret best_pindex_foreach(void *ctx, CowlAnyPrimitive *primitive) {
    struct BestPrimitiveCtx *c = ctx;
    CowlVector *index = pindex(c->onto, primitive);
    ulib_uint const count = cowl_vector_count(index);

    if (count < *c->count) {
        *c->count = count;
        c->best = primitive;
        c->best_index = index;
    }

    return COWL_CONTINUE;
}

static CowlVector *best_pindex(CowlOntology *onto, CowlAny *obj, CowlPrimitive **best) {
    ulib_uint count = ULIB_UINT_MAX;
    struct BestPrimitiveCtx ctx = { .onto = onto, .count = &count };
    CowlIterator iter = { .ctx = &ctx, .for_each = best_pindex_foreach };
    cowl_iterate_primitives(obj, COWL_PF_ALL, &iter);
    if (best) *best = ctx.best;
    return ctx.best_index;
}

static inline CowlVector *best_index_between(CowlVector *a, CowlVector *b) {
    if (!a) return b;
    if (!b) return a;
    return cowl_vector_count(a) < cowl_vector_count(b) ? a : b;
}

static CowlVector *best_index(CowlOntology *onto, CowlAny *obj, CowlAxiomType type) {
    CowlVector *t = NULL;
    if (type < COWL_AT_COUNT && !(t = tindex(onto, type))) return NULL;
    CowlVector *p = cowl_is_primitive(obj) ? pindex(onto, obj) : best_pindex(onto, obj, NULL);
    return best_index_between(p, t);
}

CowlOntology *cowl_ontology_at_path(UString path, cowl_ret *ret) {
    return cowl_reader_read_ontology_at_path(cowl_get_reader(), path, ret);
}

CowlOntology *cowl_ontology_from_stream(UIStream *stream, cowl_ret *ret) {
    return cowl_reader_read_ontology(cowl_get_reader(), stream, ret);
}

cowl_ret cowl_ontology_to_path(CowlOntology *onto, UString path) {
    return cowl_writer_write_ontology_to_path(cowl_get_writer(), path, onto);
}

cowl_ret cowl_ontology_to_stream(CowlOntology *onto, UOStream *stream) {
    return cowl_writer_write_ontology(cowl_get_writer(), stream, onto);
}

CowlPrefixMap *cowl_ontology_get_prefix_map(CowlOntology *onto) {
    return onto->pm ? onto->pm : (onto->pm = cowl_prefix_map());
}

CowlIRI *cowl_ontology_get_iri(CowlOntology *onto) {
    return onto->iri;
}

CowlIRI *cowl_ontology_get_version(CowlOntology *onto) {
    return onto->version;
}

CowlVector *cowl_ontology_get_annot(CowlOntology *onto) {
    return onto->annot ? onto->annot : (onto->annot = cowl_vector_ordered_empty());
}

ulib_uint cowl_ontology_axiom_count(CowlOntology *onto) {
    ulib_uint count = 0;

    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        count += cowl_vector_count(tindex(onto, type));
    }

    return count;
}

ulib_uint cowl_ontology_imports_count(CowlOntology *onto) {
    return cowl_vector_count(onto->imports);
}

ulib_uint cowl_ontology_axiom_count_for_type(CowlOntology *onto, CowlAxiomType type) {
    return cowl_vector_count(tindex(onto, type));
}

ulib_uint cowl_ontology_axiom_count_for_types(CowlOntology *onto, CowlAxiomFlags types) {
    ulib_uint count = 0;
    cowl_axiom_flags_foreach_type (types, type) {
        count += cowl_ontology_axiom_count_for_type(onto, type);
    }
    return count;
}

ulib_uint cowl_ontology_axiom_count_for_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive) {
    ulib_uint count = cowl_vector_count(pindex(onto, primitive));

    if (cowl_is_entity(primitive)) {
        CowlIRI *iri = cowl_entity_get_iri(primitive);
        count += cowl_vector_count(pindex(onto, iri));
    }

    return count;
}

ulib_uint cowl_ontology_primitives_count(CowlOntology *onto, CowlPrimitiveFlags flags) {
    ulib_uint count = 0;

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        if (cowl_primitive_flags_has_type(flags, i)) {
            count += uhash_count(CowlObjectPtr, &onto->refs[i]);
        }
    }

    return count;
}

bool cowl_ontology_has_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive) {
    CowlPrimitiveType type = cowl_primitive_get_type(primitive);
    if (uhash_contains(CowlObjectPtr, &onto->refs[type], primitive)) return true;

    if (cowl_primitive_type_is_entity(type)) {
        CowlIRI *iri = cowl_entity_get_iri(primitive);
        if (uhash_contains(CowlObjectPtr, &onto->refs[COWL_PT_IRI], iri)) return true;
    }

    return false;
}

bool cowl_ontology_has_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    CowlVector *index = best_index(onto, axiom, cowl_axiom_get_type(axiom));
    return index ? cowl_vector_contains(index, axiom) : false;
}

cowl_ret cowl_ontology_iterate_annot(CowlOntology *onto, CowlIterator *iter) {
    cowl_vector_foreach (onto->annot, annot) {
        cowl_ret const ret = cowl_iterator_call(iter, *annot.item);
        if (cowl_should_stop(ret)) return ret;
    }
    return COWL_CONTINUE;
}

cowl_ret cowl_ontology_iterate_imports(CowlOntology *onto, CowlIterator *iter) {
    cowl_vector_foreach (onto->imports, import) {
        cowl_ret const ret = cowl_iterator_call(iter, *import.item);
        if (cowl_should_stop(ret)) return ret;
    }
    return COWL_CONTINUE;
}

cowl_ret
cowl_ontology_iterate_primitives(CowlOntology *onto, CowlPrimitiveFlags flags, CowlIterator *iter) {
    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        if (!cowl_primitive_flags_has_type(flags, i)) continue;
        uhash_foreach (CowlObjectPtr, &onto->refs[i], p) {
            cowl_ret const ret = cowl_iterate_primitives(*p.key, flags, iter);
            if (cowl_should_stop(ret)) return ret;
        }
    }
    return COWL_CONTINUE;
}

cowl_ret cowl_ontology_iterate_axioms(CowlOntology *onto, CowlIterator *iter) {
    for (CowlAxiomType type = COWL_AT_FIRST; type < COWL_AT_COUNT; ++type) {
        cowl_vector_foreach (tindex(onto, type), axiom) {
            cowl_ret const ret = cowl_iterator_call(iter, *axiom.item);
            if (cowl_should_stop(ret)) return ret;
        }
    }
    return COWL_CONTINUE;
}

cowl_ret
cowl_ontology_iterate_axioms_of_type(CowlOntology *onto, CowlAxiomType type, CowlIterator *iter) {
    cowl_vector_foreach (tindex(onto, type), axiom) {
        cowl_ret const ret = cowl_iterator_call(iter, *axiom.item);
        if (cowl_should_stop(ret)) return ret;
    }
    return COWL_CONTINUE;
}

cowl_ret cowl_ontology_iterate_axioms_of_types(CowlOntology *onto, CowlAxiomFlags types,
                                               CowlIterator *iter) {
    cowl_axiom_flags_foreach_type (types, type) {
        cowl_ret const ret = cowl_ontology_iterate_axioms_of_type(onto, type, iter);
        if (cowl_should_stop(ret)) return ret;
    }
    return COWL_CONTINUE;
}

cowl_ret cowl_ontology_iterate_axioms_for_primitive(CowlOntology *onto, CowlAnyPrimitive *primitive,
                                                    CowlIterator *iter) {
    CowlVector *axioms = pindex(onto, primitive);

    cowl_vector_foreach (axioms, a) {
        cowl_ret const ret = cowl_iterator_call(iter, *a.item);
        if (cowl_should_stop(ret)) return ret;
    }

    if (cowl_is_entity(primitive)) {
        CowlIRI *iri = cowl_entity_get_iri(primitive);
        cowl_vector_foreach (pindex(onto, iri), a) {
            cowl_ret const ret = cowl_iterator_call(iter, *a.item);
            if (cowl_should_stop(ret)) return ret;
        }
    }

    return COWL_CONTINUE;
}

static CowlVector *
best_pindex_for_filter(CowlOntology *onto, CowlAxiomFilter *filter, CowlPrimitive **best) {
    CowlVector vec = cowl_vector_init(&filter->primitives);
    CowlPrimitive *lbest = NULL;
    CowlVector *index = best_pindex(onto, &vec, &lbest);
    ulib_uint const count = cowl_vector_count(index);

    if (!count || cowl_axiom_flags_has_no_types(filter->types)) {
        filter->types = COWL_AF_NONE;
        lbest = NULL;
    } else if (cowl_axiom_flags_has_all_types(filter->types)) {
        filter->types = COWL_AF_ALL;
    } else if (cowl_ontology_axiom_count_for_types(onto, filter->types) < count) {
        lbest = NULL;
    }

    if (best) *best = lbest;
    if (lbest) {
        cowl_axiom_filter_remove_primitive(filter, lbest);
        return index;
    }
    return NULL;
}

struct MatchingCtx {
    CowlAxiomFilter *filter;
    CowlIterator *iter;
};

static cowl_ret iterate_axioms_matching_foreach(void *ctx, CowlAnyAxiom *axiom) {
    struct MatchingCtx *mctx = ctx;
    if (!cowl_axiom_filter_matches(mctx->filter, axiom)) return COWL_CONTINUE;
    return cowl_iterator_call(mctx->iter, axiom);
}

cowl_ret cowl_ontology_iterate_axioms_matching(CowlOntology *onto, CowlAxiomFilter *filter,
                                               CowlIterator *iter) {
    cowl_ret ret = COWL_CONTINUE;
    CowlAxiomFilter f = cowl_axiom_filter_move(filter);

    struct MatchingCtx ctx = {
        .filter = &f,
        .iter = iter,
    };

    CowlPrimitive *best = NULL;
    best_pindex_for_filter(onto, &f, &best);
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
        if (check) {
            CowlIterator l_iter = { .ctx = &ctx, .for_each = iterate_axioms_matching_foreach };
            ret = cowl_ontology_iterate_axioms_for_primitive(onto, best, &l_iter);
        } else {
            ret = cowl_ontology_iterate_axioms_for_primitive(onto, best, iter);
        }
    } else {
        // We will be iterating only over axioms of the specified types.
        CowlAxiomFlags types = f.types;
        f.types = COWL_AF_ALL;
        if (check == NONE) {
            ret = cowl_ontology_iterate_axioms(onto, iter);
        } else if (check == TYPES) {
            ret = cowl_ontology_iterate_axioms_of_types(onto, types, iter);
        } else if (ubit_is_set(8, check, TYPES)) {
            CowlIterator l_iter = { .ctx = &ctx, .for_each = iterate_axioms_matching_foreach };
            ret = cowl_ontology_iterate_axioms_of_types(onto, types, &l_iter);
        } else {
            CowlIterator l_iter = { .ctx = &ctx, .for_each = iterate_axioms_matching_foreach };
            ret = cowl_ontology_iterate_axioms(onto, &l_iter);
        }
    }

end:
    cowl_axiom_filter_deinit(&f);
    return ret;
}

struct RelatedCtx {
    CowlAxiomFlags types;
    CowlPosition position;
    CowlAnyPrimitive *primitive;
    CowlIterator *iter;
};

static cowl_ret iterate_related_foreach_foreach(void *ctx, CowlAny *op) {
    struct RelatedCtx *c = ctx;
    if (c->primitive == op) return COWL_CONTINUE;
    return cowl_iterator_call(c->iter, op);
}

static cowl_ret iterate_related_foreach(void *ctx, CowlAny *axiom) {
    struct RelatedCtx *c = ctx;
    if (!cowl_axiom_flags_has_type(c->types, cowl_axiom_get_type(axiom))) return COWL_CONTINUE;
    if (!cowl_axiom_has_operand(axiom, c->primitive, COWL_PS_ANY)) return COWL_CONTINUE;
    CowlIterator iter = { .ctx = ctx, .for_each = iterate_related_foreach_foreach };
    return cowl_axiom_iterate_operands(axiom, c->position, &iter);
}

cowl_ret
cowl_ontology_iterate_related(CowlOntology *onto, CowlAnyPrimitive *primitive, CowlAxiomFlags types,
                              CowlPosition position, CowlIterator *iter) {
    struct RelatedCtx ctx = {
        .types = types,
        .position = position,
        .primitive = primitive,
        .iter = iter,
    };
    CowlIterator l_iter = { .ctx = &ctx, .for_each = iterate_related_foreach };
    CowlVector *index = pindex(onto, primitive);
    return index ? cowl_vector_iterate(index, &l_iter) : COWL_OK;
}

cowl_ret cowl_ontology_set_iri(CowlOntology *onto, CowlIRI *iri) {
    cowl_release(onto->iri);
    onto->iri = iri ? cowl_retain(iri) : NULL;
    return COWL_OK;
}

cowl_ret cowl_ontology_set_version(CowlOntology *onto, CowlIRI *version) {
    cowl_release(onto->version);
    onto->version = version ? cowl_retain(version) : NULL;
    return COWL_OK;
}

typedef struct CowlAxiomCtx {
    CowlOntology *onto;
    CowlAxiom *axiom;
} CowlAxiomCtx;

static inline cowl_ret vector_ptr_add(CowlVector **vec, CowlAny *obj) {
    if (!(*vec || (*vec = cowl_vector_ordered_empty()))) return COWL_ERR_MEM;
    return cowl_vector_add(*vec, obj) ? COWL_ERR_MEM : COWL_OK;
}

static bool vector_ptr_remove(CowlVector **vec, CowlAny *obj) {
    if (!*vec) return false;
    bool removed = cowl_vector_remove(*vec, obj);
    if (removed && cowl_vector_count(*vec) == 0) {
        cowl_release(*vec);
        *vec = NULL;
    }
    return removed;
}

static cowl_ret add_primitive_to_map(CowlObject *primitive, UHash(CowlObjectPtr) *map) {
    ulib_uint idx;
    ulib_ret const ret = uhash_put(CowlObjectPtr, map, primitive, &idx);
    if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);
    if (ret == ULIB_OK) uhmap_set_val(CowlObjectPtr, map, idx, NULL);
    return COWL_OK;
}

static cowl_ret add_annot_foreach(void *ctx, CowlAny *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    UHash(CowlObjectPtr) *map = &axiom_ctx->onto->refs[cowl_primitive_get_type(obj)];
    return add_primitive_to_map(obj, map);
}

cowl_ret cowl_ontology_add_annot(CowlOntology *onto, CowlAnnotation *annot) {
    CowlAxiomCtx ctx = { .onto = onto };
    CowlIterator iter = { &ctx, add_annot_foreach };
    cowl_ret ret = cowl_iterate_primitives(annot, COWL_PF_ALL, &iter);
    if (cowl_is_ok(ret)) ret = vector_ptr_add(&onto->annot, annot);
    return ret;
}

bool cowl_ontology_remove_annot(CowlOntology *onto, CowlAnnotation *annot) {
    return vector_ptr_remove(&onto->annot, annot);
}

bool cowl_ontology_has_import(CowlOntology *onto, CowlIRI *import) {
    return onto->imports && cowl_vector_contains(onto->imports, import);
}

cowl_ret cowl_ontology_add_import(CowlOntology *onto, CowlIRI *import) {
    return vector_ptr_add(&onto->imports, import);
}

bool cowl_ontology_remove_import(CowlOntology *onto, CowlIRI *iri) {
    return vector_ptr_remove(&onto->imports, iri);
}

static inline cowl_ret
add_axiom_to_map(CowlObject *primitive, CowlAxiom *axiom, UHash(CowlObjectPtr) *map) {
    ulib_uint idx;
    ulib_ret const ret = uhash_put(CowlObjectPtr, map, primitive, &idx);
    if (ulib_is_err(ret)) return cowl_ret_from_ulib(ret);

    CowlVector *vec = uhmap_val(CowlObjectPtr, map, idx);

    if (ret == ULIB_OK || !vec) {
        vec = cowl_vector_ordered_empty();
        uhmap_set_val(CowlObjectPtr, map, idx, vec);
        if (!vec) return COWL_ERR_MEM;
    }

    if (cowl_vector_push(vec, axiom)) {
        return COWL_ERR_MEM;
    }

    return COWL_OK;
}

static inline cowl_ret add_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    return vector_ptr_add(&onto->axioms_by_type[cowl_axiom_get_type(axiom)], axiom);
}

static cowl_ret index_axiom_foreach(void *ctx, CowlAny *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    UHash(CowlObjectPtr) *map = &axiom_ctx->onto->refs[cowl_primitive_get_type(obj)];
    return add_axiom_to_map(obj, axiom_ctx->axiom, map);
}

static inline cowl_ret index_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = { &ctx, index_axiom_foreach };
    return cowl_iterate_primitives(axiom, COWL_PF_ALL, &iter);
}

cowl_ret cowl_ontology_add_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    if (indexing_enabled(onto)) {
        cowl_ret ret = index_axiom(onto, axiom);
        if (cowl_is_err(ret)) return ret;
    }
    return add_axiom(onto, axiom);
}

static inline void
remove_axiom_from_map(CowlObject *primitive, CowlAxiom *axiom, UHash(CowlObjectPtr) *map) {
    CowlVector *vec = uhmap_get(CowlObjectPtr, map, primitive, NULL);
    if (!vec) return;
    uvec_foreach_reverse (CowlObjectPtr, &vec->data, a) {
        if (*a.item == axiom) {
            uvec_unordered_remove_at(CowlObjectPtr, &vec->data, a.i);
            break;
        }
    }
}

static void remove_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    // We could just use uvec_unordered_remove, though looking for axioms to remove in reverse
    // is desirable as recently added axioms are likely to be at the top of the vector.
    UVec(CowlObjectPtr) *vec = &tindex(onto, cowl_axiom_get_type(axiom))->data;
    uvec_foreach_reverse (CowlObjectPtr, vec, a) {
        if (*a.item == axiom) {
            uvec_unordered_remove_at(CowlObjectPtr, vec, a.i);
            break;
        }
    }
}

static cowl_ret unindex_axiom_foreach(void *ctx, void *obj) {
    CowlAxiomCtx *axiom_ctx = ctx;
    UHash(CowlObjectPtr) *map = &axiom_ctx->onto->refs[cowl_primitive_get_type(obj)];
    remove_axiom_from_map(obj, axiom_ctx->axiom, map);
    return COWL_CONTINUE;
}

static void unindex_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    CowlAxiomCtx ctx = { .onto = onto, .axiom = axiom };
    CowlIterator iter = { &ctx, unindex_axiom_foreach };
    cowl_iterate_primitives(axiom, COWL_PF_ALL, &iter);
}

static void remove_and_unindex(CowlOntology *onto, CowlAnyAxiom *axiom) {
    remove_axiom(onto, axiom);
    unindex_axiom(onto, axiom);
    cowl_release(axiom);
}

bool cowl_ontology_remove_axiom(CowlOntology *onto, CowlAnyAxiom *axiom) {
    CowlVector *index = best_index(onto, axiom, cowl_axiom_get_type(axiom));
    if (!index) return false;

    uvec_foreach_reverse (CowlObjectPtr, &index->data, a) {
        if (cowl_equals(axiom, *a.item)) {
            remove_and_unindex(onto, axiom);
            return true;
        }
    }

    return false;
}

static ulib_uint remove_matching(CowlOntology *onto, CowlVector *index, CowlAxiomFilter *f) {
    if (!index) return 0;
    ulib_uint count = 0;
    uvec_foreach_reverse (CowlObjectPtr, &index->data, axiom) {
        CowlAnyAxiom *a = *axiom.item;
        if (!cowl_axiom_filter_matches(f, a)) continue;
        remove_and_unindex(onto, a);
        count++;
    }
    return count;
}

ulib_uint cowl_ontology_remove_axioms_matching(CowlOntology *onto, CowlAxiomFilter *filter) {
    ulib_uint count = 0;
    CowlAxiomFilter f = cowl_axiom_filter_move(filter);
    CowlVector *best = NULL;
    if (f.types == COWL_AF_NONE) goto end;

    if ((best = best_pindex_for_filter(onto, &f, NULL))) {
        // Iterate over axioms referencing the primitive.
        count = remove_matching(onto, best, &f);
        goto end;
    }

    // Iterate over axioms of the specified types.
    CowlAxiomFlags types = f.types;
    f.types = COWL_AF_ALL;
    cowl_axiom_flags_foreach_type (types, type) {
        count += remove_matching(onto, tindex(onto, type), &f);
    }

end:
    cowl_axiom_filter_deinit(&f);
    return count;
}

cowl_ret cowl_ontology_finalize(CowlOntology *onto) {
    if (onto->annot && cowl_vector_shrink(onto->annot)) return COWL_ERR_MEM;
    if (onto->imports && cowl_vector_shrink(onto->imports)) return COWL_ERR_MEM;

    for (CowlAxiomType t = COWL_AT_FIRST; t < COWL_AT_COUNT; ++t) {
        CowlVector *axioms = onto->axioms_by_type[t];
        if (axioms && cowl_vector_shrink(axioms)) return COWL_ERR_MEM;
    }

    for (CowlPrimitiveType i = COWL_PT_FIRST; i < COWL_PT_COUNT; ++i) {
        uhash_foreach (CowlObjectPtr, &onto->refs[i], item) {
            CowlVector *primitives = *item.val;
            if (primitives && cowl_vector_shrink(primitives)) return COWL_ERR_MEM;
        }
    }

    return COWL_OK;
}
