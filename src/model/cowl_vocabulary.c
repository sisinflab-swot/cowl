/// @author Ivano Bilenchi

#include "cowl_vocabulary.h"

#pragma mark - Private

#define COWL_IRI_STRING(ns, rem) ns rem

#define COWL_OWL_NS "http://www.w3.org/2002/07/owl#"

#define COWL_OWL_THING_REM "Thing"
#define COWL_OWL_NOTHING_REM "Nothing"

#pragma mark - Namespaces

char const *cowl_vocab_owl_ns = COWL_OWL_NS;

#pragma mark - Remainders

char const *cowl_vocab_owl_thing_rem = COWL_OWL_THING_REM;
char const *cowl_vocab_owl_nothing_rem = COWL_OWL_NOTHING_REM;

#pragma mark - Full IRIs

char const *cowl_vocab_owl_thing = COWL_IRI_STRING(COWL_OWL_NS, COWL_OWL_THING_REM);
char const *cowl_vocab_owl_nothing = COWL_IRI_STRING(COWL_OWL_NS, COWL_OWL_NOTHING_REM);
