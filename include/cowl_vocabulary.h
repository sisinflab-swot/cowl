/// @author Ivano Bilenchi

#ifndef COWL_VOCABULARY_H
#define COWL_VOCABULARY_H

#include "cowl_iterator.h"
#include "cowl_std.h"

COWL_BEGIN_DECLS

typedef struct CowlClass const CowlClass;
typedef struct CowlIRI const CowlIRI;
typedef struct CowlString const CowlString;

typedef struct CowlVocabulary {
    struct CowlNSVocabulary {
        CowlString *owl;
    } ns;

    struct CowlRemVocabulary {
        CowlString *thing;
        CowlString *nothing;
    } rem;

    struct CowlIRIVocabulary {
        CowlIRI *thing;
        CowlIRI *nothing;
    } iri;

    struct CowlClassVocabulary {
        CowlClass *thing;
        CowlClass *nothing;
    } cls;

} const CowlVocabulary;

CowlVocabulary* cowl_vocabulary_get(void);
void cowl_vocabulary_iterate_signature(void *ctx, CowlEntityIterator iter);

COWL_END_DECLS

#endif // COWL_VOCABULARY_H
