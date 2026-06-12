/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2026 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 */

#include "cowl_axiom_tests.h"
#include "cowl.h"
#include "cowl_test_utils.h"
#include "ulib.h"
#include <stddef.h>

#define test_iri_prefix "http://test.org/axiom#"

static CowlVector *make_vector(CowlAny *const items[], ulib_uint count) {
    UVec(CowlObjectPtr) vec = uvec(CowlObjectPtr);

    for (ulib_uint i = 0; i < count; ++i) {
        uvec_push(CowlObjectPtr, &vec, items[i]);
    }

    return cowl_vector(&vec);
}

void cowl_test_axiom_equals(void) {
    CowlClass *class_a = cowl_class_from_literal(test_iri_prefix "A");
    CowlClass *class_b = cowl_class_from_literal(test_iri_prefix "B");
    CowlDeclAxiom *decl_a = cowl_decl_axiom(class_a, NULL);
    CowlDeclAxiom *decl_a_copy = cowl_decl_axiom(class_a, NULL);
    CowlDeclAxiom *decl_b = cowl_decl_axiom(class_b, NULL);
    CowlSubClsAxiom *sub_ax = cowl_sub_cls_axiom(class_a, class_b, NULL);

    utest_assert(cowl_equals(decl_a, decl_a_copy));
    utest_assert(cowl_axiom_equals(decl_a, decl_a_copy, true));
    utest_assert_false(cowl_equals(decl_a, decl_b));
    utest_assert_false(cowl_axiom_equals(decl_a, decl_b, true));
    utest_assert_false(cowl_equals(decl_a, sub_ax));
    utest_assert_false(cowl_axiom_equals(decl_a, sub_ax, true));

    CowlAnnotProp *annot_prop = cowl_annot_prop_from_literal(test_iri_prefix "annot");
    CowlLiteral *annot_literal = cowl_literal_plain(ustring_literal("annot-value"));
    CowlAnnotation *annotation = cowl_annotation(annot_prop, annot_literal, NULL);
    CowlAny *annot_items[] = { annotation };
    CowlVector *annot_vec = make_vector(annot_items, ulib_array_count(annot_items));
    CowlDeclAxiom *decl_a_annot = cowl_decl_axiom(class_a, annot_vec);

    utest_assert_false(cowl_equals(decl_a, decl_a_annot));
    utest_assert(cowl_axiom_equals(decl_a, decl_a_annot, false));
    utest_assert_false(cowl_axiom_equals(decl_a, decl_a_annot, true));

    cowl_release_all(decl_a, decl_a_copy, decl_b, sub_ax, decl_a_annot, annot_vec, annotation,
                     annot_literal, annot_prop, class_a, class_b);
}

void cowl_test_axiom_operands(void) {
    CowlClass *class_a = cowl_class_from_literal(test_iri_prefix "A");
    CowlClass *class_b = cowl_class_from_literal(test_iri_prefix "B");

    CowlObjProp *prop_p = cowl_obj_prop_from_literal(test_iri_prefix "p");
    CowlObjProp *prop_q = cowl_obj_prop_from_literal(test_iri_prefix "q");
    CowlDataProp *data_prop_r = cowl_data_prop_from_literal(test_iri_prefix "r");

    CowlNamedInd *ind_s = cowl_named_ind_from_literal(test_iri_prefix "s");
    CowlNamedInd *ind_o = cowl_named_ind_from_literal(test_iri_prefix "o");

    CowlSubClsAxiom *sub_ax = cowl_sub_cls_axiom(class_a, class_b, NULL);
    CowlObjPropAssertAxiom *assert_ax = cowl_obj_prop_assert_axiom(prop_p, ind_s, ind_o, NULL);

    CowlAny *obj_props_items[] = { prop_p, prop_q };
    CowlAny *data_props_items[] = { data_prop_r };
    CowlVector *obj_props = make_vector(obj_props_items, ulib_array_count(obj_props_items));
    CowlVector *data_props = make_vector(data_props_items, ulib_array_count(data_props_items));
    CowlHasKeyAxiom *key_ax = cowl_has_key_axiom(class_a, obj_props, data_props, NULL);

    utest_assert(cowl_axiom_has_operand(sub_ax, class_a, COWL_PS_LEFT));
    utest_assert(cowl_axiom_has_operand(sub_ax, class_b, COWL_PS_RIGHT));
    utest_assert_false(cowl_axiom_has_operand(sub_ax, class_a, COWL_PS_RIGHT));
    utest_assert_false(cowl_axiom_has_operand(sub_ax, class_b, COWL_PS_LEFT));

    utest_assert(cowl_axiom_has_operand(key_ax, prop_p, COWL_PS_MIDDLE));
    utest_assert(cowl_axiom_has_operand(key_ax, prop_q, COWL_PS_MIDDLE));
    utest_assert(cowl_axiom_has_operand(key_ax, class_a, COWL_PS_LEFT));
    utest_assert(cowl_axiom_has_operand(key_ax, data_prop_r, COWL_PS_RIGHT));
    utest_assert_false(cowl_axiom_has_operand(key_ax, class_a, COWL_PS_MIDDLE));
    utest_assert_false(cowl_axiom_has_operand(key_ax, data_prop_r, COWL_PS_LEFT));

    CowlIRI *iri = cowl_get_iri(prop_p);
    utest_assert(cowl_axiom_has_operand_with_iri(assert_ax, iri, COWL_PS_PREDICATE));
    iri = cowl_get_iri(ind_s);
    utest_assert(cowl_axiom_has_operand_with_iri(assert_ax, iri, COWL_PS_SUBJECT));
    iri = cowl_get_iri(ind_o);
    utest_assert(cowl_axiom_has_operand_with_iri(assert_ax, iri, COWL_PS_OBJECT));
    iri = cowl_get_iri(prop_p);
    utest_assert_false(cowl_axiom_has_operand_with_iri(assert_ax, iri, COWL_PS_OBJECT));
    iri = cowl_get_iri(class_a);
    utest_assert_false(cowl_axiom_has_operand_with_iri(assert_ax, iri, COWL_PS_ANY));

    ulib_uint count = 0;
    CowlIterator iter = cowl_iterator_count(&count);
    cowl_assert_ok(cowl_axiom_iterate_operands(key_ax, COWL_PS_ANY, &iter));
    utest_assert_uint(count, ==, 4);

    count = 0;
    iter = cowl_iterator_count(&count);
    cowl_assert_ok(cowl_axiom_iterate_operands(key_ax, COWL_PS_LEFT, &iter));
    utest_assert_uint(count, ==, 1);

    count = 0;
    iter = cowl_iterator_count(&count);
    cowl_assert_ok(cowl_axiom_iterate_operands(key_ax, COWL_PS_MIDDLE, &iter));
    utest_assert_uint(count, ==, 2);

    count = 0;
    iter = cowl_iterator_count(&count);
    cowl_assert_ok(cowl_axiom_iterate_operands(key_ax, COWL_PS_RIGHT, &iter));
    utest_assert_uint(count, ==, 1);

    iter = cowl_iterator_contains(prop_q);
    utest_assert_enum(cowl_axiom_iterate_operands(key_ax, COWL_PS_MIDDLE, &iter), ==, COWL_STOP);
    iter = cowl_iterator_contains(prop_q);
    utest_assert_enum(cowl_axiom_iterate_operands(key_ax, COWL_PS_RIGHT, &iter), ==, COWL_CONTINUE);

    cowl_release_all(class_a, class_b, prop_p, prop_q, data_prop_r, ind_s, ind_o, sub_ax, assert_ax,
                     obj_props, data_props, key_ax);
}

void cowl_test_axiom_primitives(void) {
    CowlClass *class_a = cowl_class_from_literal(test_iri_prefix "A");
    CowlClass *class_b = cowl_class_from_literal(test_iri_prefix "B");
    CowlObjProp *prop_p = cowl_obj_prop_from_literal(test_iri_prefix "p");
    CowlNamedInd *ind_s = cowl_named_ind_from_literal(test_iri_prefix "s");

    CowlSubClsAxiom *sub_ax = cowl_sub_cls_axiom(class_a, class_b, NULL);
    CowlObjPropAssertAxiom *assert_ax = cowl_obj_prop_assert_axiom(prop_p, ind_s, ind_s, NULL);

    utest_assert(cowl_axiom_has_primitive(sub_ax, class_a, COWL_PS_LEFT));
    utest_assert(cowl_axiom_has_primitive(sub_ax, class_b, COWL_PS_RIGHT));
    utest_assert_false(cowl_axiom_has_primitive(sub_ax, class_a, COWL_PS_RIGHT));
    utest_assert_false(cowl_axiom_has_primitive(sub_ax, class_b, COWL_PS_LEFT));

    utest_assert(cowl_axiom_has_primitive(assert_ax, prop_p, COWL_PS_PREDICATE));
    utest_assert(cowl_axiom_has_primitive(assert_ax, ind_s, COWL_PS_SUBJECT));
    utest_assert(cowl_axiom_has_primitive(assert_ax, ind_s, COWL_PS_OBJECT));
    utest_assert_false(cowl_axiom_has_primitive(assert_ax, prop_p, COWL_PS_OBJECT));
    utest_assert_false(cowl_axiom_has_primitive(assert_ax, class_a, COWL_PS_ANY));

    cowl_release_all(class_a, class_b, prop_p, ind_s, sub_ax, assert_ax);
}
