/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_VOCAB_PRIVATE_H
#define COWL_VOCAB_PRIVATE_H

#include "cowl_annot_prop.h"
#include "cowl_class.h"
#include "cowl_data_prop.h"
#include "cowl_datatype.h"
#include "cowl_iri_private.h"
#include "cowl_obj_prop.h"
#include "cowl_std.h"
#include "cowl_string.h"
#include "cowl_vocab.h"

COWL_BEGIN_DECLS

#define cowl_string_vocab(str) cowl_string(ustring_literal(str))
#define cowl_string_vocab_intern(str) cowl_string_opt(ustring_literal(str), COWL_SO_INTERN)
#define cowl_string_vocab_free(STR) ulib_free(STR)

#define cowl_iri_vocab(NS_STR, REM_CSTR) cowl_iri_unvalidated((NS_STR), cowl_string_vocab(REM_CSTR))

#define cowl_iri_vocab_free(IRI)                                                                   \
    do {                                                                                           \
        cowl_string_vocab_free(cowl_iri_get_rem(IRI));                                             \
        ulib_free(IRI);                                                                            \
    } while (0)

#define cowl_annot_prop_vocab(IRI) cowl_annot_prop(IRI)
#define cowl_annot_prop_vocab_free(PROP) ulib_free(PROP)

#define cowl_class_vocab(IRI) cowl_class(IRI)
#define cowl_class_vocab_free(CLS) ulib_free(CLS)

#define cowl_datatype_vocab(IRI) cowl_datatype(IRI)
#define cowl_datatype_vocab_free(DT) ulib_free(DT)

#define cowl_data_prop_vocab(IRI) cowl_data_prop(IRI)
#define cowl_data_prop_vocab_free(PROP) ulib_free(PROP)

#define cowl_obj_prop_vocab(IRI) cowl_obj_prop(IRI)
#define cowl_obj_prop_vocab_free(PROP) ulib_free(PROP)

cowl_ret cowl_vocab_init(void);
void cowl_vocab_deinit(void);

COWL_END_DECLS

#endif // COWL_VOCAB_PRIVATE_H
