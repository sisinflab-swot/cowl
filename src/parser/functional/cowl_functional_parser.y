// API configuration

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%locations

// Code

%code requires {
    #include "cowl_std.h"

    #ifndef YY_TYPEDEF_YY_SCANNER_T
    #define YY_TYPEDEF_YY_SCANNER_T
    typedef void *yyscan_t;
    #endif

    typedef struct CowlIRI const CowlIRI;
    typedef struct CowlString const CowlString;
}

%code top {
    #include "cowl_functional_parser.h"
    #include "cowl_functional_lexer.h"

    #include "cowl_iri_private.h"
    #include "cowl_string_private.h"

    static void yyerror(YYLTYPE *yylloc, cowl_unused yyscan_t yyscanner, const char* s) {
        fprintf(stderr, "Parse error on line %d: %s\n", yylloc->last_line, s);
    }
}

// Tokens

%define api.value.type union

%token <uint32_t> NON_NEGATIVE_INTEGER
%token <CowlString *> QUOTED_STRING
%token <CowlString *> BLANK_NODE_LABEL
%token <CowlString *> PNAME_NS
%token <CowlString *> PNAME_LN
%token <CowlString *> LANG_TAG
%token <CowlIRI *> IRI_REF

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

%start ontology_document

%%

// Grammar reference: https://www.w3.org/TR/owl2-syntax

// IRIs

full_iri
    : IRI_REF {
        CowlString *ns = cowl_iri_get_ns($1);
        CowlString *rem = cowl_iri_get_rem($1);
        printf("IRI: %s%s\n", cowl_string_get_cstring(ns), cowl_string_get_cstring(rem));
        cowl_iri_release($1);
    }
;

prefix_name
    : PNAME_NS {
        printf("Prefix: %s\n", cowl_string_get_cstring($1));
        cowl_string_release($1);
    }
;

abbreviated_iri
    : PNAME_LN {
        printf("Abbreviated IRI: %s\n", cowl_string_get_cstring($1));
        cowl_string_release($1);
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
    : PREFIX L_PAREN prefix_name EQUALS full_iri R_PAREN
;

ontology
    : ONTOLOGY L_PAREN ontology_id directly_imports_documents ontology_annotations axioms R_PAREN
;

ontology_id
    : %empty
    | ontology_iri
    | ontology_iri version_iri
;

ontology_iri
    : iri
;

version_iri
    : iri
;

directly_imports_documents
    : %empty
    | directly_imports_documents import
;

import
    : IMPORT L_PAREN iri R_PAREN
;

ontology_annotations
    : %empty
    | ontology_annotations annotation
;

axioms
    : %empty
    | axioms axiom
;

// Classes

class
    : iri
;

// Datatypes

datatype
    : iri
;

// Object properties

object_property
    : iri
;

// Data properties

data_property
    : iri
;

// Annotation properties

annotation_property
    : iri
;

// Individuals

individual
    : named_individual
    | anonymous_individual
;

named_individual
    : iri
;

anonymous_individual
    : node_id
;

node_id
    : BLANK_NODE_LABEL {
        printf("Blank node: %s\n", cowl_string_get_cstring($1));
        cowl_string_release($1);
    }
;

// Literals

literal
    : typed_literal
    | string_literal_no_language
    | string_literal_with_language
;

typed_literal
    : lexical_form DOUBLE_CARET datatype
;

lexical_form
    : QUOTED_STRING {
        printf("Lexical form: %s\n", cowl_string_get_cstring($1));
        cowl_string_release($1);
    }
;

string_literal_no_language
    : QUOTED_STRING {
        printf("String literal: %s\n", cowl_string_get_cstring($1));
        cowl_string_release($1);
    }
;

string_literal_with_language
    : QUOTED_STRING LANG_TAG {
        printf("String literal: %s %s\n", cowl_string_get_cstring($1), cowl_string_get_cstring($2));
        cowl_string_release($1);
        cowl_string_release($2);
    }
;

// Entity declarations and typing

declaration
    : DECLARATION L_PAREN axiom_annotations entity R_PAREN
;

entity
    : CLASS L_PAREN class R_PAREN
    | DATATYPE L_PAREN datatype R_PAREN
    | OBJECT_PROPERTY L_PAREN object_property R_PAREN
    | DATA_PROPERTY L_PAREN data_property R_PAREN
    | ANNOTATION_PROPERTY L_PAREN annotation_property R_PAREN
    | NAMED_INDIVIDUAL L_PAREN named_individual R_PAREN
;

// Object property expressions

object_property_expression
    : object_property
    | inverse_object_property
;

inverse_object_property
    : OBJECT_INVERSE_OF L_PAREN object_property R_PAREN
;

// Data property expressions

data_property_expression
    : data_property
;

// Data ranges

data_range
    : datatype
    | data_intersection_of
    | data_union_of
    | data_complement_of
    | data_one_of
    | datatype_restriction
;

data_intersection_of
    : DATA_INTERSECTION_OF L_PAREN data_range_2_list R_PAREN
;

data_union_of
    : DATA_UNION_OF L_PAREN data_range_2_list R_PAREN
;

data_complement_of
    : DATA_COMPLEMENT_OF L_PAREN data_range R_PAREN
;

data_one_of
    : DATA_ONE_OF L_PAREN literal_list R_PAREN
;

datatype_restriction
    : DATATYPE_RESTRICTION L_PAREN datatype datatype_restriction_value_list R_PAREN
;

datatype_restriction_value_list
    : datatype_restriction_value
    | datatype_restriction_value_list datatype_restriction_value
;

datatype_restriction_value
    : constraining_facet restriction_value
;

constraining_facet
    : iri
;

restriction_value
    : literal
;

// Class expressions

class_expression
    : class
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
    : OBJECT_INTERSECTION_OF L_PAREN class_expression_2_list R_PAREN
;

object_union_of
    : OBJECT_UNION_OF L_PAREN class_expression_2_list R_PAREN
;

object_complement_of
    : OBJECT_COMPLEMENT_OF L_PAREN class_expression R_PAREN
;

object_one_of
    : OBJECT_ONE_OF L_PAREN individual_list R_PAREN
;

object_some_values_from
    : OBJECT_SOME_VALUES_FROM L_PAREN object_property_expression class_expression R_PAREN
;

object_all_values_from
    : OBJECT_ALL_VALUES_FROM L_PAREN object_property_expression class_expression R_PAREN
;

object_has_value
    : OBJECT_HAS_VALUE L_PAREN object_property_expression individual R_PAREN
;

object_has_self
    : OBJECT_HAS_SELF L_PAREN object_property_expression R_PAREN
;

object_min_cardinality
    : OBJECT_MIN_CARDINALITY L_PAREN object_cardinality_body R_PAREN
;

object_max_cardinality
    : OBJECT_MAX_CARDINALITY L_PAREN object_cardinality_body R_PAREN
;

object_exact_cardinality
    : OBJECT_EXACT_CARDINALITY L_PAREN object_cardinality_body R_PAREN
;

object_cardinality_body
    : NON_NEGATIVE_INTEGER object_property_expression { printf("Cardinality: %d\n", $1); }
    | NON_NEGATIVE_INTEGER object_property_expression class_expression
;

data_some_values_from
    : DATA_SOME_VALUES_FROM L_PAREN data_property_expression_list data_range R_PAREN
;

data_all_values_from
    : DATA_ALL_VALUES_FROM L_PAREN data_property_expression_list data_range R_PAREN
;

data_has_value
    : DATA_HAS_VALUE L_PAREN data_property_expression literal R_PAREN
;

data_min_cardinality
    : DATA_MIN_CARDINALITY L_PAREN data_cardinality_body R_PAREN
;

data_max_cardinality
    : DATA_MAX_CARDINALITY L_PAREN data_cardinality_body R_PAREN
;

data_exact_cardinality
    : DATA_EXACT_CARDINALITY L_PAREN data_cardinality_body R_PAREN
;

data_cardinality_body
    : NON_NEGATIVE_INTEGER data_property_expression
    | NON_NEGATIVE_INTEGER data_property_expression data_range
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

axiom_annotations
    : %empty
    | axiom_annotations annotation
;

// Class expression axioms

class_axiom
    : sub_class_of
    | equivalent_classes
    | disjoint_classes
    | disjoint_union
;

sub_class_of
    : SUB_CLASS_OF L_PAREN axiom_annotations sub_class_expression super_class_expression R_PAREN
;

sub_class_expression
    : class_expression
;

super_class_expression
    : class_expression
;

equivalent_classes
    : EQUIVALENT_CLASSES L_PAREN axiom_annotations class_expression_2_list R_PAREN
;

disjoint_classes
    : DISJOINT_CLASSES L_PAREN axiom_annotations class_expression_2_list R_PAREN
;

disjoint_union
    : DISJOINT_UNION L_PAREN axiom_annotations class disjoint_class_expressions R_PAREN
;

disjoint_class_expressions
    : class_expression_2_list
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
    : SUB_OBJECT_PROPERTY_OF L_PAREN axiom_annotations sub_object_property_expression super_object_property_expression R_PAREN
;

sub_object_property_expression
    : object_property_expression
    | property_expression_chain
;

property_expression_chain
    : OBJECT_PROPERTY_CHAIN L_PAREN object_property_expression_2_list R_PAREN
;

super_object_property_expression
    : object_property_expression
;

equivalent_object_properties
    : EQUIVALENT_OBJECT_PROPERTIES L_PAREN axiom_annotations object_property_expression_2_list R_PAREN
;

disjoint_object_properties
    : DISJOINT_OBJECT_PROPERTIES L_PAREN axiom_annotations object_property_expression_2_list R_PAREN
;

inverse_object_properties
    : INVERSE_OBJECT_PROPERTIES L_PAREN axiom_annotations object_property_expression object_property_expression R_PAREN
;

object_property_domain
    : OBJECT_PROPERTY_DOMAIN L_PAREN axiom_annotations object_property_expression class_expression R_PAREN
;

object_property_range
    : OBJECT_PROPERTY_RANGE L_PAREN axiom_annotations object_property_expression class_expression R_PAREN
;

functional_object_property
    : FUNCTIONAL_OBJECT_PROPERTY L_PAREN axiom_annotations object_property_expression R_PAREN
;

inverse_functional_object_property
    : INVERSE_FUNCTIONAL_OBJECT_PROPERTY L_PAREN axiom_annotations object_property_expression R_PAREN
;

reflexive_object_property
    : REFLEXIVE_OBJECT_PROPERTY L_PAREN axiom_annotations object_property_expression R_PAREN
;

irreflexive_object_property
    : IRREFLEXIVE_OBJECT_PROPERTY L_PAREN axiom_annotations object_property_expression R_PAREN
;

symmetric_object_property
    : SYMMETRIC_OBJECT_PROPERTY L_PAREN axiom_annotations object_property_expression R_PAREN
;

asymmetric_object_property
    : ASYMMETRIC_OBJECT_PROPERTY L_PAREN axiom_annotations object_property_expression R_PAREN
;

transitive_object_property
    : TRANSITIVE_OBJECT_PROPERTY L_PAREN axiom_annotations object_property_expression R_PAREN
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
    : SUB_DATA_PROPERTY_OF L_PAREN axiom_annotations sub_data_property_expression super_data_property_expression R_PAREN
;

sub_data_property_expression
    : data_property_expression
;

super_data_property_expression
    : data_property_expression
;

equivalent_data_properties
    : EQUIVALENT_DATA_PROPERTIES L_PAREN axiom_annotations data_property_expression_2_list R_PAREN
;

disjoint_data_properties
    : DISJOINT_DATA_PROPERTIES L_PAREN axiom_annotations data_property_expression_2_list R_PAREN
;

data_property_domain
    : DATA_PROPERTY_DOMAIN L_PAREN axiom_annotations data_property_expression class_expression R_PAREN
;

data_property_range
    : DATA_PROPERTY_RANGE L_PAREN axiom_annotations data_property_expression data_range R_PAREN
;

functional_data_property
    : FUNCTIONAL_DATA_PROPERTY L_PAREN axiom_annotations data_property_expression R_PAREN
;

// Datatype definitions

datatype_definition
    : DATATYPE_DEFINITION L_PAREN axiom_annotations datatype data_range R_PAREN
;

// Keys

has_key
    :   HAS_KEY L_PAREN axiom_annotations class_expression
            L_PAREN object_property_expression_star R_PAREN
            L_PAREN data_property_expression_star L_PAREN
        R_PAREN
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
    : SAME_INDIVIDUAL L_PAREN axiom_annotations individual_2_list R_PAREN
;

different_individuals
    : DIFFERENT_INDIVIDUALS L_PAREN axiom_annotations individual_2_list R_PAREN
;

class_assertion
    : CLASS_ASSERTION L_PAREN axiom_annotations class_expression individual R_PAREN
;

object_property_assertion
    : OBJECT_PROPERTY_ASSERTION L_PAREN axiom_annotations object_property_expression source_individual target_individual R_PAREN
;

negative_object_property_assertion
    : NEGATIVE_OBJECT_PROPERTY_ASSERTION L_PAREN axiom_annotations object_property_expression source_individual target_individual R_PAREN
;

data_property_assertion
    : DATA_PROPERTY_ASSERTION L_PAREN axiom_annotations data_property_expression source_individual target_value R_PAREN
;

negative_data_property_assertion
    : NEGATIVE_DATA_PROPERTY_ASSERTION L_PAREN axiom_annotations data_property_expression source_individual target_value R_PAREN
;

source_individual
    : individual
;

target_individual
    : individual
;

target_value
    : literal
;

// Annotations

annotation
    : ANNOTATION L_PAREN annotation_annotations annotation_property annotation_value R_PAREN
;

annotation_annotations
    : %empty
    | annotation_annotations annotation
;

annotation_value
    : anonymous_individual
    | iri
    | literal
;

// Annotation axioms

annotation_axiom
    : annotation_assertion
    | sub_annotation_property_of
    | annotation_property_domain
    | annotation_property_range
;

annotation_assertion
    : ANNOTATION_ASSERTION L_PAREN axiom_annotations annotation_property annotation_subject annotation_value R_PAREN
;

annotation_subject
    : iri
    | anonymous_individual
;

sub_annotation_property_of
    : SUB_ANNOTATION_PROPERTY_OF L_PAREN axiom_annotations sub_annotation_property super_annotation_property R_PAREN
;

sub_annotation_property
    : annotation_property
;

super_annotation_property
    : annotation_property
;

annotation_property_domain
    : ANNOTATION_PROPERTY_DOMAIN L_PAREN axiom_annotations annotation_property iri R_PAREN
;

annotation_property_range
    : ANNOTATION_PROPERTY_RANGE L_PAREN axiom_annotations annotation_property iri R_PAREN
;

// Lists

class_expression_list
    : class_expression
    | class_expression_list class_expression
;

class_expression_2_list
    : class_expression_list class_expression
;

data_property_expression_list
    : data_property_expression
    | data_property_expression_list data_property_expression
;

data_property_expression_2_list
    : data_property_expression_list data_property_expression
;

data_property_expression_star
    : %empty
    | data_property_expression_star data_property_expression
;

data_range_list
    : data_range
    | data_range_list data_range
;

data_range_2_list
    : data_range_list data_range
;

individual_list
    : individual
    | individual_list individual
;

individual_2_list
    : individual_list individual
;

literal_list
    : literal
    | literal_list literal
;

object_property_expression_list
    : object_property_expression
    | object_property_expression_list object_property_expression
;

object_property_expression_2_list
    : object_property_expression_list object_property_expression
;

object_property_expression_star
    : %empty
    | object_property_expression_star object_property_expression
;

%%