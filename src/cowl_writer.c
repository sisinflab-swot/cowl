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
#define GEN_OT_STRING(T, S)                                                                        \
    case COWL_OT_##T: return cowl_write_static(s, S)

    switch (type) {
        GEN_OT_STRING(STRING, "String");
        GEN_OT_STRING(VECTOR, "Vector");
        GEN_OT_STRING(TABLE, "Table");
        GEN_OT_STRING(IRI, "IRI");
        GEN_OT_STRING(LITERAL, "Literal");
        GEN_OT_STRING(FACET_RESTR, "FacetRestriction");
        GEN_OT_STRING(ONTOLOGY, "Ontology");
        GEN_OT_STRING(MANAGER, "Manager");
        GEN_OT_STRING(ANNOTATION, "Annotation");
        GEN_OT_STRING(ANNOT_PROP, "AnnotationProperty");
        GEN_OT_STRING(A_DECL, "Declaration");
        GEN_OT_STRING(A_DATATYPE_DEF, "DatatypeDefinition");
        GEN_OT_STRING(A_SUB_CLASS, "SubClassOf");
        GEN_OT_STRING(A_EQUIV_CLASSES, "EquivalentClasses");
        GEN_OT_STRING(A_DISJ_CLASSES, "DisjointClasses");
        GEN_OT_STRING(A_DISJ_UNION, "DisjointUnion");
        GEN_OT_STRING(A_CLASS_ASSERT, "ClassAssertion");
        GEN_OT_STRING(A_SAME_IND, "SameIndividual");
        GEN_OT_STRING(A_DIFF_IND, "DifferentIndividuals");
        GEN_OT_STRING(A_OBJ_PROP_ASSERT, "ObjectPropertyAssertion");
        GEN_OT_STRING(A_NEG_OBJ_PROP_ASSERT, "NegativeObjectPropertyAssertion");
        GEN_OT_STRING(A_DATA_PROP_ASSERT, "DataPropertyAssertion");
        GEN_OT_STRING(A_NEG_DATA_PROP_ASSERT, "NegativeDataPropertyAssertion");
        GEN_OT_STRING(A_SUB_OBJ_PROP, "SubObjectPropertyOf");
        GEN_OT_STRING(A_INV_OBJ_PROP, "InverseObjectProperties");
        GEN_OT_STRING(A_EQUIV_OBJ_PROP, "EquivalentObjectProperties");
        GEN_OT_STRING(A_DISJ_OBJ_PROP, "DisjointObjectProperties");
        GEN_OT_STRING(A_FUNC_OBJ_PROP, "FunctionalObjectProperty");
        GEN_OT_STRING(A_INV_FUNC_OBJ_PROP, "InverseFunctionalObjectProperty");
        GEN_OT_STRING(A_SYMM_OBJ_PROP, "SymmetricObjectProperty");
        GEN_OT_STRING(A_ASYMM_OBJ_PROP, "AsymmetricObjectProperty");
        GEN_OT_STRING(A_TRANS_OBJ_PROP, "TransitiveObjectProperty");
        GEN_OT_STRING(A_REFL_OBJ_PROP, "ReflexiveObjectProperty");
        GEN_OT_STRING(A_IRREFL_OBJ_PROP, "IrreflexiveObjectProperty");
        GEN_OT_STRING(A_OBJ_PROP_DOMAIN, "ObjectPropertyDomain");
        GEN_OT_STRING(A_OBJ_PROP_RANGE, "ObjectPropertyRange");
        GEN_OT_STRING(A_SUB_DATA_PROP, "SubDataPropertyOf");
        GEN_OT_STRING(A_EQUIV_DATA_PROP, "EquivalentDataProperties");
        GEN_OT_STRING(A_DISJ_DATA_PROP, "DisjointDataProperties");
        GEN_OT_STRING(A_FUNC_DATA_PROP, "FunctionalDataProperty");
        GEN_OT_STRING(A_DATA_PROP_DOMAIN, "DataPropertyDomain");
        GEN_OT_STRING(A_DATA_PROP_RANGE, "DataPropertyRange");
        GEN_OT_STRING(A_HAS_KEY, "HasKey");
        GEN_OT_STRING(A_ANNOT_ASSERT, "AnnotationAssertion");
        GEN_OT_STRING(A_SUB_ANNOT_PROP, "SubAnnotationPropertyOf");
        GEN_OT_STRING(A_ANNOT_PROP_DOMAIN, "AnnotationPropertyDomain");
        GEN_OT_STRING(A_ANNOT_PROP_RANGE, "AnnotationPropertyRange");
        GEN_OT_STRING(CE_CLASS, "Class");
        GEN_OT_STRING(CE_OBJ_SOME, "ObjectSomeValuesFrom");
        GEN_OT_STRING(CE_OBJ_ALL, "ObjectAllValuesFrom");
        GEN_OT_STRING(CE_OBJ_MIN_CARD, "ObjectMinCardinality");
        GEN_OT_STRING(CE_OBJ_MAX_CARD, "ObjectMaxCardinality");
        GEN_OT_STRING(CE_OBJ_EXACT_CARD, "ObjectExactCardinality");
        GEN_OT_STRING(CE_OBJ_HAS_VALUE, "ObjectHasValue");
        GEN_OT_STRING(CE_OBJ_HAS_SELF, "ObjectHasSelf");
        GEN_OT_STRING(CE_DATA_SOME, "DataSomeValuesFrom");
        GEN_OT_STRING(CE_DATA_ALL, "DataAllValuesFrom");
        GEN_OT_STRING(CE_DATA_MIN_CARD, "DataMinCardinality");
        GEN_OT_STRING(CE_DATA_MAX_CARD, "DataMaxCardinality");
        GEN_OT_STRING(CE_DATA_EXACT_CARD, "DataExactCardinality");
        GEN_OT_STRING(CE_DATA_HAS_VALUE, "DataHasValue");
        GEN_OT_STRING(CE_OBJ_INTERSECT, "ObjectIntersectionOf");
        GEN_OT_STRING(CE_OBJ_UNION, "ObjectUnionOf");
        GEN_OT_STRING(CE_OBJ_COMPL, "ObjectComplementOf");
        GEN_OT_STRING(CE_OBJ_ONE_OF, "ObjectOneOf");
        GEN_OT_STRING(DPE_DATA_PROP, "DataProperty");
        GEN_OT_STRING(DR_DATATYPE, "Datatype");
        GEN_OT_STRING(DR_DATATYPE_RESTR, "DatatypeRestriction");
        GEN_OT_STRING(DR_DATA_INTERSECT, "DataIntersectionOf");
        GEN_OT_STRING(DR_DATA_UNION, "DataUnionOf");
        GEN_OT_STRING(DR_DATA_COMPL, "DataComplementOf");
        GEN_OT_STRING(DR_DATA_ONE_OF, "DataOneOf");
        GEN_OT_STRING(I_ANONYMOUS, "AnonymousIndividual");
        GEN_OT_STRING(I_NAMED, "NamedIndividual");
        GEN_OT_STRING(OPE_OBJ_PROP, "ObjectProperty");
        GEN_OT_STRING(OPE_INV_OBJ_PROP, "ObjectInverseOf");
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
