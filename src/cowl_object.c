/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2020-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_object_private.h"
#include "cowl_private.h"

ulib_byte composite_fields[COWL_OT_COUNT] = {0};

cowl_ret cowl_object_api_init(void) {
    composite_fields[COWL_OT_FACET_RESTR] = 2;
    composite_fields[COWL_OT_ANNOTATION] = 2;
    composite_fields[COWL_OT_A_DECL] = 1;
    composite_fields[COWL_OT_A_DATATYPE_DEF] = 2;
    composite_fields[COWL_OT_A_SUB_CLASS] = 2;
    composite_fields[COWL_OT_A_EQUIV_CLASSES] = 1;
    composite_fields[COWL_OT_A_DISJ_CLASSES] = 1;
    composite_fields[COWL_OT_A_DISJ_UNION] = 2;
    composite_fields[COWL_OT_A_CLASS_ASSERT] = 2;
    composite_fields[COWL_OT_A_SAME_IND] = 1;
    composite_fields[COWL_OT_A_DIFF_IND] = 1;
    composite_fields[COWL_OT_A_OBJ_PROP_ASSERT] = 3;
    composite_fields[COWL_OT_A_NEG_OBJ_PROP_ASSERT] = 3;
    composite_fields[COWL_OT_A_DATA_PROP_ASSERT] = 3;
    composite_fields[COWL_OT_A_NEG_DATA_PROP_ASSERT] = 3;
    composite_fields[COWL_OT_A_SUB_OBJ_PROP] = 2;
    composite_fields[COWL_OT_A_INV_OBJ_PROP] = 2;
    composite_fields[COWL_OT_A_EQUIV_OBJ_PROP] = 1;
    composite_fields[COWL_OT_A_DISJ_OBJ_PROP] = 1;
    composite_fields[COWL_OT_A_FUNC_OBJ_PROP] = 1;
    composite_fields[COWL_OT_A_INV_FUNC_OBJ_PROP] = 1;
    composite_fields[COWL_OT_A_SYMM_OBJ_PROP] = 1;
    composite_fields[COWL_OT_A_ASYMM_OBJ_PROP] = 1;
    composite_fields[COWL_OT_A_REFL_OBJ_PROP] = 1;
    composite_fields[COWL_OT_A_IRREFL_OBJ_PROP] = 1;
    composite_fields[COWL_OT_A_TRANS_OBJ_PROP] = 1;
    composite_fields[COWL_OT_A_OBJ_PROP_DOMAIN] = 2;
    composite_fields[COWL_OT_A_OBJ_PROP_RANGE] = 2;
    composite_fields[COWL_OT_A_SUB_DATA_PROP] = 2;
    composite_fields[COWL_OT_A_EQUIV_DATA_PROP] = 1;
    composite_fields[COWL_OT_A_DISJ_DATA_PROP] = 1;
    composite_fields[COWL_OT_A_FUNC_DATA_PROP] = 1;
    composite_fields[COWL_OT_A_DATA_PROP_DOMAIN] = 2;
    composite_fields[COWL_OT_A_DATA_PROP_RANGE] = 2;
    composite_fields[COWL_OT_A_HAS_KEY] = 3;
    composite_fields[COWL_OT_A_ANNOT_ASSERT] = 3;
    composite_fields[COWL_OT_A_SUB_ANNOT_PROP] = 2;
    composite_fields[COWL_OT_A_ANNOT_PROP_DOMAIN] = 2;
    composite_fields[COWL_OT_A_ANNOT_PROP_RANGE] = 2;
    composite_fields[COWL_OT_CE_OBJ_SOME] = 1;
    composite_fields[COWL_OT_CE_OBJ_ALL] = 1;
    composite_fields[COWL_OT_CE_OBJ_MIN_CARD] = 1;
    composite_fields[COWL_OT_CE_OBJ_MAX_CARD] = 1;
    composite_fields[COWL_OT_CE_OBJ_EXACT_CARD] = 1;
    composite_fields[COWL_OT_CE_OBJ_HAS_VALUE] = 2;
    composite_fields[COWL_OT_CE_OBJ_HAS_SELF] = 1;
    composite_fields[COWL_OT_CE_DATA_SOME] = 2;
    composite_fields[COWL_OT_CE_DATA_ALL] = 2;
    composite_fields[COWL_OT_CE_DATA_MIN_CARD] = 1;
    composite_fields[COWL_OT_CE_DATA_MAX_CARD] = 1;
    composite_fields[COWL_OT_CE_DATA_EXACT_CARD] = 1;
    composite_fields[COWL_OT_CE_DATA_HAS_VALUE] = 2;
    composite_fields[COWL_OT_CE_OBJ_INTERSECT] = 1;
    composite_fields[COWL_OT_CE_OBJ_UNION] = 1;
    composite_fields[COWL_OT_CE_OBJ_COMPL] = 1;
    composite_fields[COWL_OT_CE_OBJ_ONE_OF] = 1;
    composite_fields[COWL_OT_DR_DATATYPE_RESTR] = 2;
    composite_fields[COWL_OT_DR_DATA_INTERSECT] = 1;
    composite_fields[COWL_OT_DR_DATA_UNION] = 1;
    composite_fields[COWL_OT_DR_DATA_COMPL] = 1;
    composite_fields[COWL_OT_DR_DATA_ONE_OF] = 1;
    composite_fields[COWL_OT_OPE_INV_OBJ_PROP] = 1;
    return COWL_OK;
}

void cowl_object_api_deinit(void) { /* No-op */ }

CowlAny* cowl_retain(CowlAny *object) {
    return cowl_object_incr_ref(object);
}

void cowl_release(CowlAny *object) {
    if (!object) return;

    #define GEN_RELEASE(UC, LC) cowl_##LC##_release((Cowl##UC *)object); break
    #define GEN_RELEASE_AXIOM(UC, LC) cowl_##LC##_axiom_release((Cowl##UC##Axiom *)object); break

    switch (cowl_get_type(object)) {
        case COWL_OT_STRING: GEN_RELEASE(String, string);
        case COWL_OT_VECTOR: GEN_RELEASE(Vector, vector);
        case COWL_OT_TABLE: GEN_RELEASE(Table, table);
        case COWL_OT_IRI: GEN_RELEASE(IRI, iri);
        case COWL_OT_LITERAL: GEN_RELEASE(Literal, literal);
        case COWL_OT_FACET_RESTR: GEN_RELEASE(FacetRestr, facet_restr);
        case COWL_OT_ONTOLOGY: GEN_RELEASE(Ontology, ontology);
        case COWL_OT_STREAM: GEN_RELEASE(Stream, stream);
        case COWL_OT_MANAGER: GEN_RELEASE(Manager, manager);
        case COWL_OT_ANNOTATION: GEN_RELEASE(Annotation, annotation);
        case COWL_OT_ANNOT_PROP: GEN_RELEASE(AnnotProp, annot_prop);
        case COWL_OT_A_DECL: GEN_RELEASE_AXIOM(Decl, decl);
        case COWL_OT_A_DATATYPE_DEF: GEN_RELEASE_AXIOM(DatatypeDef, datatype_def);
        case COWL_OT_A_SUB_CLASS: GEN_RELEASE_AXIOM(SubCls, sub_cls);
        case COWL_OT_A_EQUIV_CLASSES:
        case COWL_OT_A_DISJ_CLASSES: GEN_RELEASE_AXIOM(NAryCls, nary_cls);
        case COWL_OT_A_DISJ_UNION: GEN_RELEASE_AXIOM(DisjUnion, disj_union);
        case COWL_OT_A_CLASS_ASSERT: GEN_RELEASE_AXIOM(ClsAssert, cls_assert);
        case COWL_OT_A_SAME_IND:
        case COWL_OT_A_DIFF_IND: GEN_RELEASE_AXIOM(NAryInd, nary_ind);
        case COWL_OT_A_OBJ_PROP_ASSERT:
        case COWL_OT_A_NEG_OBJ_PROP_ASSERT: GEN_RELEASE_AXIOM(ObjPropAssert, obj_prop_assert);
        case COWL_OT_A_DATA_PROP_ASSERT:
        case COWL_OT_A_NEG_DATA_PROP_ASSERT: GEN_RELEASE_AXIOM(DataPropAssert, data_prop_assert);
        case COWL_OT_A_SUB_OBJ_PROP: GEN_RELEASE_AXIOM(SubObjProp, sub_obj_prop);
        case COWL_OT_A_INV_OBJ_PROP: GEN_RELEASE_AXIOM(InvObjProp, inv_obj_prop);
        case COWL_OT_A_EQUIV_OBJ_PROP:
        case COWL_OT_A_DISJ_OBJ_PROP: GEN_RELEASE_AXIOM(NAryObjProp, nary_obj_prop);
        case COWL_OT_A_FUNC_OBJ_PROP:
        case COWL_OT_A_INV_FUNC_OBJ_PROP:
        case COWL_OT_A_SYMM_OBJ_PROP:
        case COWL_OT_A_ASYMM_OBJ_PROP:
        case COWL_OT_A_TRANS_OBJ_PROP:
        case COWL_OT_A_REFL_OBJ_PROP:
        case COWL_OT_A_IRREFL_OBJ_PROP: GEN_RELEASE_AXIOM(ObjPropChar, obj_prop_char);
        case COWL_OT_A_OBJ_PROP_DOMAIN: GEN_RELEASE_AXIOM(ObjPropDomain, obj_prop_domain);
        case COWL_OT_A_OBJ_PROP_RANGE: GEN_RELEASE_AXIOM(ObjPropRange, obj_prop_range);
        case COWL_OT_A_SUB_DATA_PROP: GEN_RELEASE_AXIOM(SubDataProp, sub_data_prop);
        case COWL_OT_A_EQUIV_DATA_PROP:
        case COWL_OT_A_DISJ_DATA_PROP: GEN_RELEASE_AXIOM(NAryDataProp, nary_data_prop);
        case COWL_OT_A_FUNC_DATA_PROP: GEN_RELEASE_AXIOM(FuncDataProp, func_data_prop);
        case COWL_OT_A_DATA_PROP_DOMAIN: GEN_RELEASE_AXIOM(DataPropDomain, data_prop_domain);
        case COWL_OT_A_DATA_PROP_RANGE: GEN_RELEASE_AXIOM(DataPropRange, data_prop_range);
        case COWL_OT_A_HAS_KEY: GEN_RELEASE_AXIOM(HasKey, has_key);
        case COWL_OT_A_ANNOT_ASSERT: GEN_RELEASE_AXIOM(AnnotAssert, annot_assert);
        case COWL_OT_A_SUB_ANNOT_PROP: GEN_RELEASE_AXIOM(SubAnnotProp, sub_annot_prop);
        case COWL_OT_A_ANNOT_PROP_DOMAIN: GEN_RELEASE_AXIOM(AnnotPropDomain, annot_prop_domain);
        case COWL_OT_A_ANNOT_PROP_RANGE: GEN_RELEASE_AXIOM(AnnotPropRange, annot_prop_range);
        case COWL_OT_CE_CLASS: GEN_RELEASE(Class, class);
        case COWL_OT_CE_OBJ_SOME:
        case COWL_OT_CE_OBJ_ALL: GEN_RELEASE(ObjQuant, obj_quant);
        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD: GEN_RELEASE(ObjCard, obj_card);
        case COWL_OT_CE_OBJ_HAS_VALUE: GEN_RELEASE(ObjHasValue, obj_has_value);
        case COWL_OT_CE_OBJ_HAS_SELF: GEN_RELEASE(ObjHasSelf, obj_has_self);
        case COWL_OT_CE_DATA_SOME:
        case COWL_OT_CE_DATA_ALL: GEN_RELEASE(DataQuant, data_quant);
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: GEN_RELEASE(DataCard, data_card);
        case COWL_OT_CE_DATA_HAS_VALUE: GEN_RELEASE(DataHasValue, data_has_value);
        case COWL_OT_CE_OBJ_INTERSECT:
        case COWL_OT_CE_OBJ_UNION: GEN_RELEASE(NAryBool, nary_bool);
        case COWL_OT_CE_OBJ_COMPL: GEN_RELEASE(ObjCompl, obj_compl);
        case COWL_OT_CE_OBJ_ONE_OF: GEN_RELEASE(ObjOneOf, obj_one_of);
        case COWL_OT_DPE_DATA_PROP: GEN_RELEASE(DataProp, data_prop);
        case COWL_OT_DR_DATATYPE: GEN_RELEASE(Datatype, datatype);
        case COWL_OT_DR_DATATYPE_RESTR: GEN_RELEASE(DatatypeRestr, datatype_restr);
        case COWL_OT_DR_DATA_INTERSECT:
        case COWL_OT_DR_DATA_UNION: GEN_RELEASE(NAryData, nary_data);
        case COWL_OT_DR_DATA_COMPL: GEN_RELEASE(DataCompl, data_compl);
        case COWL_OT_DR_DATA_ONE_OF: GEN_RELEASE(DataOneOf, data_one_of);
        case COWL_OT_I_ANONYMOUS: GEN_RELEASE(AnonInd, anon_ind);
        case COWL_OT_I_NAMED: GEN_RELEASE(NamedInd, named_ind);
        case COWL_OT_OPE_OBJ_PROP: GEN_RELEASE(ObjProp, obj_prop);
        case COWL_OT_OPE_INV_OBJ_PROP: GEN_RELEASE(InvObjProp, inv_obj_prop);
        case COWL_OT_COUNT: break;
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

CowlIRI* cowl_get_iri(CowlAny *object) {
    return cowl_is_entity(object) ? cowl_entity_get_iri(object) : NULL;
}

static cowl_ret cowl_write_debug_impl(UOStream *stream, CowlAny *object) {
    return cowl_ret_from_ustream(cowl_write_debug(stream, object));
}

static CowlString* cowl_to_string_impl(CowlAny *object, cowl_ret (*fun)(UOStream *, CowlAny *)) {
    UOStream stream;
    UStrBuf buf = ustrbuf();
    if (uostream_to_strbuf(&stream, &buf) ||
        fun(&stream, object)) goto err;

    CowlString *string = cowl_string(ustrbuf_to_ustring(&buf));
    uostream_deinit(&stream);
    return string;

err:
    uostream_deinit(&stream);
    ustrbuf_deinit(&buf);
    return NULL;
}

CowlString* cowl_to_string(CowlAny *object) {
    return cowl_to_string_impl(object, cowl_write);
}

CowlString* cowl_to_debug_string(CowlAny *object) {
    return cowl_to_string_impl(object, cowl_write_debug_impl);
}

bool cowl_equals(CowlAny *lhs, CowlAny *rhs) {
    CowlObjectType type = cowl_get_type(lhs);
    if (type != cowl_get_type(rhs)) return false;

    #define GEN_EQUALS(UC, LC) \
        return cowl_##LC##_equals((Cowl##UC *)lhs, (Cowl##UC *)rhs)
    #define GEN_EQUALS_AXIOM(UC, LC) \
        return cowl_##LC##_axiom_equals((Cowl##UC##Axiom *)lhs, (Cowl##UC##Axiom *)rhs)

    switch (type) {
        case COWL_OT_STRING: GEN_EQUALS(String, string);
        case COWL_OT_VECTOR: GEN_EQUALS(Vector, vector);
        case COWL_OT_TABLE: GEN_EQUALS(Table, table);
        case COWL_OT_IRI: GEN_EQUALS(IRI, iri);
        case COWL_OT_LITERAL: GEN_EQUALS(Literal, literal);
        case COWL_OT_FACET_RESTR: GEN_EQUALS(FacetRestr, facet_restr);
        case COWL_OT_ONTOLOGY: GEN_EQUALS(Ontology, ontology);
        case COWL_OT_ANNOTATION: GEN_EQUALS(Annotation, annotation);
        case COWL_OT_ANNOT_PROP: GEN_EQUALS(AnnotProp, annot_prop);
        case COWL_OT_A_DECL: GEN_EQUALS_AXIOM(Decl, decl);
        case COWL_OT_A_DATATYPE_DEF: GEN_EQUALS_AXIOM(DatatypeDef, datatype_def);
        case COWL_OT_A_SUB_CLASS: GEN_EQUALS_AXIOM(SubCls, sub_cls);
        case COWL_OT_A_EQUIV_CLASSES:
        case COWL_OT_A_DISJ_CLASSES: GEN_EQUALS_AXIOM(NAryCls, nary_cls);
        case COWL_OT_A_DISJ_UNION: GEN_EQUALS_AXIOM(DisjUnion, disj_union);
        case COWL_OT_A_CLASS_ASSERT: GEN_EQUALS_AXIOM(ClsAssert, cls_assert);
        case COWL_OT_A_SAME_IND:
        case COWL_OT_A_DIFF_IND: GEN_EQUALS_AXIOM(NAryInd, nary_ind);
        case COWL_OT_A_OBJ_PROP_ASSERT:
        case COWL_OT_A_NEG_OBJ_PROP_ASSERT: GEN_EQUALS_AXIOM(ObjPropAssert, obj_prop_assert);
        case COWL_OT_A_DATA_PROP_ASSERT:
        case COWL_OT_A_NEG_DATA_PROP_ASSERT: GEN_EQUALS_AXIOM(DataPropAssert, data_prop_assert);
        case COWL_OT_A_SUB_OBJ_PROP: GEN_EQUALS_AXIOM(SubObjProp, sub_obj_prop);
        case COWL_OT_A_INV_OBJ_PROP: GEN_EQUALS_AXIOM(InvObjProp, inv_obj_prop);
        case COWL_OT_A_EQUIV_OBJ_PROP:
        case COWL_OT_A_DISJ_OBJ_PROP: GEN_EQUALS_AXIOM(NAryObjProp, nary_obj_prop);
        case COWL_OT_A_FUNC_OBJ_PROP:
        case COWL_OT_A_INV_FUNC_OBJ_PROP:
        case COWL_OT_A_SYMM_OBJ_PROP:
        case COWL_OT_A_ASYMM_OBJ_PROP:
        case COWL_OT_A_TRANS_OBJ_PROP:
        case COWL_OT_A_REFL_OBJ_PROP:
        case COWL_OT_A_IRREFL_OBJ_PROP: GEN_EQUALS_AXIOM(ObjPropChar, obj_prop_char);
        case COWL_OT_A_OBJ_PROP_DOMAIN: GEN_EQUALS_AXIOM(ObjPropDomain, obj_prop_domain);
        case COWL_OT_A_OBJ_PROP_RANGE: GEN_EQUALS_AXIOM(ObjPropRange, obj_prop_range);
        case COWL_OT_A_SUB_DATA_PROP: GEN_EQUALS_AXIOM(SubDataProp, sub_data_prop);
        case COWL_OT_A_EQUIV_DATA_PROP:
        case COWL_OT_A_DISJ_DATA_PROP: GEN_EQUALS_AXIOM(NAryDataProp, nary_data_prop);
        case COWL_OT_A_FUNC_DATA_PROP: GEN_EQUALS_AXIOM(FuncDataProp, func_data_prop);
        case COWL_OT_A_DATA_PROP_DOMAIN: GEN_EQUALS_AXIOM(DataPropDomain, data_prop_domain);
        case COWL_OT_A_DATA_PROP_RANGE: GEN_EQUALS_AXIOM(DataPropRange, data_prop_range);
        case COWL_OT_A_HAS_KEY: GEN_EQUALS_AXIOM(HasKey, has_key);
        case COWL_OT_A_ANNOT_ASSERT: GEN_EQUALS_AXIOM(AnnotAssert, annot_assert);
        case COWL_OT_A_SUB_ANNOT_PROP: GEN_EQUALS_AXIOM(SubAnnotProp, sub_annot_prop);
        case COWL_OT_A_ANNOT_PROP_DOMAIN: GEN_EQUALS_AXIOM(AnnotPropDomain, annot_prop_domain);
        case COWL_OT_A_ANNOT_PROP_RANGE: GEN_EQUALS_AXIOM(AnnotPropRange, annot_prop_range);
        case COWL_OT_CE_CLASS: GEN_EQUALS(Class, class);
        case COWL_OT_CE_OBJ_SOME:
        case COWL_OT_CE_OBJ_ALL: GEN_EQUALS(ObjQuant, obj_quant);
        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD: GEN_EQUALS(ObjCard, obj_card);
        case COWL_OT_CE_OBJ_HAS_VALUE: GEN_EQUALS(ObjHasValue, obj_has_value);
        case COWL_OT_CE_OBJ_HAS_SELF: GEN_EQUALS(ObjHasSelf, obj_has_self);
        case COWL_OT_CE_DATA_SOME:
        case COWL_OT_CE_DATA_ALL: GEN_EQUALS(DataQuant, data_quant);
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: GEN_EQUALS(DataCard, data_card);
        case COWL_OT_CE_DATA_HAS_VALUE: GEN_EQUALS(DataHasValue, data_has_value);
        case COWL_OT_CE_OBJ_INTERSECT:
        case COWL_OT_CE_OBJ_UNION: GEN_EQUALS(NAryBool, nary_bool);
        case COWL_OT_CE_OBJ_COMPL: GEN_EQUALS(ObjCompl, obj_compl);
        case COWL_OT_CE_OBJ_ONE_OF: GEN_EQUALS(ObjOneOf, obj_one_of);
        case COWL_OT_DPE_DATA_PROP: GEN_EQUALS(DataProp, data_prop);
        case COWL_OT_DR_DATATYPE: GEN_EQUALS(Datatype, datatype);
        case COWL_OT_DR_DATATYPE_RESTR: GEN_EQUALS(DatatypeRestr, datatype_restr);
        case COWL_OT_DR_DATA_INTERSECT:
        case COWL_OT_DR_DATA_UNION: GEN_EQUALS(NAryData, nary_data);
        case COWL_OT_DR_DATA_COMPL: GEN_EQUALS(DataCompl, data_compl);
        case COWL_OT_DR_DATA_ONE_OF: GEN_EQUALS(DataOneOf, data_one_of);
        case COWL_OT_I_ANONYMOUS: GEN_EQUALS(AnonInd, anon_ind);
        case COWL_OT_I_NAMED: GEN_EQUALS(NamedInd, named_ind);
        case COWL_OT_OPE_OBJ_PROP: GEN_EQUALS(ObjProp, obj_prop);
        case COWL_OT_OPE_INV_OBJ_PROP: GEN_EQUALS(InvObjProp, inv_obj_prop);
        default: return lhs == rhs;
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

ulib_uint cowl_hash(CowlAny *object) {
    #define GEN_HASH(UC, LC) return cowl_##LC##_hash((Cowl##UC *)object)
    #define GEN_HASH_AXIOM(UC, LC) return cowl_##LC##_axiom_hash((Cowl##UC##Axiom *)object)

    switch (cowl_get_type(object)) {
        case COWL_OT_STRING: GEN_HASH(String, string);
        case COWL_OT_VECTOR: GEN_HASH(Vector, vector);
        case COWL_OT_TABLE: GEN_HASH(Table, table);
        case COWL_OT_IRI: GEN_HASH(IRI, iri);
        case COWL_OT_LITERAL: GEN_HASH(Literal, literal);
        case COWL_OT_FACET_RESTR: GEN_HASH(FacetRestr, facet_restr);
        case COWL_OT_ONTOLOGY: GEN_HASH(Ontology, ontology);
        case COWL_OT_ANNOTATION: GEN_HASH(Annotation, annotation);
        case COWL_OT_ANNOT_PROP: GEN_HASH(AnnotProp, annot_prop);
        case COWL_OT_A_DECL: GEN_HASH_AXIOM(Decl, decl);
        case COWL_OT_A_DATATYPE_DEF: GEN_HASH_AXIOM(DatatypeDef, datatype_def);
        case COWL_OT_A_SUB_CLASS: GEN_HASH_AXIOM(SubCls, sub_cls);
        case COWL_OT_A_EQUIV_CLASSES:
        case COWL_OT_A_DISJ_CLASSES: GEN_HASH_AXIOM(NAryCls, nary_cls);
        case COWL_OT_A_DISJ_UNION: GEN_HASH_AXIOM(DisjUnion, disj_union);
        case COWL_OT_A_CLASS_ASSERT: GEN_HASH_AXIOM(ClsAssert, cls_assert);
        case COWL_OT_A_SAME_IND:
        case COWL_OT_A_DIFF_IND: GEN_HASH_AXIOM(NAryInd, nary_ind);
        case COWL_OT_A_OBJ_PROP_ASSERT:
        case COWL_OT_A_NEG_OBJ_PROP_ASSERT: GEN_HASH_AXIOM(ObjPropAssert, obj_prop_assert);
        case COWL_OT_A_DATA_PROP_ASSERT:
        case COWL_OT_A_NEG_DATA_PROP_ASSERT: GEN_HASH_AXIOM(DataPropAssert, data_prop_assert);
        case COWL_OT_A_SUB_OBJ_PROP: GEN_HASH_AXIOM(SubObjProp, sub_obj_prop);
        case COWL_OT_A_INV_OBJ_PROP: GEN_HASH_AXIOM(InvObjProp, inv_obj_prop);
        case COWL_OT_A_EQUIV_OBJ_PROP:
        case COWL_OT_A_DISJ_OBJ_PROP: GEN_HASH_AXIOM(NAryObjProp, nary_obj_prop);
        case COWL_OT_A_FUNC_OBJ_PROP:
        case COWL_OT_A_INV_FUNC_OBJ_PROP:
        case COWL_OT_A_SYMM_OBJ_PROP:
        case COWL_OT_A_ASYMM_OBJ_PROP:
        case COWL_OT_A_TRANS_OBJ_PROP:
        case COWL_OT_A_REFL_OBJ_PROP:
        case COWL_OT_A_IRREFL_OBJ_PROP: GEN_HASH_AXIOM(ObjPropChar, obj_prop_char);
        case COWL_OT_A_OBJ_PROP_DOMAIN: GEN_HASH_AXIOM(ObjPropDomain, obj_prop_domain);
        case COWL_OT_A_OBJ_PROP_RANGE: GEN_HASH_AXIOM(ObjPropRange, obj_prop_range);
        case COWL_OT_A_SUB_DATA_PROP: GEN_HASH_AXIOM(SubDataProp, sub_data_prop);
        case COWL_OT_A_EQUIV_DATA_PROP:
        case COWL_OT_A_DISJ_DATA_PROP: GEN_HASH_AXIOM(NAryDataProp, nary_data_prop);
        case COWL_OT_A_FUNC_DATA_PROP: GEN_HASH_AXIOM(FuncDataProp, func_data_prop);
        case COWL_OT_A_DATA_PROP_DOMAIN: GEN_HASH_AXIOM(DataPropDomain, data_prop_domain);
        case COWL_OT_A_DATA_PROP_RANGE: GEN_HASH_AXIOM(DataPropRange, data_prop_range);
        case COWL_OT_A_HAS_KEY: GEN_HASH_AXIOM(HasKey, has_key);
        case COWL_OT_A_ANNOT_ASSERT: GEN_HASH_AXIOM(AnnotAssert, annot_assert);
        case COWL_OT_A_SUB_ANNOT_PROP: GEN_HASH_AXIOM(SubAnnotProp, sub_annot_prop);
        case COWL_OT_A_ANNOT_PROP_DOMAIN: GEN_HASH_AXIOM(AnnotPropDomain, annot_prop_domain);
        case COWL_OT_A_ANNOT_PROP_RANGE: GEN_HASH_AXIOM(AnnotPropRange, annot_prop_range);
        case COWL_OT_CE_CLASS: GEN_HASH(Class, class);
        case COWL_OT_CE_OBJ_SOME:
        case COWL_OT_CE_OBJ_ALL: GEN_HASH(ObjQuant, obj_quant);
        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD: GEN_HASH(ObjCard, obj_card);
        case COWL_OT_CE_OBJ_HAS_VALUE: GEN_HASH(ObjHasValue, obj_has_value);
        case COWL_OT_CE_OBJ_HAS_SELF: GEN_HASH(ObjHasSelf, obj_has_self);
        case COWL_OT_CE_DATA_SOME:
        case COWL_OT_CE_DATA_ALL: GEN_HASH(DataQuant, data_quant);
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: GEN_HASH(DataCard, data_card);
        case COWL_OT_CE_DATA_HAS_VALUE: GEN_HASH(DataHasValue, data_has_value);
        case COWL_OT_CE_OBJ_INTERSECT:
        case COWL_OT_CE_OBJ_UNION: GEN_HASH(NAryBool, nary_bool);
        case COWL_OT_CE_OBJ_COMPL: GEN_HASH(ObjCompl, obj_compl);
        case COWL_OT_CE_OBJ_ONE_OF: GEN_HASH(ObjOneOf, obj_one_of);
        case COWL_OT_DPE_DATA_PROP: GEN_HASH(DataProp, data_prop);
        case COWL_OT_DR_DATATYPE: GEN_HASH(Datatype, datatype);
        case COWL_OT_DR_DATATYPE_RESTR: GEN_HASH(DatatypeRestr, datatype_restr);
        case COWL_OT_DR_DATA_INTERSECT:
        case COWL_OT_DR_DATA_UNION: GEN_HASH(NAryData, nary_data);
        case COWL_OT_DR_DATA_COMPL: GEN_HASH(DataCompl, data_compl);
        case COWL_OT_DR_DATA_ONE_OF: GEN_HASH(DataOneOf, data_one_of);
        case COWL_OT_I_ANONYMOUS: GEN_HASH(AnonInd, anon_ind);
        case COWL_OT_I_NAMED: GEN_HASH(NamedInd, named_ind);
        case COWL_OT_OPE_OBJ_PROP: GEN_HASH(ObjProp, obj_prop);
        case COWL_OT_OPE_INV_OBJ_PROP: GEN_HASH(InvObjProp, inv_obj_prop);
        default: return uhash_ptr_hash(object);
    }
}

bool cowl_iterate_primitives(CowlAny *object, CowlPrimitiveFlags flags, CowlIterator *iter) {
    #define GEN_ITER(UC, LC) \
        return cowl_##LC##_iterate_primitives((Cowl##UC *)object, flags, iter)
    #define GEN_ITER_AXIOM(UC, LC) \
        return cowl_##LC##_axiom_iterate_primitives((Cowl##UC##Axiom *)object, flags, iter)
    #define GEN_ITER_PRIMITIVE(TYPE) \
        return ubit_is_set(COWL_PF, flags, COWL_PF_##TYPE) ? cowl_iterate(iter, object) : true

    switch (cowl_get_type(object)) {
        case COWL_OT_VECTOR: GEN_ITER(Vector, vector);
        case COWL_OT_TABLE: GEN_ITER(Table, table);
        case COWL_OT_LITERAL: GEN_ITER(Literal, literal);
        case COWL_OT_FACET_RESTR: GEN_ITER(FacetRestr, facet_restr);
        case COWL_OT_ONTOLOGY: return cowl_ontology_iterate_primitives(object, flags, iter, false);
        case COWL_OT_ANNOTATION: GEN_ITER(Annotation, annotation);
        case COWL_OT_ANNOT_PROP: GEN_ITER_PRIMITIVE(ANNOT_PROP);
        case COWL_OT_A_DECL: GEN_ITER_AXIOM(Decl, decl);
        case COWL_OT_A_DATATYPE_DEF: GEN_ITER_AXIOM(DatatypeDef, datatype_def);
        case COWL_OT_A_SUB_CLASS: GEN_ITER_AXIOM(SubCls, sub_cls);
        case COWL_OT_A_EQUIV_CLASSES:
        case COWL_OT_A_DISJ_CLASSES: GEN_ITER_AXIOM(NAryCls, nary_cls);
        case COWL_OT_A_DISJ_UNION: GEN_ITER_AXIOM(DisjUnion, disj_union);
        case COWL_OT_A_CLASS_ASSERT: GEN_ITER_AXIOM(ClsAssert, cls_assert);
        case COWL_OT_A_SAME_IND:
        case COWL_OT_A_DIFF_IND: GEN_ITER_AXIOM(NAryInd, nary_ind);
        case COWL_OT_A_OBJ_PROP_ASSERT:
        case COWL_OT_A_NEG_OBJ_PROP_ASSERT: GEN_ITER_AXIOM(ObjPropAssert, obj_prop_assert);
        case COWL_OT_A_DATA_PROP_ASSERT:
        case COWL_OT_A_NEG_DATA_PROP_ASSERT: GEN_ITER_AXIOM(DataPropAssert, data_prop_assert);
        case COWL_OT_A_SUB_OBJ_PROP: GEN_ITER_AXIOM(SubObjProp, sub_obj_prop);
        case COWL_OT_A_INV_OBJ_PROP: GEN_ITER_AXIOM(InvObjProp, inv_obj_prop);
        case COWL_OT_A_EQUIV_OBJ_PROP:
        case COWL_OT_A_DISJ_OBJ_PROP: GEN_ITER_AXIOM(NAryObjProp, nary_obj_prop);
        case COWL_OT_A_FUNC_OBJ_PROP:
        case COWL_OT_A_INV_FUNC_OBJ_PROP:
        case COWL_OT_A_SYMM_OBJ_PROP:
        case COWL_OT_A_ASYMM_OBJ_PROP:
        case COWL_OT_A_TRANS_OBJ_PROP:
        case COWL_OT_A_REFL_OBJ_PROP:
        case COWL_OT_A_IRREFL_OBJ_PROP: GEN_ITER_AXIOM(ObjPropChar, obj_prop_char);
        case COWL_OT_A_OBJ_PROP_DOMAIN: GEN_ITER_AXIOM(ObjPropDomain, obj_prop_domain);
        case COWL_OT_A_OBJ_PROP_RANGE: GEN_ITER_AXIOM(ObjPropRange, obj_prop_range);
        case COWL_OT_A_SUB_DATA_PROP: GEN_ITER_AXIOM(SubDataProp, sub_data_prop);
        case COWL_OT_A_EQUIV_DATA_PROP:
        case COWL_OT_A_DISJ_DATA_PROP: GEN_ITER_AXIOM(NAryDataProp, nary_data_prop);
        case COWL_OT_A_FUNC_DATA_PROP: GEN_ITER_AXIOM(FuncDataProp, func_data_prop);
        case COWL_OT_A_DATA_PROP_DOMAIN: GEN_ITER_AXIOM(DataPropDomain, data_prop_domain);
        case COWL_OT_A_DATA_PROP_RANGE: GEN_ITER_AXIOM(DataPropRange, data_prop_range);
        case COWL_OT_A_HAS_KEY: GEN_ITER_AXIOM(HasKey, has_key);
        case COWL_OT_A_ANNOT_ASSERT: GEN_ITER_AXIOM(AnnotAssert, annot_assert);
        case COWL_OT_A_SUB_ANNOT_PROP: GEN_ITER_AXIOM(SubAnnotProp, sub_annot_prop);
        case COWL_OT_A_ANNOT_PROP_DOMAIN: GEN_ITER_AXIOM(AnnotPropDomain, annot_prop_domain);
        case COWL_OT_A_ANNOT_PROP_RANGE: GEN_ITER_AXIOM(AnnotPropRange, annot_prop_range);
        case COWL_OT_CE_CLASS: GEN_ITER_PRIMITIVE(CLASS);
        case COWL_OT_CE_OBJ_SOME:
        case COWL_OT_CE_OBJ_ALL: GEN_ITER(ObjQuant, obj_quant);
        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD: GEN_ITER(ObjCard, obj_card);
        case COWL_OT_CE_OBJ_HAS_VALUE: GEN_ITER(ObjHasValue, obj_has_value);
        case COWL_OT_CE_OBJ_HAS_SELF: GEN_ITER(ObjHasSelf, obj_has_self);
        case COWL_OT_CE_DATA_SOME:
        case COWL_OT_CE_DATA_ALL: GEN_ITER(DataQuant, data_quant);
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: GEN_ITER(DataCard, data_card);
        case COWL_OT_CE_DATA_HAS_VALUE: GEN_ITER(DataHasValue, data_has_value);
        case COWL_OT_CE_OBJ_INTERSECT:
        case COWL_OT_CE_OBJ_UNION: GEN_ITER(NAryBool, nary_bool);
        case COWL_OT_CE_OBJ_COMPL: GEN_ITER(ObjCompl, obj_compl);
        case COWL_OT_CE_OBJ_ONE_OF: GEN_ITER(ObjOneOf, obj_one_of);
        case COWL_OT_DPE_DATA_PROP: GEN_ITER_PRIMITIVE(DATA_PROP);
        case COWL_OT_DR_DATATYPE: GEN_ITER_PRIMITIVE(DATATYPE);
        case COWL_OT_DR_DATATYPE_RESTR: GEN_ITER(DatatypeRestr, datatype_restr);
        case COWL_OT_DR_DATA_INTERSECT:
        case COWL_OT_DR_DATA_UNION: GEN_ITER(NAryData, nary_data);
        case COWL_OT_DR_DATA_COMPL: GEN_ITER(DataCompl, data_compl);
        case COWL_OT_DR_DATA_ONE_OF: GEN_ITER(DataOneOf, data_one_of);
        case COWL_OT_I_ANONYMOUS: GEN_ITER_PRIMITIVE(ANON_IND);
        case COWL_OT_I_NAMED: GEN_ITER_PRIMITIVE(NAMED_IND);
        case COWL_OT_OPE_OBJ_PROP: GEN_ITER_PRIMITIVE(OBJ_PROP);
        case COWL_OT_OPE_INV_OBJ_PROP: GEN_ITER(InvObjProp, inv_obj_prop);
        default: return true;
    }
}

CowlAny* cowl_get_impl(CowlObjectType type, CowlAny *fields[], CowlAny *opt) {
    if (!cowl_enum_value_is_valid(OT, type)) return NULL;

    ulib_byte count = composite_fields[type];
    for (ulib_byte i = 0; i < count; ++i) { if (!fields[i]) return NULL; }

    CowlComposite *obj = ulib_malloc(sizeof(*obj) + (opt ? count + 1 : count) * sizeof(*obj->data));
    if (!obj) return NULL;

    obj->super = COWL_OBJECT_BIT_INIT(type, opt);
    for (ulib_byte i = 0; i < count; ++i) { obj->data[i] = cowl_retain(fields[i]); }
    if (opt) obj->data[count] = cowl_retain(opt);

    return obj;
}

CowlAny* cowl_get_impl_uint(CowlObjectType type, CowlAny *fields[], ulib_uint val, CowlAny *opt) {
    if (!cowl_enum_value_is_valid(OT, type)) return NULL;

    ulib_byte count = composite_fields[type];
    for (ulib_byte i = 0; i < count; ++i) { if (!fields[i]) return NULL; }

    ulib_byte data_size = opt ? count + 2 : count + 1;
    CowlComposite *obj = ulib_malloc(sizeof(*obj) + data_size * sizeof(*obj->data));
    if (!obj) return NULL;

    obj->super = COWL_OBJECT_BIT_INIT(type, opt);
    for (ulib_byte i = 0; i < count; ++i) { obj->data[i] = cowl_retain(fields[i]); }

    if (opt) {
        obj->data[count] = cowl_retain(opt);
        obj->data[count + 1] = (CowlAny *)(uintptr_t)val;
    } else {
        obj->data[count] = (CowlAny *)(uintptr_t)val;
    }

    return obj;
}

void cowl_release_impl(CowlAny *object) {
    if (!object || cowl_object_decr_ref(object)) return;
    ulib_byte count = composite_fields[cowl_get_type(object)];
    if (cowl_has_opt_field(object)) ++count;
    for (ulib_byte i = 0; i < count; ++i) { cowl_release(cowl_get_field(object, i)); }
    ulib_free(object);
}

bool cowl_equals_impl(CowlAny *lhs, CowlAny *rhs) {
    if (lhs == rhs) return true;

    CowlObjectType type = cowl_get_type(lhs);
    if (type != cowl_get_type(rhs)) return false;

    ulib_byte count = composite_fields[cowl_get_type(lhs)];
    for (ulib_byte i = 0; i < count; ++i) {
        if (!cowl_equals(cowl_get_field(lhs, i), cowl_get_field(rhs, i))) return false;
    }

    CowlAny *lhs_opt = cowl_get_opt_field(lhs), *rhs_opt = cowl_get_opt_field(rhs);
    if (lhs_opt == rhs_opt) return true;
    if (!(lhs_opt && rhs_opt)) return false;

    return cowl_equals(lhs_opt, rhs_opt);
}

bool cowl_uint_equals_impl(CowlAny *lhs, CowlAny *rhs) {
    if (!cowl_equals_impl(lhs, rhs)) return false;
    return cowl_get_uint_field(lhs) == cowl_get_uint_field(rhs);
}

ulib_uint cowl_hash_impl(CowlAny *object) {
    CowlObjectType type = cowl_get_type(object);
    ulib_byte count = composite_fields[type];

    ulib_uint hash = uhash_combine_hash(6151U, type);

    for (ulib_byte i = 0; i < count; ++i) {
        ulib_uint lhash = cowl_hash(cowl_get_field(object, i));
        hash = uhash_combine_hash(hash, lhash);
    }

    return hash;
}

ulib_uint cowl_uint_hash_impl(CowlAny *object) {
    ulib_uint hash = cowl_hash_impl(object);
    return uhash_combine_hash(hash, cowl_get_uint_field(object));
}

bool cowl_iterate_primitives_impl(CowlAny *object, CowlPrimitiveFlags flags,
                                  CowlIterator *iter) {
    ulib_byte count = composite_fields[cowl_get_type(object)];
    for (ulib_byte i = 0; i < count; ++i) {
        if (!cowl_iterate_primitives(cowl_get_field(object, i), flags, iter)) return false;
    }
    CowlAny *opt = cowl_get_opt_field(object);
    if (opt) cowl_iterate_primitives(opt, flags, iter);
    return true;
}

CowlAny* cowl_get_field(CowlAny *object, ulib_uint index) {
    return ((CowlComposite *)object)->data[index];
}

bool cowl_has_opt_field(CowlAny *object) {
    return cowl_object_bit_get(object);
}

CowlAny* cowl_get_opt_field(CowlAny *object) {
    if (!cowl_object_bit_get(object)) return NULL;
    return cowl_get_field(object, composite_fields[cowl_get_type(object)]);
}

ulib_uint cowl_get_uint_field(CowlAny *object) {
    ulib_byte idx = composite_fields[cowl_get_type(object)];
    if (cowl_has_opt_field(object)) idx++;
    return (ulib_uint)(uintptr_t)cowl_get_field(object, idx);
}
