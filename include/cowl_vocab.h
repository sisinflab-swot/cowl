/// @author Ivano Bilenchi

#ifndef COWL_VOCAB_H
#define COWL_VOCAB_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlClass);
cowl_struct_decl(CowlDatatype);
cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlString);

cowl_struct(CowlOWLVocab) {
    CowlString *ns;

    struct {
        CowlIRI *thing;
        CowlIRI *nothing;
    } iri;

    struct {
        CowlClass *thing;
        CowlClass *nothing;
    } cls;
};

cowl_struct(CowlRDFVocab) {
    CowlString *ns;

    struct {
        CowlIRI *plain_literal;
    } iri;

    struct {
        CowlDatatype *plain_literal;
    } dt;
};

cowl_struct(CowlXSDVocab) {
    CowlString *ns;

    struct {
        CowlIRI *length;
        CowlIRI *min_length;
        CowlIRI *max_length;
        CowlIRI *pattern;
        CowlIRI *min_inclusive;
        CowlIRI *min_exclusive;
        CowlIRI *max_inclusive;
        CowlIRI *max_exclusive;
        CowlIRI *total_digits;
        CowlIRI *fraction_digits;
        CowlIRI *lang_range;
    } iri;
};

cowl_struct_decl(CowlOWLVocab);
cowl_struct_decl(CowlRDFVocab);
cowl_struct_decl(CowlXSDVocab);

CowlOWLVocab* cowl_owl_vocab_get(void);
CowlRDFVocab* cowl_rdf_vocab_get(void);
CowlXSDVocab* cowl_xsd_vocab_get(void);

COWL_END_DECLS

#endif // COWL_VOCAB_H
