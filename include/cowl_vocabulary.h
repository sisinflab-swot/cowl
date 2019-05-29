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
    } ns;

    cowl_struct(CowlRemVocabulary) {
        CowlString *thing;
        CowlString *nothing;
        CowlString *plain_literal;
    } rem;

    cowl_struct(CowlIRIVocabulary) {
        CowlIRI *thing;
        CowlIRI *nothing;
        CowlIRI *plain_literal;
    } iri;

    cowl_struct(CowlClassVocabulary) {
        CowlClass *thing;
        CowlClass *nothing;
    } cls;

    cowl_struct(CowlDatatypeVocabulary) {
        CowlDatatype *plain_literal;
    } dt;
};

cowl_struct_decl(CowlVocabulary);

CowlVocabulary* cowl_vocabulary_get(void);
void cowl_vocabulary_iterate_signature(void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_VOCABULARY_H
