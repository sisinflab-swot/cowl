/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_xsd_vocab_private.h"
#include "cowl_vocab_utils.h"

static CowlXSDVocab vocab;

static inline cowl_ret cowl_xsd_vocab_validate(void) {
    if (!vocab.ns) return COWL_ERR_MEM;

    void **temp = (void **)&vocab.iri;
    size_t count = sizeof(vocab.iri) / sizeof(void*);
    for (size_t i = 0; i < count; ++i) if (!temp[i]) return COWL_ERR_MEM;

    temp = (void **)&vocab.dt;
    count = sizeof(vocab.dt) / sizeof(void*);
    for (size_t i = 0; i < count; ++i) if (!temp[i]) return COWL_ERR_MEM;

    return COWL_OK;
}

cowl_ret cowl_xsd_vocab_init(void) {
    CowlString *ns = cowl_string_vocab("http://www.w3.org/2001/XMLSchema#");

    CowlXSDIRIVocab v = {
        .any_atomic_type = cowl_iri_vocab(ns, "anyAtomicType"),
        .any_simple_type = cowl_iri_vocab(ns, "anySimpleType"),
        .any_type = cowl_iri_vocab(ns, "anyType"),
        .any_uri = cowl_iri_vocab(ns, "anyURI"),
        .base64_binary = cowl_iri_vocab(ns, "base64Binary"),
        .boolean = cowl_iri_vocab(ns, "boolean"),
        .byte = cowl_iri_vocab(ns, "byte"),
        .date = cowl_iri_vocab(ns, "date"),
        .date_time = cowl_iri_vocab(ns, "dateTime"),
        .date_timestamp = cowl_iri_vocab(ns, "dateTimeStamp"),
        .day_time_duration = cowl_iri_vocab(ns, "dayTimeDuration"),
        .decimal = cowl_iri_vocab(ns, "decimal"),
        .xsd_double = cowl_iri_vocab(ns, "double"),
        .duration = cowl_iri_vocab(ns, "duration"),
        .entities = cowl_iri_vocab(ns, "ENTITIES"),
        .entity = cowl_iri_vocab(ns, "ENTITY"),
        .xsd_float = cowl_iri_vocab(ns, "float"),
        .g_day = cowl_iri_vocab(ns, "gDay"),
        .g_month = cowl_iri_vocab(ns, "gMonth"),
        .g_month_day = cowl_iri_vocab(ns, "gMonthDay"),
        .g_year = cowl_iri_vocab(ns, "gYear"),
        .g_year_month = cowl_iri_vocab(ns, "gYearMonth"),
        .hex_binary = cowl_iri_vocab(ns, "hexBinary"),
        .id = cowl_iri_vocab(ns, "ID"),
        .id_ref = cowl_iri_vocab(ns, "IDREF"),
        .id_refs = cowl_iri_vocab(ns, "IDREFS"),
        .xsd_int = cowl_iri_vocab(ns, "int"),
        .integer = cowl_iri_vocab(ns, "integer"),
        .language = cowl_iri_vocab(ns, "language"),
        .xsd_long = cowl_iri_vocab(ns, "long"),
        .name = cowl_iri_vocab(ns, "Name"),
        .ncname = cowl_iri_vocab(ns, "NCName"),
        .negative_int = cowl_iri_vocab(ns, "negativeInteger"),
        .nmtoken = cowl_iri_vocab(ns, "NMTOKEN"),
        .nmtokens = cowl_iri_vocab(ns, "NMTOKENS"),
        .non_negative_int = cowl_iri_vocab(ns, "nonNegativeInteger"),
        .non_positive_int = cowl_iri_vocab(ns, "nonPositiveInteger"),
        .norm_string = cowl_iri_vocab(ns, "normalizedString"),
        .notation = cowl_iri_vocab(ns, "NOTATION"),
        .positive_int = cowl_iri_vocab(ns, "positiveInteger"),
        .q_name = cowl_iri_vocab(ns, "QName"),
        .xsd_short = cowl_iri_vocab(ns, "short"),
        .string = cowl_iri_vocab(ns, "string"),
        .time = cowl_iri_vocab(ns, "time"),
        .token = cowl_iri_vocab(ns, "token"),
        .unsigned_byte = cowl_iri_vocab(ns, "unsignedByte"),
        .unsigned_int = cowl_iri_vocab(ns, "unsignedInt"),
        .unsigned_long = cowl_iri_vocab(ns, "unsignedLong"),
        .unsigned_short = cowl_iri_vocab(ns, "unsignedShort"),
        .year_month_duration = cowl_iri_vocab(ns, "yearMonthDuration"),
        .length = cowl_iri_vocab(ns, "length"),
        .min_length = cowl_iri_vocab(ns, "minLength"),
        .max_length = cowl_iri_vocab(ns, "maxLength"),
        .pattern = cowl_iri_vocab(ns, "pattern"),
        .min_inclusive = cowl_iri_vocab(ns, "minInclusive"),
        .min_exclusive = cowl_iri_vocab(ns, "minExclusive"),
        .max_inclusive = cowl_iri_vocab(ns, "maxInclusive"),
        .max_exclusive = cowl_iri_vocab(ns, "maxExclusive"),
        .total_digits = cowl_iri_vocab(ns, "totalDigits"),
        .fraction_digits = cowl_iri_vocab(ns, "fractionDigits")
    };

    vocab = (struct CowlXSDVocab) {
        .ns = ns,
        .iri = v,
        .dt = {
            .any_atomic_type = cowl_datatype_vocab(v.any_atomic_type),
            .any_simple_type = cowl_datatype_vocab(v.any_simple_type),
            .any_type = cowl_datatype_vocab(v.any_type),
            .any_uri = cowl_datatype_vocab(v.any_uri),
            .base64_binary = cowl_datatype_vocab(v.base64_binary),
            .boolean = cowl_datatype_vocab(v.boolean),
            .byte = cowl_datatype_vocab(v.byte),
            .date = cowl_datatype_vocab(v.date),
            .date_time = cowl_datatype_vocab(v.date_time),
            .date_timestamp = cowl_datatype_vocab(v.date_timestamp),
            .day_time_duration = cowl_datatype_vocab(v.day_time_duration),
            .decimal = cowl_datatype_vocab(v.decimal),
            .xsd_double = cowl_datatype_vocab(v.xsd_double),
            .duration = cowl_datatype_vocab(v.duration),
            .entities = cowl_datatype_vocab(v.entities),
            .entity = cowl_datatype_vocab(v.entity),
            .xsd_float = cowl_datatype_vocab(v.xsd_float),
            .g_day = cowl_datatype_vocab(v.g_day),
            .g_month = cowl_datatype_vocab(v.g_month),
            .g_month_day = cowl_datatype_vocab(v.g_month_day),
            .g_year = cowl_datatype_vocab(v.g_year),
            .g_year_month = cowl_datatype_vocab(v.g_year_month),
            .hex_binary = cowl_datatype_vocab(v.hex_binary),
            .id = cowl_datatype_vocab(v.id),
            .id_ref = cowl_datatype_vocab(v.id_ref),
            .id_refs = cowl_datatype_vocab(v.id_refs),
            .xsd_int = cowl_datatype_vocab(v.xsd_int),
            .integer = cowl_datatype_vocab(v.integer),
            .language = cowl_datatype_vocab(v.language),
            .xsd_long = cowl_datatype_vocab(v.xsd_long),
            .name = cowl_datatype_vocab(v.name),
            .ncname = cowl_datatype_vocab(v.ncname),
            .negative_int = cowl_datatype_vocab(v.negative_int),
            .nmtoken = cowl_datatype_vocab(v.nmtoken),
            .nmtokens = cowl_datatype_vocab(v.nmtokens),
            .non_negative_int = cowl_datatype_vocab(v.non_negative_int),
            .non_positive_int = cowl_datatype_vocab(v.non_positive_int),
            .norm_string = cowl_datatype_vocab(v.norm_string),
            .notation = cowl_datatype_vocab(v.notation),
            .positive_int = cowl_datatype_vocab(v.positive_int),
            .q_name = cowl_datatype_vocab(v.q_name),
            .xsd_short = cowl_datatype_vocab(v.xsd_short),
            .string = cowl_datatype_vocab(v.string),
            .time = cowl_datatype_vocab(v.time),
            .token = cowl_datatype_vocab(v.token),
            .unsigned_byte = cowl_datatype_vocab(v.unsigned_byte),
            .unsigned_int = cowl_datatype_vocab(v.unsigned_int),
            .unsigned_long = cowl_datatype_vocab(v.unsigned_long),
            .unsigned_short = cowl_datatype_vocab(v.unsigned_short),
            .year_month_duration = cowl_datatype_vocab(v.year_month_duration)
        }
    };

    return cowl_xsd_vocab_validate();
}

void cowl_xsd_vocab_deinit(void) {
    cowl_string_vocab_free(vocab.ns);

    CowlIRI **iris = (CowlIRI **)&vocab.iri;
    size_t count = sizeof(vocab.iri) / sizeof(CowlIRI*);
    for (size_t i = 0; i < count; ++i) cowl_iri_vocab_free(iris[i]);

    CowlDatatype **dts = (CowlDatatype **)&vocab.dt;
    count = sizeof(vocab.dt) / sizeof(CowlDatatype*);
    for (size_t i = 0; i < count; ++i) cowl_datatype_vocab_free(dts[i]);
}

CowlXSDVocab const* cowl_xsd_vocab(void) {
    return &vocab;
}
