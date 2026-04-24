/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

#ifndef COWL_TEST_UTILS_H
#define COWL_TEST_UTILS_H

#include "cowl_attrs.h"
#include "cowl_utils.h"
#include "ulib.h"

COWL_BEGIN_DECLS

cowl_struct_decl(CowlIRI);
cowl_struct_decl(CowlOntology);

// Test utils

#define cowl_assert_equal(T, lhs, rhs)                                                             \
    do {                                                                                           \
        if (!cowl_equals(lhs, rhs)) {                                                              \
            UString T##_lhs_str = cowl_to_string(lhs);                                             \
            UString T##_rhs_str = cowl_to_string(rhs);                                             \
            utest_log_failure_reason("\"" #lhs "\" must be equal to \"%s\", found \"%s\".",        \
                                     ustring_data(T##_rhs_str), ustring_data(T##_lhs_str));        \
            ustring_deinit(&T##_lhs_str);                                                          \
            ustring_deinit(&T##_rhs_str);                                                          \
            utest_fail();                                                                          \
        }                                                                                          \
    } while (0)

#define cowl_assert_not_equal(T, lhs, rhs)                                                         \
    do {                                                                                           \
        if (cowl_equals(lhs, rhs)) {                                                               \
            UString T##_rhs_str = cowl_to_string(rhs);                                             \
            utest_log_failure_reason("\"" #lhs "\" must not be equal to \"%s\".",                  \
                                     ustring_data(T##_rhs_str));                                   \
            ustring_deinit(&T##_rhs_str);                                                          \
            utest_fail();                                                                          \
        }                                                                                          \
    } while (0)

#define cowl_assert_ok(ret) utest_assert_enum(ret, ==, COWL_OK)

// Test data

#define COWL_TEST_ONTOLOGY "test_onto.owl"
#define COWL_TEST_IMPORT "test_import.owl"

COWL_END_DECLS

#endif // COWL_TEST_UTILS_H
