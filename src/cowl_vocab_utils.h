/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_VOCAB_UTILS_H
#define COWL_VOCAB_UTILS_H

#include "cowl_std.h"
#include "cowl_annot_prop.h"
#include "cowl_class.h"
#include "cowl_data_prop.h"
#include "cowl_datatype.h"
#include "cowl_iri_private.h"
#include "cowl_obj_prop.h"
#include "cowl_string_private.h"

COWL_BEGIN_DECLS

#define cowl_string_vocab_get(CSTR) \
    cowl_string_get(ustring_literal(CSTR))

#define cowl_string_vocab_free(STR) ulib_free(STR)

#define cowl_iri_vocab_get(NS_STR, REM_CSTR) \
    cowl_iri_unvalidated_get((NS_STR), cowl_string_vocab_get(REM_CSTR))

#define cowl_iri_vocab_free(IRI) do {                                                               \
    cowl_string_vocab_free((IRI)->rem);                                                             \
    ulib_free(IRI);                                                                                 \
} while(0)

#define cowl_annot_prop_vocab_get(IRI) cowl_annot_prop_get(IRI)
#define cowl_annot_prop_vocab_free(PROP) ulib_free(PROP)

#define cowl_class_vocab_get(IRI) cowl_class_get(IRI)
#define cowl_class_vocab_free(CLS) ulib_free(CLS)

#define cowl_datatype_vocab_get(IRI) cowl_datatype_get(IRI)
#define cowl_datatype_vocab_free(DT) ulib_free(DT)

#define cowl_data_prop_vocab_get(IRI) cowl_data_prop_get(IRI)
#define cowl_data_prop_vocab_free(PROP) ulib_free(PROP)

#define cowl_obj_prop_vocab_get(IRI) cowl_obj_prop_get(IRI)
#define cowl_obj_prop_vocab_free(PROP) ulib_free(PROP)

COWL_END_DECLS

#endif // COWL_VOCAB_UTILS_H
