/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2023 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_object_type.h"
#include "cowl_string.h"

UString cowl_object_type_to_ustring(CowlObjectType type) {
    switch (type) {
        case COWL_OT_STRING: return ustring_literal("String");
        case COWL_OT_VECTOR: return ustring_literal("Vector");
        case COWL_OT_TABLE: return ustring_literal("Table");
        case COWL_OT_IRI: return ustring_literal("IRI");
        case COWL_OT_LITERAL: return ustring_literal("Literal");
        case COWL_OT_FACET_RESTR: return ustring_literal("FacetRestriction");
        case COWL_OT_ONTOLOGY: return ustring_literal("Ontology");
        case COWL_OT_MANAGER: return ustring_literal("Manager");
        case COWL_OT_SYM_TABLE: return ustring_literal("SymbolTable");
        case COWL_OT_ISTREAM: return ustring_literal("InputStream");
        case COWL_OT_OSTREAM: return ustring_literal("OutputStream");
        case COWL_OT_ANNOTATION: return ustring_literal("Annotation");
        case COWL_OT_ANNOT_PROP: return ustring_literal("AnnotationProperty");
        case COWL_OT_A_DECL: return ustring_literal("Declaration");
        case COWL_OT_A_DATATYPE_DEF: return ustring_literal("DatatypeDefinition");
        case COWL_OT_A_SUB_CLASS: return ustring_literal("SubClassOf");
        case COWL_OT_A_EQUIV_CLASSES: return ustring_literal("EquivalentClasses");
        case COWL_OT_A_DISJ_CLASSES: return ustring_literal("DisjointClasses");
        case COWL_OT_A_DISJ_UNION: return ustring_literal("DisjointUnion");
        case COWL_OT_A_CLASS_ASSERT: return ustring_literal("ClassAssertion");
        case COWL_OT_A_SAME_IND: return ustring_literal("SameIndividual");
        case COWL_OT_A_DIFF_IND: return ustring_literal("DifferentIndividuals");
        case COWL_OT_A_OBJ_PROP_ASSERT: return ustring_literal("ObjectPropertyAssertion");
        case COWL_OT_A_NEG_OBJ_PROP_ASSERT:
            return ustring_literal("NegativeObjectPropertyAssertion");
        case COWL_OT_A_DATA_PROP_ASSERT: return ustring_literal("DataPropertyAssertion");
        case COWL_OT_A_NEG_DATA_PROP_ASSERT:
            return ustring_literal("NegativeDataPropertyAssertion");
        case COWL_OT_A_SUB_OBJ_PROP: return ustring_literal("SubObjectPropertyOf");
        case COWL_OT_A_INV_OBJ_PROP: return ustring_literal("InverseObjectProperties");
        case COWL_OT_A_EQUIV_OBJ_PROP: return ustring_literal("EquivalentObjectProperties");
        case COWL_OT_A_DISJ_OBJ_PROP: return ustring_literal("DisjointObjectProperties");
        case COWL_OT_A_FUNC_OBJ_PROP: return ustring_literal("FunctionalObjectProperty");
        case COWL_OT_A_INV_FUNC_OBJ_PROP: return ustring_literal("InverseFunctionalObjectProperty");
        case COWL_OT_A_SYMM_OBJ_PROP: return ustring_literal("SymmetricObjectProperty");
        case COWL_OT_A_ASYMM_OBJ_PROP: return ustring_literal("AsymmetricObjectProperty");
        case COWL_OT_A_TRANS_OBJ_PROP: return ustring_literal("TransitiveObjectProperty");
        case COWL_OT_A_REFL_OBJ_PROP: return ustring_literal("ReflexiveObjectProperty");
        case COWL_OT_A_IRREFL_OBJ_PROP: return ustring_literal("IrreflexiveObjectProperty");
        case COWL_OT_A_OBJ_PROP_DOMAIN: return ustring_literal("ObjectPropertyDomain");
        case COWL_OT_A_OBJ_PROP_RANGE: return ustring_literal("ObjectPropertyRange");
        case COWL_OT_A_SUB_DATA_PROP: return ustring_literal("SubDataPropertyOf");
        case COWL_OT_A_EQUIV_DATA_PROP: return ustring_literal("EquivalentDataProperties");
        case COWL_OT_A_DISJ_DATA_PROP: return ustring_literal("DisjointDataProperties");
        case COWL_OT_A_FUNC_DATA_PROP: return ustring_literal("FunctionalDataProperty");
        case COWL_OT_A_DATA_PROP_DOMAIN: return ustring_literal("DataPropertyDomain");
        case COWL_OT_A_DATA_PROP_RANGE: return ustring_literal("DataPropertyRange");
        case COWL_OT_A_HAS_KEY: return ustring_literal("HasKey");
        case COWL_OT_A_ANNOT_ASSERT: return ustring_literal("AnnotationAssertion");
        case COWL_OT_A_SUB_ANNOT_PROP: return ustring_literal("SubAnnotationPropertyOf");
        case COWL_OT_A_ANNOT_PROP_DOMAIN: return ustring_literal("AnnotationPropertyDomain");
        case COWL_OT_A_ANNOT_PROP_RANGE: return ustring_literal("AnnotationPropertyRange");
        case COWL_OT_CE_CLASS: return ustring_literal("Class");
        case COWL_OT_CE_OBJ_SOME: return ustring_literal("ObjectSomeValuesFrom");
        case COWL_OT_CE_OBJ_ALL: return ustring_literal("ObjectAllValuesFrom");
        case COWL_OT_CE_OBJ_MIN_CARD: return ustring_literal("ObjectMinCardinality");
        case COWL_OT_CE_OBJ_MAX_CARD: return ustring_literal("ObjectMaxCardinality");
        case COWL_OT_CE_OBJ_EXACT_CARD: return ustring_literal("ObjectExactCardinality");
        case COWL_OT_CE_OBJ_HAS_VALUE: return ustring_literal("ObjectHasValue");
        case COWL_OT_CE_OBJ_HAS_SELF: return ustring_literal("ObjectHasSelf");
        case COWL_OT_CE_DATA_SOME: return ustring_literal("DataSomeValuesFrom");
        case COWL_OT_CE_DATA_ALL: return ustring_literal("DataAllValuesFrom");
        case COWL_OT_CE_DATA_MIN_CARD: return ustring_literal("DataMinCardinality");
        case COWL_OT_CE_DATA_MAX_CARD: return ustring_literal("DataMaxCardinality");
        case COWL_OT_CE_DATA_EXACT_CARD: return ustring_literal("DataExactCardinality");
        case COWL_OT_CE_DATA_HAS_VALUE: return ustring_literal("DataHasValue");
        case COWL_OT_CE_OBJ_INTERSECT: return ustring_literal("ObjectIntersectionOf");
        case COWL_OT_CE_OBJ_UNION: return ustring_literal("ObjectUnionOf");
        case COWL_OT_CE_OBJ_COMPL: return ustring_literal("ObjectComplementOf");
        case COWL_OT_CE_OBJ_ONE_OF: return ustring_literal("ObjectOneOf");
        case COWL_OT_DPE_DATA_PROP: return ustring_literal("DataProperty");
        case COWL_OT_DR_DATATYPE: return ustring_literal("Datatype");
        case COWL_OT_DR_DATATYPE_RESTR: return ustring_literal("DatatypeRestriction");
        case COWL_OT_DR_DATA_INTERSECT: return ustring_literal("DataIntersectionOf");
        case COWL_OT_DR_DATA_UNION: return ustring_literal("DataUnionOf");
        case COWL_OT_DR_DATA_COMPL: return ustring_literal("DataComplementOf");
        case COWL_OT_DR_DATA_ONE_OF: return ustring_literal("DataOneOf");
        case COWL_OT_I_ANONYMOUS: return ustring_literal("AnonymousIndividual");
        case COWL_OT_I_NAMED: return ustring_literal("NamedIndividual");
        case COWL_OT_OPE_OBJ_PROP: return ustring_literal("ObjectProperty");
        case COWL_OT_OPE_INV_OBJ_PROP: return ustring_literal("ObjectInverseOf");
        default: return ustring_literal("UnknownConstruct");
    }
}

CowlString *cowl_object_type_to_string(CowlObjectType type) {
    return cowl_string_opt(cowl_object_type_to_ustring(type), COWL_SO_COPY);
}
