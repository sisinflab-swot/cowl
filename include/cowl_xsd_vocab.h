/**
 * Defines CowlXSDVocab.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_XSD_VOCAB_H
#define COWL_XSD_VOCAB_H

#include "cowl_std.h"

COWL_BEGIN_DECLS

/// @cond
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);
/// @endcond

/// Vocabulary of XSD IRIs.
typedef struct CowlXSDIRIVocab {

/// @name Datatypes

    /// xsd:anyAtomicType
    CowlIRI *any_atomic_type;

    /// xsd:anySimpleType
    CowlIRI *any_simple_type;

    /// xsd:anyType
    CowlIRI *any_type;

    /// xsd:anyURI
    CowlIRI *any_uri;

    /// xsd:base64Binary
    CowlIRI *base64_binary;

    /// xsd:boolean
    CowlIRI *boolean;

    /// xsd:byte
    CowlIRI *byte;

    /// xsd:date
    CowlIRI *date;

    /// xsd:dateTime
    CowlIRI *date_time;

    /// xsd:dateTimeStamp
    CowlIRI *date_timestamp;

    /// xsd:dayTimeDuration
    CowlIRI *day_time_duration;

    /// xsd:decimal
    CowlIRI *decimal;

    /// xsd:double
    CowlIRI *xsd_double;

    /// xsd:duration
    CowlIRI *duration;

    /// xsd:ENTITIES
    CowlIRI *entities;

    /// xsd:ENTITY
    CowlIRI *entity;

    /// xsd:float
    CowlIRI *xsd_float;

    /// xsd:gDay
    CowlIRI *g_day;

    /// xsd:gMonth
    CowlIRI *g_month;

    /// xsd:gMonthDay
    CowlIRI *g_month_day;

    /// xsd:gYear
    CowlIRI *g_year;

    /// xsd:gYearMonth
    CowlIRI *g_year_month;

    /// xsd:hexBinary
    CowlIRI *hex_binary;

    /// xsd:ID
    CowlIRI *id;

    /// xsd:IDREF
    CowlIRI *id_ref;

    /// xsd:IDREFS
    CowlIRI *id_refs;

    /// xsd:int
    CowlIRI *xsd_int;

    /// xsd:integer
    CowlIRI *integer;

    /// xsd:language
    CowlIRI *language;

    /// xsd:long
    CowlIRI *xsd_long;

    /// xsd:Name
    CowlIRI *name;

    /// xsd:NCName
    CowlIRI *ncname;

    /// xsd:negativeInteger
    CowlIRI *negative_int;

    /// xsd:NMTOKEN
    CowlIRI *nmtoken;

    /// xsd:NMTOKENS
    CowlIRI *nmtokens;

    /// xsd:nonNegativeInteger
    CowlIRI *non_negative_int;

    /// xsd:nonPositiveInteger
    CowlIRI *non_positive_int;

    /// xsd:normalizedString
    CowlIRI *norm_string;

    /// xsd:NOTATION
    CowlIRI *notation;

    /// xsd:positiveInteger
    CowlIRI *positive_int;

    /// xsd:QName
    CowlIRI *q_name;

    /// xsd:short
    CowlIRI *xsd_short;

    /// xsd:string
    CowlIRI *string;

    /// xsd:time
    CowlIRI *time;

    /// xsd:token
    CowlIRI *token;

    /// xsd:unsignedByte
    CowlIRI *unsigned_byte;

    /// xsd:unsignedInt
    CowlIRI *unsigned_int;

    /// xsd:unsignedLong
    CowlIRI *unsigned_long;

    /// xsd:unsignedShort
    CowlIRI *unsigned_short;

    /// xsd:yearMonthDuration
    CowlIRI *year_month_duration;

/// @name Facets

    /// xsd:length
    CowlIRI *length;

    /// xsd:minLength
    CowlIRI *min_length;

    /// xsd:maxLength
    CowlIRI *max_length;

    /// xsd:pattern
    CowlIRI *pattern;

    /// xsd:minInclusive
    CowlIRI *min_inclusive;

    /// xsd:minExclusive
    CowlIRI *min_exclusive;

    /// xsd:maxInclusive
    CowlIRI *max_inclusive;

    /// xsd:maxExclusive
    CowlIRI *max_exclusive;

    /// xsd:totalDigits
    CowlIRI *total_digits;

    /// xsd:fractionDigits
    CowlIRI *fraction_digits;

} CowlXSDIRIVocab;

/// Vocabulary of XSD datatypes.
typedef struct CowlXSDDatatypeVocab {

    /// xsd:anyAtomicType
    CowlDatatype *any_atomic_type;

    /// xsd:anySimpleType
    CowlDatatype *any_simple_type;

    /// xsd:anyType
    CowlDatatype *any_type;

    /// xsd:anyURI
    CowlDatatype *any_uri;

    /// xsd:base64Binary
    CowlDatatype *base64_binary;

    /// xsd:boolean
    CowlDatatype *boolean;

    /// xsd:byte
    CowlDatatype *byte;

    /// xsd:date
    CowlDatatype *date;

    /// xsd:dateTime
    CowlDatatype *date_time;

    /// xsd:dateTimeStamp
    CowlDatatype *date_timestamp;

    /// xsd:dayTimeDuration
    CowlDatatype *day_time_duration;

    /// xsd:decimal
    CowlDatatype *decimal;

    /// xsd:double
    CowlDatatype *xsd_double;

    /// xsd:duration
    CowlDatatype *duration;

    /// xsd:ENTITIES
    CowlDatatype *entities;

    /// xsd:ENTITY
    CowlDatatype *entity;

    /// xsd:float
    CowlDatatype *xsd_float;

    /// xsd:gDay
    CowlDatatype *g_day;

    /// xsd:gMonth
    CowlDatatype *g_month;

    /// xsd:gMonthDay
    CowlDatatype *g_month_day;

    /// xsd:gYear
    CowlDatatype *g_year;

    /// xsd:gYearMonth
    CowlDatatype *g_year_month;

    /// xsd:hexBinary
    CowlDatatype *hex_binary;

    /// xsd:ID
    CowlDatatype *id;

    /// xsd:IDREF
    CowlDatatype *id_ref;

    /// xsd:IDREFS
    CowlDatatype *id_refs;

    /// xsd:int
    CowlDatatype *xsd_int;

    /// xsd:integer
    CowlDatatype *integer;

    /// xsd:language
    CowlDatatype *language;

    /// xsd:long
    CowlDatatype *xsd_long;

    /// xsd:Name
    CowlDatatype *name;

    /// xsd:NCName
    CowlDatatype *ncname;

    /// xsd:negativeInteger
    CowlDatatype *negative_int;

    /// xsd:NMTOKEN
    CowlDatatype *nmtoken;

    /// xsd:NMTOKENS
    CowlDatatype *nmtokens;

    /// xsd:nonNegativeInteger
    CowlDatatype *non_negative_int;

    /// xsd:nonPositiveInteger
    CowlDatatype *non_positive_int;

    /// xsd:normalizedString
    CowlDatatype *norm_string;

    /// xsd:NOTATION
    CowlDatatype *notation;

    /// xsd:positiveInteger
    CowlDatatype *positive_int;

    /// xsd:QName
    CowlDatatype *q_name;

    /// xsd:short
    CowlDatatype *xsd_short;

    /// xsd:string
    CowlDatatype *string;

    /// xsd:time
    CowlDatatype *time;

    /// xsd:token
    CowlDatatype *token;

    /// xsd:unsignedByte
    CowlDatatype *unsigned_byte;

    /// xsd:unsignedInt
    CowlDatatype *unsigned_int;

    /// xsd:unsignedLong
    CowlDatatype *unsigned_long;

    /// xsd:unsignedShort
    CowlDatatype *unsigned_short;

    /// xsd:yearMonthDuration
    CowlDatatype *year_month_duration;

} CowlXSDDatatypeVocab;

/// The XSD vocabulary.
typedef struct CowlXSDVocab {

    /// XSD namespace.
    CowlString *ns;

    /// IRIs sub-vocabulary.
    CowlXSDIRIVocab iri;

    /// Datatypes sub-vocabulary.
    CowlXSDDatatypeVocab dt;

} const CowlXSDVocab;

/**
 * Gets the XSD vocabulary.
 *
 * @return The XSD vocabulary.
 *
 * @public @memberof CowlXSDVocab
 */
COWL_PUBLIC
CowlXSDVocab* cowl_xsd_vocab_get(void);

COWL_END_DECLS

#endif // COWL_XSD_VOCAB_H
