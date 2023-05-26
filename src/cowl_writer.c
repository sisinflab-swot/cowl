/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_writer.h"
#include "cowl_config_private.h"
#include "cowl_cstring.h"
#include "cowl_iri.h"
#include "cowl_manager_private.h"
#include "cowl_ontology.h"
#include "cowl_reader.h"
#include "cowl_string_private.h"

#define UINT_MAX_DIGITS 20

cowl_ret cowl_write(UOStream *stream, CowlAny *object) {
    CowlWriter writer = cowl_get_writer();
    if (writer.write) return writer.write(stream, object);
    return cowl_ret_from_ustream(cowl_write_debug(stream, object));
}

ustream_ret cowl_write_debug(UOStream *s, CowlAny *obj) {
    uostream_writef(s, NULL, "<CowlObject %p, type ", obj);
    cowl_write_object_type(s, cowl_get_type(obj));
    cowl_write_static(s, ", ref ");
    cowl_write_uint(s, cowl_object_get_ref(obj));
    cowl_write_static(s, ">");
    return s->state;
}

ustream_ret cowl_write_string(UOStream *stream, CowlString *string) {
    return uostream_write_string(stream, &string->raw_string, NULL);
}

ustream_ret cowl_write_iri(UOStream *stream, CowlIRI *iri) {
    cowl_write_string(stream, cowl_iri_get_ns(iri));
    cowl_write_string(stream, cowl_iri_get_rem(iri));
    return stream->state;
}

ustream_ret cowl_write_uint(UOStream *stream, ulib_uint uint) {
    char buf[UINT_MAX_DIGITS + 1];
    size_t len = cowl_str_from_uint(uint, buf);
    return uostream_write(stream, buf, len, NULL);
}

ustream_ret cowl_write_object_type(UOStream *s, CowlObjectType type) {
    switch (type) {
        case COWL_OT_STRING: return cowl_write_static(s, "String");
        case COWL_OT_VECTOR: return cowl_write_static(s, "Vector");
        case COWL_OT_TABLE: return cowl_write_static(s, "Table");
        case COWL_OT_IRI: return cowl_write_static(s, "IRI");
        case COWL_OT_LITERAL: return cowl_write_static(s, "Literal");
        case COWL_OT_FACET_RESTR: return cowl_write_static(s, "FacetRestriction");
        case COWL_OT_ONTOLOGY: return cowl_write_static(s, "Ontology");
        case COWL_OT_MANAGER: return cowl_write_static(s, "Manager");
        case COWL_OT_SYM_TABLE: return cowl_write_static(s, "SymbolTable");
        case COWL_OT_ISTREAM: return cowl_write_static(s, "InputStream");
        case COWL_OT_OSTREAM: return cowl_write_static(s, "OutputStream");
        case COWL_OT_ANNOTATION: return cowl_write_static(s, "Annotation");
        case COWL_OT_ANNOT_PROP: return cowl_write_static(s, "AnnotationProperty");
        case COWL_OT_A_DECL: return cowl_write_static(s, "Declaration");
        case COWL_OT_A_DATATYPE_DEF: return cowl_write_static(s, "DatatypeDefinition");
        case COWL_OT_A_SUB_CLASS: return cowl_write_static(s, "SubClassOf");
        case COWL_OT_A_EQUIV_CLASSES: return cowl_write_static(s, "EquivalentClasses");
        case COWL_OT_A_DISJ_CLASSES: return cowl_write_static(s, "DisjointClasses");
        case COWL_OT_A_DISJ_UNION: return cowl_write_static(s, "DisjointUnion");
        case COWL_OT_A_CLASS_ASSERT: return cowl_write_static(s, "ClassAssertion");
        case COWL_OT_A_SAME_IND: return cowl_write_static(s, "SameIndividual");
        case COWL_OT_A_DIFF_IND: return cowl_write_static(s, "DifferentIndividuals");
        case COWL_OT_A_OBJ_PROP_ASSERT: return cowl_write_static(s, "ObjectPropertyAssertion");
        case COWL_OT_A_NEG_OBJ_PROP_ASSERT:
            return cowl_write_static(s, "NegativeObjectPropertyAssertion");
        case COWL_OT_A_DATA_PROP_ASSERT: return cowl_write_static(s, "DataPropertyAssertion");
        case COWL_OT_A_NEG_DATA_PROP_ASSERT:
            return cowl_write_static(s, "NegativeDataPropertyAssertion");
        case COWL_OT_A_SUB_OBJ_PROP: return cowl_write_static(s, "SubObjectPropertyOf");
        case COWL_OT_A_INV_OBJ_PROP: return cowl_write_static(s, "InverseObjectProperties");
        case COWL_OT_A_EQUIV_OBJ_PROP: return cowl_write_static(s, "EquivalentObjectProperties");
        case COWL_OT_A_DISJ_OBJ_PROP: return cowl_write_static(s, "DisjointObjectProperties");
        case COWL_OT_A_FUNC_OBJ_PROP: return cowl_write_static(s, "FunctionalObjectProperty");
        case COWL_OT_A_INV_FUNC_OBJ_PROP:
            return cowl_write_static(s, "InverseFunctionalObjectProperty");
        case COWL_OT_A_SYMM_OBJ_PROP: return cowl_write_static(s, "SymmetricObjectProperty");
        case COWL_OT_A_ASYMM_OBJ_PROP: return cowl_write_static(s, "AsymmetricObjectProperty");
        case COWL_OT_A_TRANS_OBJ_PROP: return cowl_write_static(s, "TransitiveObjectProperty");
        case COWL_OT_A_REFL_OBJ_PROP: return cowl_write_static(s, "ReflexiveObjectProperty");
        case COWL_OT_A_IRREFL_OBJ_PROP: return cowl_write_static(s, "IrreflexiveObjectProperty");
        case COWL_OT_A_OBJ_PROP_DOMAIN: return cowl_write_static(s, "ObjectPropertyDomain");
        case COWL_OT_A_OBJ_PROP_RANGE: return cowl_write_static(s, "ObjectPropertyRange");
        case COWL_OT_A_SUB_DATA_PROP: return cowl_write_static(s, "SubDataPropertyOf");
        case COWL_OT_A_EQUIV_DATA_PROP: return cowl_write_static(s, "EquivalentDataProperties");
        case COWL_OT_A_DISJ_DATA_PROP: return cowl_write_static(s, "DisjointDataProperties");
        case COWL_OT_A_FUNC_DATA_PROP: return cowl_write_static(s, "FunctionalDataProperty");
        case COWL_OT_A_DATA_PROP_DOMAIN: return cowl_write_static(s, "DataPropertyDomain");
        case COWL_OT_A_DATA_PROP_RANGE: return cowl_write_static(s, "DataPropertyRange");
        case COWL_OT_A_HAS_KEY: return cowl_write_static(s, "HasKey");
        case COWL_OT_A_ANNOT_ASSERT: return cowl_write_static(s, "AnnotationAssertion");
        case COWL_OT_A_SUB_ANNOT_PROP: return cowl_write_static(s, "SubAnnotationPropertyOf");
        case COWL_OT_A_ANNOT_PROP_DOMAIN: return cowl_write_static(s, "AnnotationPropertyDomain");
        case COWL_OT_A_ANNOT_PROP_RANGE: return cowl_write_static(s, "AnnotationPropertyRange");
        case COWL_OT_CE_CLASS: return cowl_write_static(s, "Class");
        case COWL_OT_CE_OBJ_SOME: return cowl_write_static(s, "ObjectSomeValuesFrom");
        case COWL_OT_CE_OBJ_ALL: return cowl_write_static(s, "ObjectAllValuesFrom");
        case COWL_OT_CE_OBJ_MIN_CARD: return cowl_write_static(s, "ObjectMinCardinality");
        case COWL_OT_CE_OBJ_MAX_CARD: return cowl_write_static(s, "ObjectMaxCardinality");
        case COWL_OT_CE_OBJ_EXACT_CARD: return cowl_write_static(s, "ObjectExactCardinality");
        case COWL_OT_CE_OBJ_HAS_VALUE: return cowl_write_static(s, "ObjectHasValue");
        case COWL_OT_CE_OBJ_HAS_SELF: return cowl_write_static(s, "ObjectHasSelf");
        case COWL_OT_CE_DATA_SOME: return cowl_write_static(s, "DataSomeValuesFrom");
        case COWL_OT_CE_DATA_ALL: return cowl_write_static(s, "DataAllValuesFrom");
        case COWL_OT_CE_DATA_MIN_CARD: return cowl_write_static(s, "DataMinCardinality");
        case COWL_OT_CE_DATA_MAX_CARD: return cowl_write_static(s, "DataMaxCardinality");
        case COWL_OT_CE_DATA_EXACT_CARD: return cowl_write_static(s, "DataExactCardinality");
        case COWL_OT_CE_DATA_HAS_VALUE: return cowl_write_static(s, "DataHasValue");
        case COWL_OT_CE_OBJ_INTERSECT: return cowl_write_static(s, "ObjectIntersectionOf");
        case COWL_OT_CE_OBJ_UNION: return cowl_write_static(s, "ObjectUnionOf");
        case COWL_OT_CE_OBJ_COMPL: return cowl_write_static(s, "ObjectComplementOf");
        case COWL_OT_CE_OBJ_ONE_OF: return cowl_write_static(s, "ObjectOneOf");
        case COWL_OT_DPE_DATA_PROP: return cowl_write_static(s, "DataProperty");
        case COWL_OT_DR_DATATYPE: return cowl_write_static(s, "Datatype");
        case COWL_OT_DR_DATATYPE_RESTR: return cowl_write_static(s, "DatatypeRestriction");
        case COWL_OT_DR_DATA_INTERSECT: return cowl_write_static(s, "DataIntersectionOf");
        case COWL_OT_DR_DATA_UNION: return cowl_write_static(s, "DataUnionOf");
        case COWL_OT_DR_DATA_COMPL: return cowl_write_static(s, "DataComplementOf");
        case COWL_OT_DR_DATA_ONE_OF: return cowl_write_static(s, "DataOneOf");
        case COWL_OT_I_ANONYMOUS: return cowl_write_static(s, "AnonymousIndividual");
        case COWL_OT_I_NAMED: return cowl_write_static(s, "NamedIndividual");
        case COWL_OT_OPE_OBJ_PROP: return cowl_write_static(s, "ObjectProperty");
        case COWL_OT_OPE_INV_OBJ_PROP: return cowl_write_static(s, "ObjectInverseOf");
        default: {
            cowl_write_static(s, "UnknownConstruct(");
            cowl_write_uint(s, type);
            cowl_write_static(s, ")");
            break;
        }
    }
    return s->state;
}

ustream_ret cowl_write_error(UOStream *s, CowlError const *error) {
    cowl_write_static(s, "Error ");
    cowl_write_uint(s, error->code);

    if (error->origin) {
        cowl_write_static(s, " - triggered by ");

        switch (cowl_get_type(error->origin)) {
            case COWL_OT_MANAGER: {
                CowlReader reader = cowl_manager_get_reader((CowlManager *)error->origin);
                char const *name = reader.name ? reader.name : "unnamed";
                uostream_write(s, name, strlen(name), NULL);
                cowl_write_static(s, " reader");
                break;
            }
            case COWL_OT_ONTOLOGY: {
                CowlOntology *onto = error->origin;
                cowl_write_static(s, "ontology ");
                cowl_write_iri(s, cowl_ontology_get_id(onto).iri);
                break;
            }
            default: {
                cowl_write_debug(s, error->origin);
                break;
            }
        }
    }

    if (error->code == COWL_ERR_SYNTAX) {
        CowlSyntaxError const *se = (CowlSyntaxError *)error;

        if (se->loc.source || se->loc.line) {
            cowl_write_static(s, " (");

            if (se->loc.source) {
                cowl_write_string(s, se->loc.source);
                cowl_write_static(s, ", ");
            }

            if (se->loc.line) {
                cowl_write_static(s, "line ");
                cowl_write_uint(s, se->loc.line);
            }

            cowl_write_static(s, ")");
        }
    }

    cowl_write_static(s, " - ");

    UString str = cowl_ret_to_ustring(error->code);
    cowl_write_ustring(s, &str);

    if (error->description) {
        cowl_write_static(s, ": ");
        cowl_write_string(s, error->description);
    }

    return s->state;
}
