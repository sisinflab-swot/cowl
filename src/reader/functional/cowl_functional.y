/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2022 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

// API configuration

%define api.prefix {cowl_func_yy}
%define api.pure full
%lex-param {yyscan_t scanner}
%parse-param {yyscan_t scanner}
%parse-param {CowlEditor *editor}
%locations

// Code

%code provides {
    #undef YYSTYPE
    #undef YYLTYPE

    #define YYSTYPE COWL_FUNC_YYSTYPE
    #define YYLTYPE COWL_FUNC_YYLTYPE

    #define YYMALLOC ulib_malloc
    #define YYFREE ulib_free
}

%code requires {
    #include "cowl_std.h"
    #include "cowl_types.h"

    #ifndef YY_TYPEDEF_YY_SCANNER_T
    #define YY_TYPEDEF_YY_SCANNER_T
    typedef void* yyscan_t;
    #endif
}

%code top {
    #include "cowl_func_yyparser.h"
    #include "cowl_func_yylexer.h"
    #include "cowl_private.h"

    #define COWL_HANDLE_ERROR(CODE) cowl_handle_error_code((CODE), editor->ontology)
    #define COWL_HANDLE_MEM_ERROR() cowl_handle_error_code(COWL_ERR_MEM, editor->ontology)
    #define COWL_HANDLE_SYNTAX_ERROR(DESC)                                                          \
        cowl_handle_syntax_error((DESC), editor->ontology,                                          \
                                 (CowlErrorLoc) { .line = yylloc.last_line })

    static void cowl_func_yyerror(COWL_FUNC_YYLTYPE *yylloc,
                                  cowl_unused yyscan_t scanner,
                                  CowlEditor *editor, const char *s) {
        if (strcmp(s, "memory exhausted") == 0) {
            COWL_HANDLE_MEM_ERROR();
        } else {
            cowl_handle_syntax_error(ustring_wrap(s, strlen(s)), editor->ontology,
                                     (CowlErrorLoc) { .line = yylloc->last_line });
        }
    }



    #define COWL_ERROR(CODE) do {                                                                   \
        COWL_HANDLE_ERROR(CODE);                                                                    \
        YYERROR;                                                                                    \
    } while (0)

    #define COWL_ERROR_MEM COWL_ERROR(COWL_ERR_MEM)

    #define COWL_ERROR_SYNTAX(DESC) do {                                                            \
        COWL_HANDLE_SYNTAX_ERROR(DESC);                                                             \
        YYERROR;                                                                                    \
    } while (0)

    #define COWL_VEC_PUSH(T, VEC, OBJ) do {                                                         \
        if (cowl_vector_push(VEC, OBJ)) COWL_ERROR_MEM;                                             \
    } while (0)

    #define COWL_VEC_FINALIZE(VEC) do {                                                             \
        if (VEC) {                                                                                  \
            cowl_vector_release(VEC);                                                               \
            if (cowl_vector_shrink(VEC)) COWL_ERROR_MEM;                                            \
        }                                                                                           \
    } while (0)
}

%define api.value.type union

// Terminals

%token <ulib_uint> NON_NEGATIVE_INTEGER
%token <UString> QUOTED_STRING
%token <UString> BLANK_NODE_LABEL
%token <UString> PNAME_NS
%token <UString> PNAME_LN
%token <UString> LANG_TAG
%token <UString> IRI_REF

%token L_PAREN R_PAREN EQUALS DOUBLE_CARET

%token IMPORT ONTOLOGY PREFIX DECLARATION ANNOTATION DATATYPE_DEFINITION HAS_KEY
%token CLASS DATATYPE OBJECT_PROPERTY DATA_PROPERTY ANNOTATION_PROPERTY NAMED_INDIVIDUAL

%token DATA_INTERSECTION_OF DATA_UNION_OF DATA_COMPLEMENT_OF DATA_ONE_OF DATATYPE_RESTRICTION
%token DATA_SOME_VALUES_FROM DATA_ALL_VALUES_FROM DATA_HAS_VALUE
%token DATA_MIN_CARDINALITY DATA_MAX_CARDINALITY DATA_EXACT_CARDINALITY

%token OBJECT_INVERSE_OF
%token OBJECT_INTERSECTION_OF OBJECT_UNION_OF OBJECT_COMPLEMENT_OF OBJECT_ONE_OF
%token OBJECT_SOME_VALUES_FROM OBJECT_ALL_VALUES_FROM OBJECT_HAS_VALUE OBJECT_HAS_SELF
%token OBJECT_MIN_CARDINALITY OBJECT_MAX_CARDINALITY OBJECT_EXACT_CARDINALITY

%token SUB_CLASS_OF EQUIVALENT_CLASSES DISJOINT_CLASSES DISJOINT_UNION
%token SUB_OBJECT_PROPERTY_OF EQUIVALENT_OBJECT_PROPERTIES DISJOINT_OBJECT_PROPERTIES
%token OBJECT_PROPERTY_CHAIN INVERSE_OBJECT_PROPERTIES OBJECT_PROPERTY_DOMAIN OBJECT_PROPERTY_RANGE
%token FUNCTIONAL_OBJECT_PROPERTY INVERSE_FUNCTIONAL_OBJECT_PROPERTY
%token REFLEXIVE_OBJECT_PROPERTY IRREFLEXIVE_OBJECT_PROPERTY
%token SYMMETRIC_OBJECT_PROPERTY ASYMMETRIC_OBJECT_PROPERTY TRANSITIVE_OBJECT_PROPERTY

%token SUB_DATA_PROPERTY_OF EQUIVALENT_DATA_PROPERTIES DISJOINT_DATA_PROPERTIES
%token DATA_PROPERTY_DOMAIN DATA_PROPERTY_RANGE FUNCTIONAL_DATA_PROPERTY

%token SAME_INDIVIDUAL DIFFERENT_INDIVIDUALS CLASS_ASSERTION
%token OBJECT_PROPERTY_ASSERTION NEGATIVE_OBJECT_PROPERTY_ASSERTION
%token DATA_PROPERTY_ASSERTION NEGATIVE_DATA_PROPERTY_ASSERTION

%token ANNOTATION_ASSERTION SUB_ANNOTATION_PROPERTY_OF
%token ANNOTATION_PROPERTY_DOMAIN ANNOTATION_PROPERTY_RANGE

// Nonterminals

%type <CowlString *> prefix_name
%type <CowlIRI *> iri full_iri abbreviated_iri
%type <CowlAnnotation *> annotation
%type <CowlAnnotValue *> annotation_subject annotation_value
%type <ulib_uint> cardinality

%type <CowlEntity *> entity
%type <CowlClass *> class
%type <CowlObjProp *> object_property
%type <CowlDataProp *> data_property
%type <CowlNamedInd *> named_individual
%type <CowlDatatype *> datatype
%type <CowlAnnotProp *> annotation_property

%type <CowlClsExp *> class_expression
%type <CowlClsExp *> object_intersection_of object_union_of object_complement_of object_one_of
%type <CowlClsExp *> object_some_values_from object_all_values_from object_has_value object_has_self
%type <CowlClsExp *> object_min_cardinality object_max_cardinality object_exact_cardinality
%type <CowlClsExp *> data_some_values_from data_all_values_from data_has_value
%type <CowlClsExp *> data_min_cardinality data_max_cardinality data_exact_cardinality

%type <CowlIndividual *> individual anonymous_individual
%type <CowlObjPropExp *> object_property_expression inverse_object_property
%type <CowlDataPropExp *> data_property_expression

%type <CowlDataRange *> data_range data_intersection_of data_union_of data_complement_of
%type <CowlDataRange *> data_one_of datatype_restriction

%type <CowlFacetRestr *> facet_restriction
%type <CowlLiteral *> literal

%type <CowlAxiom *> axiom declaration
%type <CowlAxiom *> class_axiom object_property_axiom data_property_axiom annotation_axiom
%type <CowlAxiom *> sub_class_of equivalent_classes disjoint_classes disjoint_union
%type <CowlAxiom *> assertion same_individual different_individuals
%type <CowlAxiom *> class_assertion annotation_assertion
%type <CowlAxiom *> object_property_assertion negative_object_property_assertion
%type <CowlAxiom *> data_property_assertion negative_data_property_assertion
%type <CowlAxiom *> sub_object_property_of equivalent_object_properties
%type <CowlAxiom *> object_property_domain object_property_range
%type <CowlAxiom *> disjoint_object_properties inverse_object_properties
%type <CowlAxiom *> functional_object_property inverse_functional_object_property
%type <CowlAxiom *> reflexive_object_property irreflexive_object_property
%type <CowlAxiom *> symmetric_object_property asymmetric_object_property transitive_object_property
%type <CowlAxiom *> sub_data_property_of equivalent_data_properties disjoint_data_properties
%type <CowlAxiom *> data_property_domain data_property_range functional_data_property
%type <CowlAxiom *> datatype_definition has_key
%type <CowlAxiom *> sub_annotation_property_of annotation_property_domain annotation_property_range

%type <CowlVector *> class_expression_list class_expression_2_list
%type <CowlVector *> data_property_expression_list data_property_expression_2_list
%type <CowlVector *> data_property_expression_star
%type <CowlVector *> data_range_list data_range_2_list
%type <CowlVector *> facet_restriction_list
%type <CowlVector *> individual_list individual_2_list
%type <CowlVector *> literal_list
%type <CowlVector *> object_property_expression_list object_property_expression_2_list
%type <CowlVector *> object_property_expression_star
%type <CowlVector *> object_property_expression_ordered_2_list property_expression_chain
%type <CowlVector *> annotation_star

// Start symbol

%start ontology_document

// Destructors

%destructor { cowl_annotation_release($$); } <CowlAnnotation *>
%destructor { cowl_annot_prop_release($$); } <CowlAnnotProp *>
%destructor { cowl_annot_value_release($$); } <CowlAnnotValue *>
%destructor { cowl_axiom_release($$); } <CowlAxiom *>
%destructor { cowl_class_release($$); } <CowlClass *>
%destructor { cowl_cls_exp_release($$); } <CowlClsExp *>
%destructor { cowl_data_prop_release($$); } <CowlDataProp *>
%destructor { cowl_data_prop_exp_release($$); } <CowlDataPropExp *>
%destructor { cowl_data_range_release($$); } <CowlDataRange *>
%destructor { cowl_datatype_release($$); } <CowlDatatype *>
%destructor { cowl_entity_release($$); } <CowlEntity *>
%destructor { cowl_facet_restr_release($$); } <CowlFacetRestr *>
%destructor { cowl_individual_release($$); } <CowlIndividual *>
%destructor { cowl_iri_release($$); } <CowlIRI *>
%destructor { cowl_literal_release($$); } <CowlLiteral *>
%destructor { cowl_named_ind_release($$); } <CowlNamedInd *>
%destructor { cowl_obj_prop_release($$); } <CowlObjProp *>
%destructor { cowl_obj_prop_exp_release($$); } <CowlObjPropExp *>
%destructor { cowl_string_release($$); } <CowlString *>
%destructor { cowl_vector_release($$); } <CowlVector *>

%%

// Grammar reference: https://www.w3.org/TR/owl2-syntax

// IRIs

full_iri
    : IRI_REF {
        $$ = cowl_iri_from_string($1);
    }
;

prefix_name
    : PNAME_NS {
        $$ = cowl_string(ustring_dup($1));
    }
;

abbreviated_iri
    : PNAME_LN {
        $$ = cowl_sym_table_parse_full_iri(&editor->st, $1);
        if (!$$) {
            UString comp[] = { ustring_literal("failed to resolve "), $1 };
            UString err_str = ustring_concat(comp, ulib_array_count(comp));
            COWL_HANDLE_SYNTAX_ERROR(err_str);
            ustring_deinit(&err_str);
            YYERROR;
        }
    }
;

iri
    : full_iri
    | abbreviated_iri
;

// Ontologies

ontology_document
    : prefix_declarations ontology
;

prefix_declarations
    : %empty
    | prefix_declarations prefix_declaration
;

prefix_declaration
    : PREFIX L_PAREN prefix_name EQUALS full_iri R_PAREN {
        CowlString *iri_string = cowl_iri_to_string($5);
        cowl_ret ret = cowl_sym_table_register_prefix(&editor->st, $3, iri_string);
        cowl_string_release(iri_string);
        cowl_string_release($3);
        cowl_iri_release($5);
        if (ret) YYERROR;
    }
;

ontology
    : ONTOLOGY L_PAREN ontology_id ontology_imports ontology_annotations axioms R_PAREN
;

ontology_id
    : %empty
    | iri {
        cowl_editor_set_iri(editor, $1);
        cowl_iri_release($1);
    }
    | iri iri {
        cowl_editor_set_iri(editor, $1);
        cowl_editor_set_version(editor, $2);
        cowl_iri_release($1);
        cowl_iri_release($2);
    }
;

ontology_imports
    : %empty
    | ontology_imports import
;

import
    : IMPORT L_PAREN iri R_PAREN {
        cowl_ret ret = cowl_editor_add_import(editor, $3);
        cowl_iri_release($3);
        if (ret) YYERROR;
    }
;

ontology_annotations
    : %empty
    | ontology_annotations annotation {
        cowl_ret ret = cowl_editor_add_annot(editor, $2);
        cowl_annotation_release($2);
        if (ret) YYERROR;
    }

axioms
    : %empty
    | axioms axiom {
        cowl_ret ret = cowl_editor_add_axiom(editor, $2);
        cowl_axiom_release($2);
        if (ret) YYERROR;
    }
;

// Classes

class
    : iri {
        $$ = cowl_class($1);
        cowl_iri_release($1);
    }
;

// Datatypes

datatype
    : iri {
        $$ = cowl_datatype($1);
        cowl_iri_release($1);
    }
;

// Object properties

object_property
    : iri {
        $$ = cowl_obj_prop($1);
        cowl_iri_release($1);
    }
;

// Data properties

data_property
    : iri {
        $$ = cowl_data_prop($1);
        cowl_iri_release($1);
    }
;

// Annotation properties

annotation_property
    : iri {
        $$ = cowl_annot_prop($1);
        cowl_iri_release($1);
    }
;

// Individuals

individual
    : named_individual { $$ = (CowlIndividual *)$1; }
    | anonymous_individual
;

named_individual
    : iri {
        $$ = cowl_named_ind($1);
        cowl_iri_release($1);
    }
;

anonymous_individual
    : BLANK_NODE_LABEL {
        CowlAnonInd *ind = cowl_sym_table_get_anon(&editor->st, $1);
        $$ = (CowlIndividual *)(ind ? cowl_anon_ind_retain(ind) : NULL);
    }
;

// Literals

literal
    : QUOTED_STRING DOUBLE_CARET datatype {
        if (!$3) COWL_ERROR_MEM;
        $$ = cowl_literal_raw($3, $1, ustring_empty);
        cowl_datatype_release($3);
    }
    | QUOTED_STRING LANG_TAG {
        $$ = cowl_literal_raw(NULL, $1, $2);
    }
    | QUOTED_STRING {
        $$ = cowl_literal_raw(NULL, $1, ustring_empty);
    }
;

// Entity declarations and typing

declaration
    : DECLARATION L_PAREN annotation_star entity R_PAREN {
        $$ = (CowlAxiom *)cowl_decl_axiom($4, $3);
        COWL_VEC_FINALIZE($3);
        cowl_entity_release($4);
    }
;

entity
    : CLASS L_PAREN class R_PAREN {
        $$ = (CowlEntity *)($3);
    }
    | DATATYPE L_PAREN datatype R_PAREN {
        $$ = (CowlEntity *)($3);
    }
    | OBJECT_PROPERTY L_PAREN object_property R_PAREN {
        $$ = (CowlEntity *)($3);
    }
    | DATA_PROPERTY L_PAREN data_property R_PAREN {
        $$ = (CowlEntity *)($3);
    }
    | ANNOTATION_PROPERTY L_PAREN annotation_property R_PAREN {
        $$ = (CowlEntity *)($3);
    }
    | NAMED_INDIVIDUAL L_PAREN named_individual R_PAREN {
        $$ = (CowlEntity *)($3);
    }
;

// Object property expressions

object_property_expression
    : object_property { $$ = (CowlObjPropExp *)$1; }
    | inverse_object_property
;

inverse_object_property
    : OBJECT_INVERSE_OF L_PAREN object_property R_PAREN {
        $$ = (CowlObjPropExp *)cowl_inv_obj_prop($3);
        cowl_obj_prop_release($3);
    }
;

// Data property expressions

data_property_expression
    : data_property { $$ = (CowlDataPropExp *)$1; }
;

// Data ranges

data_range
    : datatype { $$ = (CowlDataRange *)$1; }
    | data_intersection_of
    | data_union_of
    | data_complement_of
    | data_one_of
    | datatype_restriction
;

data_intersection_of
    : DATA_INTERSECTION_OF L_PAREN data_range_2_list R_PAREN {
        $$ = (CowlDataRange *)cowl_nary_data(COWL_NT_INTERSECT, $3);
        COWL_VEC_FINALIZE($3);
    }
;

data_union_of
    : DATA_UNION_OF L_PAREN data_range_2_list R_PAREN {
        $$ = (CowlDataRange *)cowl_nary_data(COWL_NT_UNION, $3);
        COWL_VEC_FINALIZE($3);
    }
;

data_complement_of
    : DATA_COMPLEMENT_OF L_PAREN data_range R_PAREN {
        $$ = (CowlDataRange *)cowl_data_compl($3);
        cowl_data_range_release($3);
    }
;

data_one_of
    : DATA_ONE_OF L_PAREN literal_list R_PAREN {
        $$ = (CowlDataRange *)cowl_data_one_of($3);
        COWL_VEC_FINALIZE($3);
    }
;

datatype_restriction
    : DATATYPE_RESTRICTION L_PAREN datatype facet_restriction_list R_PAREN {
        $$ = (CowlDataRange *)cowl_datatype_restr($3, $4);
        cowl_datatype_release($3);
        COWL_VEC_FINALIZE($4);
    }
;

facet_restriction
    : iri literal {
        $$ = cowl_facet_restr($1, $2);
        cowl_iri_release($1);
        cowl_literal_release($2);
    }
;

// Class expressions

class_expression
    : class { $$ = (CowlClsExp *)$1; }
    | object_intersection_of
    | object_union_of
    | object_complement_of
    | object_one_of
    | object_some_values_from
    | object_all_values_from
    | object_has_value
    | object_has_self
    | object_min_cardinality
    | object_max_cardinality
    | object_exact_cardinality
    | data_some_values_from
    | data_all_values_from
    | data_has_value
    | data_min_cardinality
    | data_max_cardinality
    | data_exact_cardinality
;

object_intersection_of
    : OBJECT_INTERSECTION_OF L_PAREN class_expression_2_list R_PAREN {
        $$ = (CowlClsExp *)cowl_nary_bool(COWL_NT_INTERSECT, $3);
        COWL_VEC_FINALIZE($3);
    }
;

object_union_of
    : OBJECT_UNION_OF L_PAREN class_expression_2_list R_PAREN {
        $$ = (CowlClsExp *)cowl_nary_bool(COWL_NT_UNION, $3);
        COWL_VEC_FINALIZE($3);
    }
;

object_complement_of
    : OBJECT_COMPLEMENT_OF L_PAREN class_expression R_PAREN {
        $$ = (CowlClsExp *)cowl_obj_compl($3);
        cowl_cls_exp_release($3);
    }
;

object_one_of
    : OBJECT_ONE_OF L_PAREN individual_list R_PAREN {
        $$ = (CowlClsExp *)cowl_obj_one_of($3);
        COWL_VEC_FINALIZE($3);
    }
;

object_some_values_from
    : OBJECT_SOME_VALUES_FROM L_PAREN object_property_expression class_expression R_PAREN {
        $$ = (CowlClsExp *)cowl_obj_quant(COWL_QT_SOME, $3, $4);
        cowl_obj_prop_exp_release($3);
        cowl_cls_exp_release($4);
    }
;

object_all_values_from
    : OBJECT_ALL_VALUES_FROM L_PAREN object_property_expression class_expression R_PAREN {
        $$ = (CowlClsExp *)cowl_obj_quant(COWL_QT_ALL, $3, $4);
        cowl_obj_prop_exp_release($3);
        cowl_cls_exp_release($4);
    }
;

object_has_value
    : OBJECT_HAS_VALUE L_PAREN object_property_expression individual R_PAREN {
        $$ = (CowlClsExp *)cowl_obj_has_value($3, $4);
        cowl_obj_prop_exp_release($3);
        cowl_individual_release($4);
    }
;

object_has_self
    : OBJECT_HAS_SELF L_PAREN object_property_expression R_PAREN {
        $$ = (CowlClsExp *)cowl_obj_has_self($3);
        cowl_obj_prop_exp_release($3);
    }
;

object_min_cardinality
    : OBJECT_MIN_CARDINALITY L_PAREN cardinality object_property_expression R_PAREN {
        $$ = (CowlClsExp *)cowl_obj_card(COWL_CT_MIN, $4, NULL, $3);
        cowl_obj_prop_exp_release($4);
    }
    | OBJECT_MIN_CARDINALITY L_PAREN cardinality object_property_expression class_expression R_PAREN {
        if (!$5) COWL_ERROR_MEM;
        $$ = (CowlClsExp *)cowl_obj_card(COWL_CT_MIN, $4, $5, $3);
        cowl_obj_prop_exp_release($4);
        cowl_cls_exp_release($5);
    }
;

object_max_cardinality
    : OBJECT_MAX_CARDINALITY L_PAREN cardinality object_property_expression R_PAREN {
        $$ = (CowlClsExp *)cowl_obj_card(COWL_CT_MAX, $4, NULL, $3);
        cowl_obj_prop_exp_release($4);
    }
    | OBJECT_MAX_CARDINALITY L_PAREN cardinality object_property_expression class_expression R_PAREN {
        if (!$5) COWL_ERROR_MEM;
        $$ = (CowlClsExp *)cowl_obj_card(COWL_CT_MAX, $4, $5, $3);
        cowl_obj_prop_exp_release($4);
        cowl_cls_exp_release($5);
    }
;

object_exact_cardinality
    : OBJECT_EXACT_CARDINALITY L_PAREN cardinality object_property_expression R_PAREN {
        $$ = (CowlClsExp *)cowl_obj_card(COWL_CT_EXACT, $4, NULL, $3);
        cowl_obj_prop_exp_release($4);
    }
    | OBJECT_EXACT_CARDINALITY L_PAREN cardinality object_property_expression class_expression R_PAREN {
        if (!$5) COWL_ERROR_MEM;
        $$ = (CowlClsExp *)cowl_obj_card(COWL_CT_EXACT, $4, $5, $3);
        cowl_obj_prop_exp_release($4);
        cowl_cls_exp_release($5);
    }
;

cardinality
    : NON_NEGATIVE_INTEGER
;

data_some_values_from
    : DATA_SOME_VALUES_FROM L_PAREN data_property_expression data_range R_PAREN {
        $$ = (CowlClsExp *)cowl_data_quant(COWL_QT_SOME, $3, $4);
        cowl_data_prop_exp_release($3);
        cowl_data_range_release($4);
    }
;

data_all_values_from
    : DATA_ALL_VALUES_FROM L_PAREN data_property_expression data_range R_PAREN {
        $$ = (CowlClsExp *)cowl_data_quant(COWL_QT_ALL, $3, $4);
        cowl_data_prop_exp_release($3);
        cowl_data_range_release($4);
    }
;

data_has_value
    : DATA_HAS_VALUE L_PAREN data_property_expression literal R_PAREN {
        $$ = (CowlClsExp *)cowl_data_has_value($3, $4);
        cowl_data_prop_exp_release($3);
        cowl_literal_release($4);
    }
;

data_min_cardinality
    : DATA_MIN_CARDINALITY L_PAREN cardinality data_property_expression R_PAREN {
        $$ = (CowlClsExp *)cowl_data_card(COWL_CT_MIN, $4, NULL, $3);
        cowl_data_prop_exp_release($4);
    }
    | DATA_MIN_CARDINALITY L_PAREN cardinality data_property_expression data_range R_PAREN {
        if (!$5) COWL_ERROR_MEM;
        $$ = (CowlClsExp *)cowl_data_card(COWL_CT_MIN, $4, $5, $3);
        cowl_data_prop_exp_release($4);
        cowl_data_range_release($5);
    }
;

data_max_cardinality
    : DATA_MAX_CARDINALITY L_PAREN cardinality data_property_expression R_PAREN {
        $$ = (CowlClsExp *)cowl_data_card(COWL_CT_MAX, $4, NULL, $3);
        cowl_data_prop_exp_release($4);
    }
    | DATA_MAX_CARDINALITY L_PAREN cardinality data_property_expression data_range R_PAREN {
        if (!$5) COWL_ERROR_MEM;
        $$ = (CowlClsExp *)cowl_data_card(COWL_CT_MAX, $4, $5, $3);
        cowl_data_prop_exp_release($4);
        cowl_data_range_release($5);
    }
;

data_exact_cardinality
    : DATA_EXACT_CARDINALITY L_PAREN cardinality data_property_expression R_PAREN {
        $$ = (CowlClsExp *)cowl_data_card(COWL_CT_EXACT, $4, NULL, $3);
        cowl_data_prop_exp_release($4);
    }
    | DATA_EXACT_CARDINALITY L_PAREN cardinality data_property_expression data_range R_PAREN {
        if (!$5) COWL_ERROR_MEM;
        $$ = (CowlClsExp *)cowl_data_card(COWL_CT_EXACT, $4, $5, $3);
        cowl_data_prop_exp_release($4);
        cowl_data_range_release($5);
    }
;

// Axioms

axiom
    : declaration
    | class_axiom
    | object_property_axiom
    | data_property_axiom
    | datatype_definition
    | has_key
    | assertion
    | annotation_axiom
;

// Class expression axioms

class_axiom
    : sub_class_of
    | equivalent_classes
    | disjoint_classes
    | disjoint_union
;

sub_class_of
    : SUB_CLASS_OF L_PAREN annotation_star class_expression class_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_sub_cls_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_cls_exp_release($4);
        cowl_cls_exp_release($5);
    }
;

equivalent_classes
    : EQUIVALENT_CLASSES L_PAREN annotation_star class_expression_2_list R_PAREN {
        $$ = (CowlAxiom *)cowl_nary_cls_axiom(COWL_NAT_EQUIV, $4, $3);
        COWL_VEC_FINALIZE($3);
        COWL_VEC_FINALIZE($4);
    }
;

disjoint_classes
    : DISJOINT_CLASSES L_PAREN annotation_star class_expression_2_list R_PAREN {
        $$ = (CowlAxiom *)cowl_nary_cls_axiom(COWL_NAT_DISJ, $4, $3);
        COWL_VEC_FINALIZE($3);
        COWL_VEC_FINALIZE($4);
    }
;

disjoint_union
    : DISJOINT_UNION L_PAREN annotation_star class class_expression_2_list R_PAREN {
        $$ = (CowlAxiom *)cowl_disj_union_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_class_release($4);
        COWL_VEC_FINALIZE($5);
    }
;

// Object property axioms

object_property_axiom
    : sub_object_property_of
    | equivalent_object_properties
    | disjoint_object_properties
    | inverse_object_properties
    | object_property_domain
    | object_property_range
    | functional_object_property
    | inverse_functional_object_property
    | reflexive_object_property
    | irreflexive_object_property
    | symmetric_object_property
    | asymmetric_object_property
    | transitive_object_property
;

sub_object_property_of
    : SUB_OBJECT_PROPERTY_OF L_PAREN annotation_star object_property_expression object_property_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_sub_obj_prop_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
        cowl_obj_prop_exp_release($5);
    }
    | SUB_OBJECT_PROPERTY_OF L_PAREN annotation_star property_expression_chain object_property_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_sub_obj_prop_chain_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        COWL_VEC_FINALIZE($4);
        cowl_obj_prop_exp_release($5);
    }
;

property_expression_chain
    : OBJECT_PROPERTY_CHAIN L_PAREN object_property_expression_ordered_2_list R_PAREN {
        $$ = $3;
    }
;

equivalent_object_properties
    : EQUIVALENT_OBJECT_PROPERTIES L_PAREN annotation_star object_property_expression_2_list R_PAREN {
        $$ = (CowlAxiom *)cowl_nary_obj_prop_axiom(COWL_NAT_EQUIV, $4, $3);
        COWL_VEC_FINALIZE($3);
        COWL_VEC_FINALIZE($4);
    }
;

disjoint_object_properties
    : DISJOINT_OBJECT_PROPERTIES L_PAREN annotation_star object_property_expression_2_list R_PAREN {
        $$ = (CowlAxiom *)cowl_nary_obj_prop_axiom(COWL_NAT_DISJ, $4, $3);
        COWL_VEC_FINALIZE($3);
        COWL_VEC_FINALIZE($4);
    }
;

inverse_object_properties
    : INVERSE_OBJECT_PROPERTIES L_PAREN annotation_star object_property_expression object_property_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_inv_obj_prop_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
        cowl_obj_prop_exp_release($5);
    }
;

object_property_domain
    : OBJECT_PROPERTY_DOMAIN L_PAREN annotation_star object_property_expression class_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_obj_prop_domain_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
        cowl_cls_exp_release($5);
    }
;

object_property_range
    : OBJECT_PROPERTY_RANGE L_PAREN annotation_star object_property_expression class_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_obj_prop_range_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
        cowl_cls_exp_release($5);
    }
;

functional_object_property
    : FUNCTIONAL_OBJECT_PROPERTY L_PAREN annotation_star object_property_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_obj_prop_char_axiom(COWL_CAT_FUNC, $4, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
    }
;

inverse_functional_object_property
    : INVERSE_FUNCTIONAL_OBJECT_PROPERTY L_PAREN annotation_star object_property_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_obj_prop_char_axiom(COWL_CAT_INV_FUNC, $4, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
    }
;

reflexive_object_property
    : REFLEXIVE_OBJECT_PROPERTY L_PAREN annotation_star object_property_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_obj_prop_char_axiom(COWL_CAT_REFL, $4, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
    }
;

irreflexive_object_property
    : IRREFLEXIVE_OBJECT_PROPERTY L_PAREN annotation_star object_property_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_obj_prop_char_axiom(COWL_CAT_IRREFL, $4, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
    }
;

symmetric_object_property
    : SYMMETRIC_OBJECT_PROPERTY L_PAREN annotation_star object_property_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_obj_prop_char_axiom(COWL_CAT_SYMM, $4, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
    }
;

asymmetric_object_property
    : ASYMMETRIC_OBJECT_PROPERTY L_PAREN annotation_star object_property_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_obj_prop_char_axiom(COWL_CAT_ASYMM, $4, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
    }
;

transitive_object_property
    : TRANSITIVE_OBJECT_PROPERTY L_PAREN annotation_star object_property_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_obj_prop_char_axiom(COWL_CAT_TRANS, $4, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
    }
;

// Data property axioms

data_property_axiom
    : sub_data_property_of
    | equivalent_data_properties
    | disjoint_data_properties
    | data_property_domain
    | data_property_range
    | functional_data_property
;

sub_data_property_of
    : SUB_DATA_PROPERTY_OF L_PAREN annotation_star data_property_expression data_property_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_sub_data_prop_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_data_prop_exp_release($4);
        cowl_data_prop_exp_release($5);
    }
;

equivalent_data_properties
    : EQUIVALENT_DATA_PROPERTIES L_PAREN annotation_star data_property_expression_2_list R_PAREN {
        $$ = (CowlAxiom *)cowl_nary_data_prop_axiom(COWL_NAT_EQUIV, $4, $3);
        COWL_VEC_FINALIZE($3);
        COWL_VEC_FINALIZE($4);
    }
;

disjoint_data_properties
    : DISJOINT_DATA_PROPERTIES L_PAREN annotation_star data_property_expression_2_list R_PAREN {
        $$ = (CowlAxiom *)cowl_nary_data_prop_axiom(COWL_NAT_DISJ, $4, $3);
        COWL_VEC_FINALIZE($3);
        COWL_VEC_FINALIZE($4);
    }
;

data_property_domain
    : DATA_PROPERTY_DOMAIN L_PAREN annotation_star data_property_expression class_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_data_prop_domain_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_data_prop_exp_release($4);
        cowl_cls_exp_release($5);
    }
;

data_property_range
    : DATA_PROPERTY_RANGE L_PAREN annotation_star data_property_expression data_range R_PAREN {
        $$ = (CowlAxiom *)cowl_data_prop_range_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_data_prop_exp_release($4);
        cowl_data_range_release($5);
    }
;

functional_data_property
    : FUNCTIONAL_DATA_PROPERTY L_PAREN annotation_star data_property_expression R_PAREN {
        $$ = (CowlAxiom *)cowl_func_data_prop_axiom($4, $3);
        COWL_VEC_FINALIZE($3);
        cowl_data_prop_exp_release($4);
    }
;

// Datatype definitions

datatype_definition
    : DATATYPE_DEFINITION L_PAREN annotation_star datatype data_range R_PAREN {
        $$ = (CowlAxiom *)cowl_datatype_def_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_datatype_release($4);
        cowl_data_range_release($5);
    }
;

// Keys

has_key
    :   HAS_KEY L_PAREN annotation_star class_expression
            L_PAREN object_property_expression_star R_PAREN
            L_PAREN data_property_expression_star R_PAREN
        R_PAREN {
        $$ = (CowlAxiom *)cowl_has_key_axiom($4, $6, $9, $3);
        COWL_VEC_FINALIZE($3);
        cowl_cls_exp_release($4);
        COWL_VEC_FINALIZE($6);
        COWL_VEC_FINALIZE($9);
    }
;

// Assertions

assertion
    : same_individual
    | different_individuals
    | class_assertion
    | object_property_assertion
    | negative_object_property_assertion
    | data_property_assertion
    | negative_data_property_assertion
;

same_individual
    : SAME_INDIVIDUAL L_PAREN annotation_star individual_2_list R_PAREN {
        $$ = (CowlAxiom *)cowl_nary_ind_axiom(COWL_NAT_SAME, $4, $3);
        COWL_VEC_FINALIZE($3);
        COWL_VEC_FINALIZE($4);
    }
;

different_individuals
    : DIFFERENT_INDIVIDUALS L_PAREN annotation_star individual_2_list R_PAREN {
        $$ = (CowlAxiom *)cowl_nary_ind_axiom(COWL_NAT_DIFF, $4, $3);
        COWL_VEC_FINALIZE($3);
        COWL_VEC_FINALIZE($4);
    }
;

class_assertion
    : CLASS_ASSERTION L_PAREN annotation_star class_expression individual R_PAREN {
        $$ = (CowlAxiom *)cowl_cls_assert_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_cls_exp_release($4);
        cowl_individual_release($5);
    }
;

object_property_assertion
    : OBJECT_PROPERTY_ASSERTION L_PAREN annotation_star object_property_expression individual individual R_PAREN {
        $$ = (CowlAxiom *)cowl_obj_prop_assert_axiom($4, $5, $6, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
        cowl_individual_release($5);
        cowl_individual_release($6);
    }
;

negative_object_property_assertion
    : NEGATIVE_OBJECT_PROPERTY_ASSERTION L_PAREN annotation_star object_property_expression individual individual R_PAREN {
        $$ = (CowlAxiom *)cowl_neg_obj_prop_assert_axiom($4, $5, $6, $3);
        COWL_VEC_FINALIZE($3);
        cowl_obj_prop_exp_release($4);
        cowl_individual_release($5);
        cowl_individual_release($6);
    }
;

data_property_assertion
    : DATA_PROPERTY_ASSERTION L_PAREN annotation_star data_property_expression individual literal R_PAREN {
        $$ = (CowlAxiom *)cowl_data_prop_assert_axiom($4, $5, $6, $3);
        COWL_VEC_FINALIZE($3);
        cowl_data_prop_exp_release($4);
        cowl_individual_release($5);
        cowl_literal_release($6);
    }
;

negative_data_property_assertion
    : NEGATIVE_DATA_PROPERTY_ASSERTION L_PAREN annotation_star data_property_expression individual literal R_PAREN {
        $$ = (CowlAxiom *)cowl_neg_data_prop_assert_axiom($4, $5, $6, $3);
        COWL_VEC_FINALIZE($3);
        cowl_data_prop_exp_release($4);
        cowl_individual_release($5);
        cowl_literal_release($6);
    }
;

// Annotations

annotation
    : ANNOTATION L_PAREN annotation_star annotation_property annotation_value R_PAREN {
        $$ = cowl_annotation($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_annot_prop_release($4);
        cowl_annot_value_release($5);
    }
;

annotation_value
    : anonymous_individual {
        $$ = (CowlAnnotValue *)($1);
    }
    | iri {
        $$ = (CowlAnnotValue *)($1);
    }
    | literal {
        $$ = (CowlAnnotValue *)($1);
    }
;

// Annotation axioms

annotation_axiom
    : annotation_assertion
    | sub_annotation_property_of
    | annotation_property_domain
    | annotation_property_range
;

annotation_assertion
    : ANNOTATION_ASSERTION L_PAREN annotation_star annotation_property annotation_subject annotation_value R_PAREN {
        $$ = (CowlAxiom *)cowl_annot_assert_axiom($4, $5, $6, $3);
        COWL_VEC_FINALIZE($3);
        cowl_annot_prop_release($4);
        cowl_annot_value_release($5);
        cowl_annot_value_release($6);
    }
;

annotation_subject
    : iri {
        $$ = (CowlAnnotValue *)($1);
    }
    | anonymous_individual {
        $$ = (CowlAnnotValue *)($1);
    }
;

sub_annotation_property_of
    : SUB_ANNOTATION_PROPERTY_OF L_PAREN annotation_star annotation_property annotation_property R_PAREN {
        $$ = (CowlAxiom *)cowl_sub_annot_prop_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_annot_prop_release($4);
        cowl_annot_prop_release($5);
    }
;

annotation_property_domain
    : ANNOTATION_PROPERTY_DOMAIN L_PAREN annotation_star annotation_property iri R_PAREN {
        $$ = (CowlAxiom *)cowl_annot_prop_domain_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_annot_prop_release($4);
        cowl_iri_release($5);
    }
;

annotation_property_range
    : ANNOTATION_PROPERTY_RANGE L_PAREN annotation_star annotation_property iri R_PAREN {
        $$ = (CowlAxiom *)cowl_annot_prop_range_axiom($4, $5, $3);
        COWL_VEC_FINALIZE($3);
        cowl_annot_prop_release($4);
        cowl_iri_release($5);
    }
;

// Lists

annotation_star
    : %empty {
        $$ = NULL;
    }
    | annotation_star annotation {
        if ($1) {
            $$ = $1;
        } else {
            $$ = cowl_vector_empty();
            if (!$$) COWL_ERROR_MEM;
        }
        COWL_VEC_PUSH(annotation, $$, $2);
    }
;

class_expression_list
    : class_expression {
        $$ = cowl_vector_empty();
        if (!$$) COWL_ERROR_MEM;
        COWL_VEC_PUSH(cls_exp, $$, $1);
    }
    | class_expression_list class_expression {
        $$ = $1;
        COWL_VEC_PUSH(cls_exp, $$, $2);
    }
;

class_expression_2_list
    : class_expression_list class_expression {
        $$ = $1;
        COWL_VEC_PUSH(cls_exp, $$, $2);
    }
;

data_property_expression_list
    : data_property_expression {
        $$ = cowl_vector_empty();
        if (!$$) COWL_ERROR_MEM;
        COWL_VEC_PUSH(data_prop_exp, $$, $1);
    }
    | data_property_expression_list data_property_expression {
        $$ = $1;
        COWL_VEC_PUSH(data_prop_exp, $$, $2);
    }
;

data_property_expression_2_list
    : data_property_expression_list data_property_expression {
        $$ = $1;
        COWL_VEC_PUSH(data_prop_exp, $$, $2);
    }
;

data_property_expression_star
    : %empty {
        $$ = NULL;
    }
    | data_property_expression_star data_property_expression {
        if ($1) {
            $$ = $1;
        } else {
            $$ = cowl_vector_empty();
            if (!$$) COWL_ERROR_MEM;
        }
        COWL_VEC_PUSH(data_prop_exp, $$, $2);
    }
;

data_range_list
    : data_range {
        $$ = cowl_vector_empty();
        if (!$$) COWL_ERROR_MEM;
        COWL_VEC_PUSH(data_range, $$, $1);
    }
    | data_range_list data_range {
        $$ = $1;
        COWL_VEC_PUSH(data_range, $$, $2);
    }
;

data_range_2_list
    : data_range_list data_range {
        $$ = $1;
        COWL_VEC_PUSH(data_range, $$, $2);
    }
;

facet_restriction_list
    : facet_restriction {
        $$ = cowl_vector_empty();
        if (!$$) COWL_ERROR_MEM;
        COWL_VEC_PUSH(facet_restr, $$, $1);
    }
    | facet_restriction_list facet_restriction {
        $$ = $1;
        COWL_VEC_PUSH(facet_restr, $$, $2);
    }
;

individual_list
    : individual {
        $$ = cowl_vector_empty();
        if (!$$) COWL_ERROR_MEM;
        COWL_VEC_PUSH(individual, $$, $1);
    }
    | individual_list individual {
        $$ = $1;
        COWL_VEC_PUSH(individual, $$, $2);
    }
;

individual_2_list
    : individual_list individual {
        $$ = $1;
        COWL_VEC_PUSH(individual, $$, $2);
    }
;

literal_list
    : literal {
        $$ = cowl_vector_empty();
        if (!$$) COWL_ERROR_MEM;
        COWL_VEC_PUSH(literal, $$, $1);
    }
    | literal_list literal {
        $$ = $1;
        COWL_VEC_PUSH(literal, $$, $2);
    }
;

object_property_expression_list
    : object_property_expression {
        $$ = cowl_vector_empty();
        if (!$$) COWL_ERROR_MEM;
        COWL_VEC_PUSH(obj_prop_exp, $$, $1);
    }
    | object_property_expression_list object_property_expression {
        $$ = $1;
        COWL_VEC_PUSH(obj_prop_exp, $$, $2);
    }
;

object_property_expression_2_list
    : object_property_expression_list object_property_expression {
        $$ = $1;
        COWL_VEC_PUSH(obj_prop_exp, $$, $2);
    }
;

object_property_expression_ordered_2_list
    : object_property_expression object_property_expression {
        $$ = cowl_vector_ordered_empty();
        if (!$$) COWL_ERROR_MEM;
        COWL_VEC_PUSH(obj_prop_exp, $$, $1);
        COWL_VEC_PUSH(obj_prop_exp, $$, $2);
    }
    | object_property_expression_ordered_2_list object_property_expression {
        $$ = $1;
        COWL_VEC_PUSH(obj_prop_exp, $$, $2);
    }
;

object_property_expression_star
    : %empty {
        $$ = NULL;
    }
    | object_property_expression_star object_property_expression {
        if ($1) {
            $$ = $1;
        } else {
            $$ = cowl_vector_empty();
            if (!$$) COWL_ERROR_MEM;
        }
        COWL_VEC_PUSH(obj_prop_exp, $$, $2);
    }
;

%%
