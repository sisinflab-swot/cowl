/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#include "cowl_xsd_vocab_private.h"
#include "cowl_vocab_utils.h"

static cowl_struct(CowlXSDVocab) vocab;

void cowl_xsd_vocab_init(void) {
    CowlString *ns = cowl_string_vocab_get("http://www.w3.org/2001/XMLSchema#");

    CowlXSDIRIVocab v = {
        .any_uri = cowl_iri_vocab_get(ns, "anyURI"),
        .base64_binary = cowl_iri_vocab_get(ns, "base64Binary"),
        .boolean = cowl_iri_vocab_get(ns, "boolean"),
        .byte = cowl_iri_vocab_get(ns, "byte"),
        .date_time = cowl_iri_vocab_get(ns, "dateTime"),
        .date_timestamp = cowl_iri_vocab_get(ns, "dateTimeStamp"),
        .decimal = cowl_iri_vocab_get(ns, "decimal"),
        .xsd_double = cowl_iri_vocab_get(ns, "double"),
        .xsd_float = cowl_iri_vocab_get(ns, "float"),
        .hex_binary = cowl_iri_vocab_get(ns, "hexBinary"),
        .xsd_int = cowl_iri_vocab_get(ns, "int"),
        .integer = cowl_iri_vocab_get(ns, "integer"),
        .language = cowl_iri_vocab_get(ns, "language"),
        .xsd_long = cowl_iri_vocab_get(ns, "long"),
        .name = cowl_iri_vocab_get(ns, "Name"),
        .ncname = cowl_iri_vocab_get(ns, "NCName"),
        .negative_int = cowl_iri_vocab_get(ns, "negativeInteger"),
        .nmtoken = cowl_iri_vocab_get(ns, "NMTOKEN"),
        .non_negative_int = cowl_iri_vocab_get(ns, "nonNegativeInteger"),
        .non_positive_int = cowl_iri_vocab_get(ns, "nonPositiveInteger"),
        .norm_string = cowl_iri_vocab_get(ns, "normalizedString"),
        .xsd_short = cowl_iri_vocab_get(ns, "short"),
        .string = cowl_iri_vocab_get(ns, "string"),
        .token = cowl_iri_vocab_get(ns, "token"),
        .unsigned_byte = cowl_iri_vocab_get(ns, "unsignedByte"),
        .unsigned_int = cowl_iri_vocab_get(ns, "unsignedInt"),
        .unsigned_long = cowl_iri_vocab_get(ns, "unsignedLong"),
        .unsigned_short = cowl_iri_vocab_get(ns, "unsignedShort"),
        .length = cowl_iri_vocab_get(ns, "length"),
        .min_length = cowl_iri_vocab_get(ns, "minLength"),
        .max_length = cowl_iri_vocab_get(ns, "maxLength"),
        .pattern = cowl_iri_vocab_get(ns, "pattern"),
        .min_inclusive = cowl_iri_vocab_get(ns, "minInclusive"),
        .min_exclusive = cowl_iri_vocab_get(ns, "minExclusive"),
        .max_inclusive = cowl_iri_vocab_get(ns, "maxInclusive"),
        .max_exclusive = cowl_iri_vocab_get(ns, "maxExclusive"),
        .total_digits = cowl_iri_vocab_get(ns, "totalDigits"),
        .fraction_digits = cowl_iri_vocab_get(ns, "fractionDigits")
    };

    vocab = (cowl_struct(CowlXSDVocab)) {
        .ns = ns,
        .iri = v,
        .dt = {
            .any_uri = cowl_datatype_vocab_get(v.any_uri),
            .base64_binary = cowl_datatype_vocab_get(v.base64_binary),
            .boolean = cowl_datatype_vocab_get(v.boolean),
            .byte = cowl_datatype_vocab_get(v.byte),
            .date_time = cowl_datatype_vocab_get(v.date_time),
            .date_timestamp = cowl_datatype_vocab_get(v.date_timestamp),
            .decimal = cowl_datatype_vocab_get(v.decimal),
            .xsd_double = cowl_datatype_vocab_get(v.xsd_double),
            .xsd_float = cowl_datatype_vocab_get(v.xsd_float),
            .hex_binary = cowl_datatype_vocab_get(v.hex_binary),
            .xsd_int = cowl_datatype_vocab_get(v.xsd_int),
            .integer = cowl_datatype_vocab_get(v.integer),
            .language = cowl_datatype_vocab_get(v.language),
            .xsd_long = cowl_datatype_vocab_get(v.xsd_long),
            .name = cowl_datatype_vocab_get(v.name),
            .ncname = cowl_datatype_vocab_get(v.ncname),
            .negative_int = cowl_datatype_vocab_get(v.negative_int),
            .nmtoken = cowl_datatype_vocab_get(v.nmtoken),
            .non_negative_int = cowl_datatype_vocab_get(v.non_negative_int),
            .non_positive_int = cowl_datatype_vocab_get(v.non_positive_int),
            .norm_string = cowl_datatype_vocab_get(v.norm_string),
            .xsd_short = cowl_datatype_vocab_get(v.xsd_short),
            .string = cowl_datatype_vocab_get(v.string),
            .token = cowl_datatype_vocab_get(v.token),
            .unsigned_byte = cowl_datatype_vocab_get(v.unsigned_byte),
            .unsigned_int = cowl_datatype_vocab_get(v.unsigned_int),
            .unsigned_long = cowl_datatype_vocab_get(v.unsigned_long),
            .unsigned_short = cowl_datatype_vocab_get(v.unsigned_short)
        }
    };
}

void cowl_xsd_vocab_deinit(void) {
    cowl_string_vocab_free(vocab.ns);

    cowl_iri_vocab_free(vocab.iri.any_uri);
    cowl_iri_vocab_free(vocab.iri.base64_binary);
    cowl_iri_vocab_free(vocab.iri.boolean);
    cowl_iri_vocab_free(vocab.iri.byte);
    cowl_iri_vocab_free(vocab.iri.date_time);
    cowl_iri_vocab_free(vocab.iri.date_timestamp);
    cowl_iri_vocab_free(vocab.iri.decimal);
    cowl_iri_vocab_free(vocab.iri.xsd_double);
    cowl_iri_vocab_free(vocab.iri.xsd_float);
    cowl_iri_vocab_free(vocab.iri.hex_binary);
    cowl_iri_vocab_free(vocab.iri.xsd_int);
    cowl_iri_vocab_free(vocab.iri.integer);
    cowl_iri_vocab_free(vocab.iri.language);
    cowl_iri_vocab_free(vocab.iri.xsd_long);
    cowl_iri_vocab_free(vocab.iri.name);
    cowl_iri_vocab_free(vocab.iri.ncname);
    cowl_iri_vocab_free(vocab.iri.negative_int);
    cowl_iri_vocab_free(vocab.iri.nmtoken);
    cowl_iri_vocab_free(vocab.iri.non_negative_int);
    cowl_iri_vocab_free(vocab.iri.non_positive_int);
    cowl_iri_vocab_free(vocab.iri.norm_string);
    cowl_iri_vocab_free(vocab.iri.xsd_short);
    cowl_iri_vocab_free(vocab.iri.string);
    cowl_iri_vocab_free(vocab.iri.token);
    cowl_iri_vocab_free(vocab.iri.unsigned_byte);
    cowl_iri_vocab_free(vocab.iri.unsigned_int);
    cowl_iri_vocab_free(vocab.iri.unsigned_long);
    cowl_iri_vocab_free(vocab.iri.unsigned_short);
    cowl_iri_vocab_free(vocab.iri.length);
    cowl_iri_vocab_free(vocab.iri.min_length);
    cowl_iri_vocab_free(vocab.iri.max_length);
    cowl_iri_vocab_free(vocab.iri.pattern);
    cowl_iri_vocab_free(vocab.iri.min_inclusive);
    cowl_iri_vocab_free(vocab.iri.min_exclusive);
    cowl_iri_vocab_free(vocab.iri.max_inclusive);
    cowl_iri_vocab_free(vocab.iri.max_exclusive);
    cowl_iri_vocab_free(vocab.iri.total_digits);
    cowl_iri_vocab_free(vocab.iri.fraction_digits);

    cowl_datatype_vocab_free(vocab.dt.any_uri);
    cowl_datatype_vocab_free(vocab.dt.base64_binary);
    cowl_datatype_vocab_free(vocab.dt.boolean);
    cowl_datatype_vocab_free(vocab.dt.byte);
    cowl_datatype_vocab_free(vocab.dt.date_time);
    cowl_datatype_vocab_free(vocab.dt.date_timestamp);
    cowl_datatype_vocab_free(vocab.dt.decimal);
    cowl_datatype_vocab_free(vocab.dt.xsd_double);
    cowl_datatype_vocab_free(vocab.dt.xsd_float);
    cowl_datatype_vocab_free(vocab.dt.hex_binary);
    cowl_datatype_vocab_free(vocab.dt.xsd_int);
    cowl_datatype_vocab_free(vocab.dt.integer);
    cowl_datatype_vocab_free(vocab.dt.language);
    cowl_datatype_vocab_free(vocab.dt.xsd_long);
    cowl_datatype_vocab_free(vocab.dt.name);
    cowl_datatype_vocab_free(vocab.dt.ncname);
    cowl_datatype_vocab_free(vocab.dt.negative_int);
    cowl_datatype_vocab_free(vocab.dt.nmtoken);
    cowl_datatype_vocab_free(vocab.dt.non_negative_int);
    cowl_datatype_vocab_free(vocab.dt.non_positive_int);
    cowl_datatype_vocab_free(vocab.dt.norm_string);
    cowl_datatype_vocab_free(vocab.dt.xsd_short);
    cowl_datatype_vocab_free(vocab.dt.string);
    cowl_datatype_vocab_free(vocab.dt.token);
    cowl_datatype_vocab_free(vocab.dt.unsigned_byte);
    cowl_datatype_vocab_free(vocab.dt.unsigned_int);
    cowl_datatype_vocab_free(vocab.dt.unsigned_long);
    cowl_datatype_vocab_free(vocab.dt.unsigned_short);
}

CowlXSDVocab* cowl_xsd_vocab_get(void) {
    return &vocab;
}
