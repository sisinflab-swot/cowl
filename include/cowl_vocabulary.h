/// @author Ivano Bilenchi

#ifndef COWL_VOCABULARY_H
#define COWL_VOCABULARY_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);

cowl_struct(CowlVocabulary) {

    cowl_struct(CowlNSVocabulary) {
        CowlString *owl;
        CowlString *rdf;
        CowlString *xsd;
    } ns;

    cowl_struct(CowlIRIVocabulary) {
        // OWL
        CowlIRI *thing;
        CowlIRI *nothing;

        // RDF
        CowlIRI *rdf_plain_literal;

        // XSD
        CowlIRI *xsd_length;
        CowlIRI *xsd_min_length;
        CowlIRI *xsd_max_length;
        CowlIRI *xsd_pattern;
        CowlIRI *xsd_min_inclusive;
        CowlIRI *xsd_min_exclusive;
        CowlIRI *xsd_max_inclusive;
        CowlIRI *xsd_max_exclusive;
        CowlIRI *xsd_total_digits;
        CowlIRI *xsd_fraction_digits;
        CowlIRI *xsd_lang_range;
    } iri;

    cowl_struct(CowlClassVocabulary) {
        CowlClass *thing;
        CowlClass *nothing;
    } cls;

    cowl_struct(CowlDatatypeVocabulary) {
        CowlDatatype *rdf_plain_literal;
    } dt;
};

cowl_struct_decl(CowlVocabulary);

CowlVocabulary* cowl_vocabulary_get(void);
void cowl_vocabulary_iterate_signature(CowlEntityIterator *iter);

COWL_END_DECLS

#endif // COWL_VOCABULARY_H
