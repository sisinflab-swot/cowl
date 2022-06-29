/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2021-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_stream.h"
#include "cowl_private.h"

#define UINT_MAX_DIGITS 20

// Misc

ustream_ret cowl_stream_write_object(UOStream *s, void *obj) {
    switch (cowl_get_type(obj)) {
        case COWL_OT_STRING: return cowl_stream_write_string(s, obj);
        case COWL_OT_VECTOR: return cowl_stream_write_vector(s, obj);
        case COWL_OT_SET: return cowl_stream_write_set(s, obj);
        case COWL_OT_IRI: return cowl_stream_write_iri(s, obj);
        case COWL_OT_LITERAL: return cowl_stream_write_literal(s, obj);
        case COWL_OT_ANNOT_PROP:
        case COWL_OT_CE_CLASS:
        case COWL_OT_DPE_DATA_PROP:
        case COWL_OT_DR_DATATYPE:
        case COWL_OT_I_NAMED:
        case COWL_OT_I_ANONYMOUS:
        case COWL_OT_OPE_OBJ_PROP: return cowl_stream_write_primitive(s, obj);
        case COWL_OT_CE_OBJ_MIN_CARD:
        case COWL_OT_CE_OBJ_MAX_CARD:
        case COWL_OT_CE_OBJ_EXACT_CARD:
        case COWL_OT_CE_DATA_MIN_CARD:
        case COWL_OT_CE_DATA_MAX_CARD:
        case COWL_OT_CE_DATA_EXACT_CARD: return cowl_stream_write_composite_uint(s, obj);
        case COWL_OT_ONTOLOGY: return cowl_stream_write_ontology(s, obj);
        default: return cowl_stream_write_composite(s, obj);
    }
}

static ustream_ret cowl_stream_write_object_type(UOStream *s, CowlObjectType type) {
    #define GEN_OT_STRING(T, S) case COWL_OT_##T: return cowl_stream_write_static(s, S)

    switch (type) {
        GEN_OT_STRING(STRING, "String");
        GEN_OT_STRING(VECTOR, "Vector");
        GEN_OT_STRING(SET, "Set");
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
        GEN_OT_STRING(A_SAME_IND, "SameIndividuals");
        GEN_OT_STRING(A_DIFF_IND, "DifferentIndividuals");
        GEN_OT_STRING(A_OBJ_PROP_ASSERT, "ObjectPropertyAssertion");
        GEN_OT_STRING(A_NEG_OBJ_PROP_ASSERT, "NegativeObjectPropertyAssertion");
        GEN_OT_STRING(A_DATA_PROP_ASSERT, "DataPropertyAssertion");
        GEN_OT_STRING(A_NEG_DATA_PROP_ASSERT, "NegativeDataPropertyAssertion");
        GEN_OT_STRING(A_SUB_OBJ_PROP, "SubObjectPropertyOf");
        GEN_OT_STRING(A_SUB_OBJ_PROP_CHAIN, "SubObjectPropertyChain");
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
        GEN_OT_STRING(A_SUB_ANNOT_PROP, "AnnotationProperty");
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
        GEN_OT_STRING(OPE_INV_OBJ_PROP, "InverseObjectProperty");
        default: {
            cowl_stream_write_static(s, "UnknownConstruct(");
            cowl_stream_write_uint(s, type);
            cowl_stream_write_static(s, ")");
            break;
        }
    }
    return s->state;
}

static ustream_ret cowl_stream_write_composite_header(UOStream *s, void *obj) {
    CowlObjectType type = cowl_get_type(obj);
    cowl_stream_write_object_type(s, type);
    cowl_stream_write_static(s, "(");

    ulib_byte count = composite_fields[type];
    cowl_stream_write_object(s, cowl_get_field(obj, 0));
    for (ulib_byte i = 1; i < count; ++i) {
        cowl_stream_write_static(s, " ");
        cowl_stream_write_object(s, cowl_get_field(obj, i));
    }

    void *opt = cowl_get_opt_field(obj);
    if (opt) {
        cowl_stream_write_static(s, " ");
        cowl_stream_write_object(s, opt);
    }

    return s->state;
}

ustream_ret cowl_stream_write_composite(UOStream *s, void *obj) {
    cowl_stream_write_composite_header(s, obj);
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_composite_uint(UOStream *s, void *obj) {
    cowl_stream_write_composite_header(s, obj);
    cowl_stream_write_static(s, " ");
    cowl_stream_write_uint(s, cowl_get_uint_field(obj));
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_object_debug(UOStream *s, CowlObject *obj) {
    uostream_writef(s, NULL, "<CowlObject %p, type ", obj);
    cowl_stream_write_object_type(s, cowl_get_type(obj));
    cowl_stream_write_static(s, ", ref ");
    cowl_stream_write_uint(s, cowl_object_get_ref(obj));
    cowl_stream_write_static(s, ">");
    return s->state;
}

ustream_ret cowl_stream_write_string(UOStream *s, CowlString *string) {
    return uostream_write_string(s, &string->raw_string, NULL);
}

ustream_ret cowl_stream_write_ustring(UOStream *s, UString string) {
    return uostream_write_string(s, &string, NULL);
}

ustream_ret cowl_stream_write_iri(UOStream *s, CowlIRI *iri) {
    cowl_stream_write_static(s, "<");
    cowl_stream_write_iri_no_brackets(s, iri);
    cowl_stream_write_static(s, ">");
    return s->state;
}

ustream_ret cowl_stream_write_iri_no_brackets(UOStream *s, CowlIRI *iri) {
    cowl_stream_write_string(s, cowl_iri_get_ns(iri));
    cowl_stream_write_string(s, cowl_iri_get_rem(iri));
    return s->state;
}

static bool imports_writer(void *ctx, void *import) {
    UOStream *s = ctx;
    CowlIRI *iri = cowl_ontology_get_id(import).ontology_iri;
    cowl_stream_write_static(s, "\n");
    cowl_stream_write_static(s, "Imports");
    cowl_stream_write_static(s, "(");

    if (iri) {
        cowl_stream_write_iri(s, iri);
    } else {
        uostream_writef(s, NULL, "anon(%p)", import);
    }

    cowl_stream_write_static(s, ")");
    return s->state == USTREAM_OK;
}

static bool entity_writer(void *ctx, void *obj) {
    UOStream *s = ctx;
    cowl_stream_write_primitive(s, obj);
    cowl_stream_write_static(s, "\n");
    return s->state == USTREAM_OK;
}

static bool axiom_writer(void *ctx, void *obj) {
    UOStream *s = ctx;
    cowl_stream_write_object(s, obj);
    cowl_stream_write_static(s, "\n");
    return s->state == USTREAM_OK;
}

ustream_ret cowl_stream_write_ontology(UOStream *s, CowlOntology *onto) {
    cowl_stream_write_static(s, "Ontology");
    cowl_stream_write_static(s, "(");
    cowl_stream_write_ontology_id(s, &onto->id);

    CowlIterator iter = cowl_iterator_init(s, imports_writer);
    cowl_ontology_iterate_imports(onto, &iter);
    if (s->state) return s->state;

    CowlVector *annotations = cowl_ontology_get_annot(onto);
    cowl_vector_foreach(annotations, annot) {
        cowl_stream_write_static(s, "\n");
        cowl_stream_write_object(s, *annot.item);
    }

    cowl_stream_write_static(s, ")");
    cowl_stream_write_static(s, "\n");

    iter = cowl_iterator_init(s, entity_writer);
    cowl_ontology_iterate_primitives(onto, COWL_PF_ENTITY, &iter);

    iter = cowl_iterator_init(s, axiom_writer);
    cowl_ontology_iterate_axioms(onto, &iter);

    return s->state;
}

ustream_ret cowl_stream_write_ontology_id(UOStream *s, CowlOntologyId *id) {
    if (id->ontology_iri) cowl_stream_write_iri(s, id->ontology_iri);

    if (id->version_iri) {
        if (id->ontology_iri) cowl_stream_write_static(s, " ");
        cowl_stream_write_iri(s, id->version_iri);
    }

    return s->state;
}

ustream_ret cowl_stream_write_literal(UOStream *s, CowlLiteral *literal) {
    cowl_stream_write_static(s, "\"");
    cowl_stream_write_string(s, cowl_literal_get_value(literal));
    cowl_stream_write_static(s, "\"");

    CowlDatatype *dt = cowl_literal_get_datatype(literal);
    if (cowl_datatype_equals(dt, cowl_rdf_vocab_get()->dt.plain_literal)) {
        CowlString *lang = cowl_literal_get_lang(literal);
        if (lang) {
            cowl_stream_write_static(s, "@");
            cowl_stream_write_string(s, lang);
        }
    } else {
        cowl_stream_write_static(s, "^^");
        cowl_stream_write_iri_no_brackets(s, cowl_datatype_get_iri(dt));
    }

    return s->state;
}

ustream_ret cowl_stream_write_node_id(UOStream *s, CowlNodeId id) {
    cowl_stream_write_static(s, "_:id");
    cowl_stream_write_uint(s, id);
    return s->state;
}

ustream_ret cowl_stream_write_uint(UOStream *s, uint64_t uint) {
    char buf[UINT_MAX_DIGITS + 1];
    size_t len = cowl_str_from_uint(uint, buf);
    return uostream_write(s, buf, len, NULL);
}

ustream_ret cowl_stream_write_error(UOStream *s, CowlError const *error) {
    cowl_stream_write_static(s, "Error ");
    cowl_stream_write_uint(s, error->code);

    if (error->origin) {
        cowl_stream_write_static(s, " - triggered by ");

        if (cowl_get_type(error->origin) == COWL_OT_MANAGER) {
            CowlParser parser = cowl_manager_get_parser((CowlManager *)error->origin);
            char const *name = parser.name ? parser.name : "unnamed";
            uostream_write(s, name, strlen(name), NULL);
            cowl_stream_write_static(s, " parser ");
        } else {
            cowl_stream_write_object_debug(s, error->origin);
        }
    }

    CowlErrorLoc loc = error->location;

    if (loc.iri || loc.source || loc.line) {
        cowl_stream_write_static(s, " (");

        if (loc.iri) {
            cowl_stream_write_iri_no_brackets(s, loc.iri);
            cowl_stream_write_static(s, ", ");
        }

        if (loc.source) {
            cowl_stream_write_string(s, loc.source);
            cowl_stream_write_static(s, ", ");
        }

        if (loc.line) {
            cowl_stream_write_static(s, "line ");
            cowl_stream_write_uint(s, loc.line);
        }

        cowl_stream_write_static(s, ")");
    }

    cowl_stream_write_static(s, " - ");
    cowl_stream_write_ustring(s, cowl_ret_to_ustring(error->code));

    if (error->description) {
        cowl_stream_write_static(s, ": ");
        cowl_stream_write_string(s, error->description);
    }

    return s->state;
}

ustream_ret cowl_stream_write_primitive(UOStream *s, void *primitive) {
    CowlObjectType type = cowl_get_type(primitive);
    cowl_stream_write_object_type(s, type);
    cowl_stream_write_static(s, "(");
    if (type == COWL_OT_I_ANONYMOUS) {
        cowl_stream_write_node_id(s, cowl_anon_ind_get_id((CowlAnonInd *)primitive));
    } else {
        cowl_stream_write_iri(s, cowl_entity_get_iri((CowlEntity *)primitive));
    }
    cowl_stream_write_static(s, ")");
    return s->state;
}

ustream_ret cowl_stream_write_set(UOStream *s, CowlSet *set) {
    if (!set) return s->state;
    UHash(CowlObjectTable) const *data = cowl_set_get_data(set);
    ulib_uint current = 0, last = uhash_count(CowlObjectTable, data) - 1;

    uhash_foreach(CowlObjectTable, data, obj) {
        cowl_stream_write_object(s, *obj.key);
        if (current++ < last) cowl_stream_write_static(s, " ");
    }

    return s->state;
}

ustream_ret cowl_stream_write_vector(UOStream *s, CowlVector *vector) {
    if (!vector) return s->state;
    ulib_uint last = cowl_vector_count(vector) - 1;

    cowl_vector_foreach(vector, obj) {
        cowl_stream_write_object(s, *obj.item);
        if (obj.i < last) cowl_stream_write_static(s, " ");
    }

    return s->state;
}
