/**
 * Defines CowlXSDVocab.
 *
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
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
typedef cowl_struct(CowlXSDIRIVocab) {

/// @name Datatypes

    /// xsd:anyURI
    CowlIRI *any_uri;

    /// xsd:base64Binary
    CowlIRI *base64_binary;

    /// xsd:boolean
    CowlIRI *boolean;

    /// xsd:byte
    CowlIRI *byte;

    /// xsd:dateTime
    CowlIRI *date_time;

    /// xsd:dateTimeStamp
    CowlIRI *date_timestamp;

    /// xsd:decimal
    CowlIRI *decimal;

    /// xsd:double
    CowlIRI *xsd_double;

    /// xsd:float
    CowlIRI *xsd_float;

    /// xsd:hexBinary
    CowlIRI *hex_binary;

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

    /// xsd:nonNegativeInteger
    CowlIRI *non_negative_int;

    /// xsd:nonPositiveInteger
    CowlIRI *non_positive_int;

    /// xsd:normalizedString
    CowlIRI *norm_string;

    /// xsd:short
    CowlIRI *xsd_short;

    /// xsd:string
    CowlIRI *string;

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
typedef cowl_struct(CowlXSDDatatypeVocab) {

    /// xsd:anyURI
    CowlDatatype *any_uri;

    /// xsd:base64Binary
    CowlDatatype *base64_binary;

    /// xsd:boolean
    CowlDatatype *boolean;

    /// xsd:byte
    CowlDatatype *byte;

    /// xsd:dateTime
    CowlDatatype *date_time;

    /// xsd:dateTimeStamp
    CowlDatatype *date_timestamp;

    /// xsd:decimal
    CowlDatatype *decimal;

    /// xsd:double
    CowlDatatype *xsd_double;

    /// xsd:float
    CowlDatatype *xsd_float;

    /// xsd:hexBinary
    CowlDatatype *hex_binary;

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

    /// xsd:nonNegativeInteger
    CowlDatatype *non_negative_int;

    /// xsd:nonPositiveInteger
    CowlDatatype *non_positive_int;

    /// xsd:normalizedString
    CowlDatatype *norm_string;

    /// xsd:short
    CowlDatatype *xsd_short;

    /// xsd:string
    CowlDatatype *string;

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

} CowlXSDDatatypeVocab;

/// The XSD vocabulary.
typedef cowl_struct(CowlXSDVocab) {

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
