/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://sisinflab.poliba.it/swottools>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_VOCAB_UTILS_H
#define COWL_VOCAB_UTILS_H

#include "cowl_std.h"
#include "cowl_alloc.h"
#include "cowl_annot_prop.h"
#include "cowl_class.h"
#include "cowl_data_prop.h"
#include "cowl_datatype.h"
#include "cowl_iri_private.h"
#include "cowl_obj_prop.h"
#include "cowl_string_private.h"

COWL_BEGIN_DECLS

#define cowl_string_vocab_get(CSTR) \
    cowl_string_get((CSTR), sizeof(CSTR) - 1, false)

#define cowl_string_vocab_free(STR) cowl_free(STR)

#define cowl_iri_vocab_get(NS_STR, REM_CSTR) \
    cowl_iri_unvalidated_get((NS_STR), cowl_string_vocab_get(REM_CSTR))

#define cowl_iri_vocab_free(IRI) do {                                                               \
    cowl_string_vocab_free((IRI)->rem);                                                             \
    cowl_free(IRI);                                                                                 \
} while(0)

#define cowl_annot_prop_vocab_get(IRI) cowl_annot_prop_get(IRI)
#define cowl_annot_prop_vocab_free(PROP) cowl_free(PROP)

#define cowl_class_vocab_get(IRI) cowl_class_get(IRI)
#define cowl_class_vocab_free(CLS) cowl_free(CLS)

#define cowl_datatype_vocab_get(IRI) cowl_datatype_get(IRI)
#define cowl_datatype_vocab_free(DT) cowl_free(DT)

#define cowl_data_prop_vocab_get(IRI) cowl_data_prop_get(IRI)
#define cowl_data_prop_vocab_free(PROP) cowl_free(PROP)

#define cowl_obj_prop_vocab_get(IRI) cowl_obj_prop_get(IRI)
#define cowl_obj_prop_vocab_free(PROP) cowl_free(PROP)

COWL_END_DECLS

#endif // COWL_VOCAB_UTILS_H
