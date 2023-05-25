/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_object_private.h"
#include "cowl_private.h"

static ulib_byte field_count[COWL_OT_COUNT] = { 0 };

cowl_ret cowl_object_api_init(void) {
    field_count[COWL_OT_FACET_RESTR] = 2;
    field_count[COWL_OT_ANNOTATION] = 2;
    field_count[COWL_OT_A_DECL] = 1;
    field_count[COWL_OT_A_DATATYPE_DEF] = 2;
    field_count[COWL_OT_A_SUB_CLASS] = 2;
    field_count[COWL_OT_A_EQUIV_CLASSES] = 1;
    field_count[COWL_OT_A_DISJ_CLASSES] = 1;
    field_count[COWL_OT_A_DISJ_UNION] = 2;
    field_count[COWL_OT_A_CLASS_ASSERT] = 2;
    field_count[COWL_OT_A_SAME_IND] = 1;
    field_count[COWL_OT_A_DIFF_IND] = 1;
    field_count[COWL_OT_A_OBJ_PROP_ASSERT] = 3;
    field_count[COWL_OT_A_NEG_OBJ_PROP_ASSERT] = 3;
    field_count[COWL_OT_A_DATA_PROP_ASSERT] = 3;
    field_count[COWL_OT_A_NEG_DATA_PROP_ASSERT] = 3;
    field_count[COWL_OT_A_SUB_OBJ_PROP] = 2;
    field_count[COWL_OT_A_INV_OBJ_PROP] = 2;
    field_count[COWL_OT_A_EQUIV_OBJ_PROP] = 1;
    field_count[COWL_OT_A_DISJ_OBJ_PROP] = 1;
    field_count[COWL_OT_A_FUNC_OBJ_PROP] = 1;
    field_count[COWL_OT_A_INV_FUNC_OBJ_PROP] = 1;
    field_count[COWL_OT_A_SYMM_OBJ_PROP] = 1;
    field_count[COWL_OT_A_ASYMM_OBJ_PROP] = 1;
    field_count[COWL_OT_A_REFL_OBJ_PROP] = 1;
    field_count[COWL_OT_A_IRREFL_OBJ_PROP] = 1;
    field_count[COWL_OT_A_TRANS_OBJ_PROP] = 1;
    field_count[COWL_OT_A_OBJ_PROP_DOMAIN] = 2;
    field_count[COWL_OT_A_OBJ_PROP_RANGE] = 2;
    field_count[COWL_OT_A_SUB_DATA_PROP] = 2;
    field_count[COWL_OT_A_EQUIV_DATA_PROP] = 1;
    field_count[COWL_OT_A_DISJ_DATA_PROP] = 1;
    field_count[COWL_OT_A_FUNC_DATA_PROP] = 1;
    field_count[COWL_OT_A_DATA_PROP_DOMAIN] = 2;
    field_count[COWL_OT_A_DATA_PROP_RANGE] = 2;
    field_count[COWL_OT_A_HAS_KEY] = 3;
    field_count[COWL_OT_A_ANNOT_ASSERT] = 3;
    field_count[COWL_OT_A_SUB_ANNOT_PROP] = 2;
    field_count[COWL_OT_A_ANNOT_PROP_DOMAIN] = 2;
    field_count[COWL_OT_A_ANNOT_PROP_RANGE] = 2;
    field_count[COWL_OT_CE_OBJ_SOME] = 1;
    field_count[COWL_OT_CE_OBJ_ALL] = 1;
    field_count[COWL_OT_CE_OBJ_MIN_CARD] = 1;
    field_count[COWL_OT_CE_OBJ_MAX_CARD] = 1;
    field_count[COWL_OT_CE_OBJ_EXACT_CARD] = 1;
    field_count[COWL_OT_CE_OBJ_HAS_VALUE] = 2;
    field_count[COWL_OT_CE_OBJ_HAS_SELF] = 1;
    field_count[COWL_OT_CE_DATA_SOME] = 1;
    field_count[COWL_OT_CE_DATA_ALL] = 1;
    field_count[COWL_OT_CE_DATA_MIN_CARD] = 1;
    field_count[COWL_OT_CE_DATA_MAX_CARD] = 1;
    field_count[COWL_OT_CE_DATA_EXACT_CARD] = 1;
    field_count[COWL_OT_CE_DATA_HAS_VALUE] = 2;
    field_count[COWL_OT_CE_OBJ_INTERSECT] = 1;
    field_count[COWL_OT_CE_OBJ_UNION] = 1;
    field_count[COWL_OT_CE_OBJ_COMPL] = 1;
    field_count[COWL_OT_CE_OBJ_ONE_OF] = 1;
    field_count[COWL_OT_DR_DATATYPE_RESTR] = 2;
    field_count[COWL_OT_DR_DATA_INTERSECT] = 1;
    field_count[COWL_OT_DR_DATA_UNION] = 1;
    field_count[COWL_OT_DR_DATA_COMPL] = 1;
    field_count[COWL_OT_DR_DATA_ONE_OF] = 1;
    field_count[COWL_OT_OPE_INV_OBJ_PROP] = 1;
    return COWL_OK;
}

void cowl_object_api_deinit(void) {}

CowlAny *cowl_retain(CowlAny *object) {
    return cowl_object_incr_ref(object);
}

static inline void release_impl(CowlObjectType type, CowlAny *object) {
    ulib_byte count = field_count[type];
    if (cowl_has_opt_field(object)) ++count;
    for (ulib_byte i = 0; i < count; ++i) {
        cowl_release(cowl_get_field(object, i));
    }
    ulib_free(object);
}

void cowl_release(CowlAny *object) {
    if (!object || cowl_object_decr_ref(object)) return;
    CowlObjectType type = cowl_get_type(object);

    switch (type) {
        case COWL_OT_STRING: cowl_string_free(object); return;
        case COWL_OT_VECTOR: cowl_vector_free(object); return;
        case COWL_OT_TABLE: cowl_table_free(object); return;
        case COWL_OT_IRI: cowl_iri_free(object); return;
        case COWL_OT_LITERAL: cowl_literal_free(object); return;
        case COWL_OT_ONTOLOGY: cowl_ontology_free(object); return;
        case COWL_OT_ISTREAM: cowl_istream_free(object); return;
        case COWL_OT_OSTREAM: cowl_ostream_free(object); return;
        case COWL_OT_MANAGER: cowl_manager_free(object); return;
        case COWL_OT_I_ANONYMOUS: cowl_anon_ind_free(object); return;
        case COWL_OT_ANNOT_PROP:
        case COWL_OT_CE_CLASS:
        case COWL_OT_DPE_DATA_PROP:
        case COWL_OT_DR_DATATYPE:
        case COWL_OT_I_NAMED:
        case COWL_OT_OPE_OBJ_PROP: cowl_entity_free(object); return;
        default: release_impl(type, object); return;
    }
}

CowlObjectType cowl_get_type(CowlAny *object) {
    return cowl_object_flags_get_type(((CowlObject *)object)->flags);
}

bool cowl_is_entity(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    return (type == COWL_OT_CE_CLASS || type == COWL_OT_DR_DATATYPE ||
            type == COWL_OT_OPE_OBJ_PROP || type == COWL_OT_DPE_DATA_PROP ||
            type == COWL_OT_ANNOT_PROP || type == COWL_OT_I_NAMED);
}

bool cowl_is_axiom(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    return type >= COWL_OT_FIRST_A && type <= COWL_OT_LAST_A;
}

bool cowl_is_cls_exp(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    return type >= COWL_OT_FIRST_CE && type <= COWL_OT_LAST_CE;
}

bool cowl_is_obj_prop_exp(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    return type >= COWL_OT_FIRST_OPE && type <= COWL_OT_LAST_OPE;
}

bool cowl_is_data_prop_exp(CowlAny *object) {
    return cowl_get_type(object) == COWL_OT_DPE_DATA_PROP;
}

bool cowl_is_individual(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    return type >= COWL_OT_FIRST_I && type <= COWL_OT_LAST_I;
}

bool cowl_is_data_range(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    return type >= COWL_OT_FIRST_DR && type <= COWL_OT_LAST_DR;
}

CowlIRI *cowl_get_iri(CowlAny *object) {
    return cowl_is_entity(object) ? cowl_entity_get_iri(object) : NULL;
}

static cowl_ret cowl_write_debug_impl(UOStream *stream, CowlAny *object) {
    return cowl_ret_from_ustream(cowl_write_debug(stream, object));
}

static CowlString *cowl_to_string_impl(CowlAny *object, cowl_ret (*fun)(UOStream *, CowlAny *)) {
    UOStream stream;
    UStrBuf buf = ustrbuf();
    if (uostream_to_strbuf(&stream, &buf) || fun(&stream, object)) goto err;

    CowlString *string = cowl_string(ustrbuf_to_ustring(&buf));
    uostream_deinit(&stream);
    return string;

err:
    uostream_deinit(&stream);
    ustrbuf_deinit(&buf);
    return NULL;
}

CowlString *cowl_to_string(CowlAny *object) {
    return cowl_to_string_impl(object, cowl_write);
}

CowlString *cowl_to_debug_string(CowlAny *object) {
    return cowl_to_string_impl(object, cowl_write_debug_impl);
}

static inline bool equals_impl(CowlObjectType type, CowlAny *lhs, CowlAny *rhs) {
    ulib_byte count = field_count[type];
    if (!count) return lhs == rhs;

    for (ulib_byte i = 0; i < count; ++i) {
        if (!cowl_equals(cowl_get_field(lhs, i), cowl_get_field(rhs, i))) return false;
    }

    CowlAny *lhs_opt = cowl_get_opt_field(lhs), *rhs_opt = cowl_get_opt_field(rhs);
    if (lhs_opt == rhs_opt) return true;
    if (!(lhs_opt && rhs_opt)) return false;

    return cowl_equals(lhs_opt, rhs_opt);
}

bool cowl_equals(CowlAny *lhs, CowlAny *rhs) {
    CowlObjectType type = cowl_get_type(lhs);
    if (type != cowl_get_type(rhs)) return false;

    switch (type) {
        case COWL_OT_STRING: return cowl_string_equals(lhs, rhs);
        case COWL_OT_VECTOR: return cowl_vector_equals(lhs, rhs);
        case COWL_OT_TABLE: return cowl_table_equals(lhs, rhs);
        case COWL_OT_LITERAL: return cowl_literal_equals(lhs, rhs);
        case COWL_OT_ONTOLOGY: return cowl_ontology_equals(lhs, rhs);

        case COWL_OT_IRI:
        case COWL_OT_ANNOT_PROP:
        case COWL_OT_CE_CLASS:
        case COWL_OT_DPE_DATA_PROP:
        case COWL_OT_DR_DATATYPE:
        case COWL_OT_I_NAMED:
        case COWL_OT_I_ANONYMOUS:
        case COWL_OT_OPE_OBJ_PROP: return cowl_primitive_equals(lhs, rhs);

        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD:
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD:
            if (cowl_get_uint_field(lhs) != cowl_get_uint_field(rhs)) return false;
            // Fallthrough
        default: return equals_impl(type, lhs, rhs);
    }
}

bool cowl_equals_iri_string(CowlAny *object, UString iri_str) {
    CowlIRI *iri = cowl_get_iri(object);
    if (!iri) return false;

    CowlString *ns = cowl_iri_get_ns(iri), *rem = cowl_iri_get_rem(iri);
    ulib_uint ns_len = cowl_string_get_length(ns), rem_len = cowl_string_get_length(rem);

    if (ustring_length(iri_str) != ns_len + rem_len) return false;
    if (!ustring_ends_with(iri_str, *cowl_string_get_raw(rem))) return false;
    return ustring_starts_with(iri_str, *cowl_string_get_raw(ns));
}

static inline ulib_uint hash_impl(CowlObjectType type, CowlAny *object) {
    ulib_byte count = field_count[type];
    if (!count) return uhash_ptr_hash(object);

    ulib_uint hash = uhash_combine_hash(6151U, type);

    for (ulib_byte i = 0; i < count; ++i) {
        ulib_uint lhash = cowl_hash(cowl_get_field(object, i));
        hash = uhash_combine_hash(hash, lhash);
    }

    return hash;
}

static inline ulib_uint hash_impl_uint(CowlObjectType type, CowlAny *object) {
    ulib_uint hash = hash_impl(type, object);
    return uhash_combine_hash(hash, cowl_get_uint_field(object));
}

ulib_uint cowl_hash(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    switch (type) {
        case COWL_OT_STRING: return cowl_string_hash(object);
        case COWL_OT_VECTOR: return cowl_vector_hash(object);
        case COWL_OT_TABLE: return cowl_table_hash(object);
        case COWL_OT_LITERAL: return cowl_literal_hash(object);
        case COWL_OT_ONTOLOGY: return cowl_ontology_hash(object);

        case COWL_OT_IRI:
        case COWL_OT_ANNOT_PROP:
        case COWL_OT_CE_CLASS:
        case COWL_OT_DPE_DATA_PROP:
        case COWL_OT_DR_DATATYPE:
        case COWL_OT_I_NAMED:
        case COWL_OT_I_ANONYMOUS:
        case COWL_OT_OPE_OBJ_PROP: return cowl_primitive_hash(object);

        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD:
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: return hash_impl_uint(type, object);
        default: return hash_impl(type, object);
    }
}

static inline bool
iterate_pf(CowlPrimitiveFlags type, CowlAny *object, CowlPrimitiveFlags flags, CowlIterator *iter) {
    return ubit_is_set(COWL_PF, flags, type) ? cowl_iterate(iter, object) : true;
}

static inline bool
iterate_impl(CowlObjectType type, CowlAny *object, CowlPrimitiveFlags flags, CowlIterator *iter) {
    ulib_byte count = field_count[type];
    if (!count) return true;

    for (ulib_byte i = 0; i < count; ++i) {
        if (!cowl_iterate_primitives(cowl_get_field(object, i), flags, iter)) return false;
    }

    CowlAny *opt = cowl_get_opt_field(object);
    return opt ? cowl_iterate_primitives(opt, flags, iter) : true;
}

bool cowl_iterate_primitives(CowlAny *object, CowlPrimitiveFlags flags, CowlIterator *iter) {
    CowlObjectType type = cowl_get_type(object);
    switch (type) {
        case COWL_OT_VECTOR: return cowl_vector_iterate_primitives(object, flags, iter);
        case COWL_OT_TABLE: return cowl_table_iterate_primitives(object, flags, iter);
        case COWL_OT_IRI: return iterate_pf(COWL_PF_IRI, object, flags, iter);
        case COWL_OT_LITERAL: return cowl_literal_iterate_primitives(object, flags, iter);
        case COWL_OT_ANNOT_PROP: return iterate_pf(COWL_PF_ANNOT_PROP, object, flags, iter);
        case COWL_OT_CE_CLASS: return iterate_pf(COWL_PF_CLASS, object, flags, iter);
        case COWL_OT_DPE_DATA_PROP: return iterate_pf(COWL_PF_DATA_PROP, object, flags, iter);
        case COWL_OT_DR_DATATYPE: return iterate_pf(COWL_PF_DATATYPE, object, flags, iter);
        case COWL_OT_I_NAMED: return iterate_pf(COWL_PF_NAMED_IND, object, flags, iter);
        case COWL_OT_I_ANONYMOUS: return iterate_pf(COWL_PF_ANON_IND, object, flags, iter);
        case COWL_OT_OPE_OBJ_PROP: return iterate_pf(COWL_PF_OBJ_PROP, object, flags, iter);
        case COWL_OT_ONTOLOGY: return cowl_ontology_iterate_primitives(object, flags, iter, false);
        default: return iterate_impl(type, object, flags, iter);
    }
}

CowlAny *cowl_get_impl(CowlObjectType type, CowlAny *fields[], CowlAny *opt) {
    ulib_byte count = field_count[type];
    CowlComposite *o = ulib_malloc(sizeof(*o) + (opt ? count + 1 : count) * sizeof(*o->fields));
    if (!o) return NULL;

    o->super = COWL_OBJECT_BIT_INIT(type, opt);
    for (ulib_byte i = 0; i < count; ++i) {
        o->fields[i].obj = cowl_retain(fields[i]);
    }
    if (opt) o->fields[count].obj = cowl_retain(opt);

    return o;
}

CowlAny *cowl_get_impl_annot(CowlObjectType type, CowlAny *fields[], CowlVector *annot) {
    if (annot && !cowl_vector_count(annot)) annot = NULL;
    return cowl_get_impl(type, fields, annot);
}

CowlAny *cowl_get_impl_uint(CowlObjectType type, CowlAny *fields[], ulib_uint val, CowlAny *opt) {
    ulib_byte count = field_count[type];
    ulib_byte data_size = opt ? count + 2 : count + 1;
    CowlComposite *obj = ulib_malloc(sizeof(*obj) + data_size * sizeof(*obj->fields));
    if (!obj) return NULL;

    obj->super = COWL_OBJECT_BIT_INIT(type, opt);
    for (ulib_byte i = 0; i < count; ++i) {
        obj->fields[i].obj = cowl_retain(fields[i]);
    }

    if (opt) {
        obj->fields[count].obj = cowl_retain(opt);
        obj->fields[count + 1].uint = val;
    } else {
        obj->fields[count].uint = val;
    }

    return obj;
}

void cowl_release_all_impl(CowlAny **objects) {
    while (*objects) {
        cowl_release(*(objects++));
    }
}

ulib_uint cowl_get_field_count(CowlAny *object) {
    return field_count[cowl_get_type(object)];
}

CowlAny *cowl_get_field(CowlAny *object, ulib_uint index) {
    return ((CowlComposite *)object)->fields[index].obj;
}

bool cowl_has_opt_field(CowlAny *object) {
    return cowl_object_bit_get(object);
}

CowlAny *cowl_get_opt_field(CowlAny *object) {
    if (!cowl_object_bit_get(object)) return NULL;
    return cowl_get_field(object, field_count[cowl_get_type(object)]);
}

ulib_uint cowl_get_uint_field(CowlAny *object) {
    ulib_byte idx = field_count[cowl_get_type(object)];
    if (cowl_has_opt_field(object)) idx++;
    return ((CowlComposite *)object)->fields[idx].uint;
}
