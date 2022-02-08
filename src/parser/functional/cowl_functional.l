/**
 * @author Ivano Bilenchi
 *
 * @copyright Copyright (c) 2019-2021 SisInf Lab, Polytechnic University of Bari
 * @copyright <http://swot.sisinflab.poliba.it>
 * @copyright SPDX-License-Identifier: EPL-2.0
 *
 * @file
 */

%option prefix="cowl_func_yy"
%option 8bit reentrant bison-bridge bison-locations
%option warn nodefault
%option yylineno batch
%option noyywrap nounput noinput
%option noyyalloc noyyrealloc noyyfree
%option extra-type="UIStream *"

%top{
    #include "cowl_func_yyparser.h"
}

%{
    #include "cowl_cstring.h"

    #define YY_INPUT(buf, result, max_size) do {                                                    \
        size_t cowl_yyinput_read;                                                                   \
        if (uistream_read(yyextra, buf, max_size, &cowl_yyinput_read))                              \
            YY_FATAL_ERROR("Failed to read from stream");                                           \
        result = (int)cowl_yyinput_read;                                                            \
    } while(0)

    #define YY_USER_ACTION ((yylloc)->first_line = (yylloc)->last_line = yylineno);

    void* yyalloc(size_t bytes, cowl_unused void *yyscanner) {
        return ulib_malloc(bytes);
    }

    void* yyrealloc(void *ptr, size_t bytes, cowl_unused void *yyscanner) {
        return ulib_realloc(ptr, bytes);
    }

    void yyfree(void *ptr, cowl_unused void *yyscanner) {
        ulib_free(ptr);
    }
%}

WHITESPACE                              [ \t\r\n]+
COMMENT                                 "#"[^\n]*
DIGIT                                   [0-9]
ALPHA                                   [A-Za-z]
ALNUM                                   ({ALPHA}|{DIGIT})
PN_CHARS_BASE                           {ALPHA}
PN_CHARS_U                              ({PN_CHARS_BASE}|_)
PN_CHARS                                ({PN_CHARS_U}|-|{DIGIT})
PN_PREFIX                               {PN_CHARS_BASE}(({PN_CHARS}|\.)*{PN_CHARS})?
PN_LOCAL                                ({PN_CHARS_U}|{DIGIT})(({PN_CHARS}|\.)*{PN_CHARS})?
PNAME_NS                                {PN_PREFIX}?:
PNAME_LN                                {PNAME_NS}{PN_LOCAL}
IRI_REF                                 <[^<>"{}|\^`\\ ]{-}[\x00-\x20]*>
BLANK_NODE_LABEL                        _:{PN_LOCAL}
LANG_TAG                                @{ALPHA}+(-{ALNUM}+)*
QUOTED_STRING                           \"([^\"\\]|\\\"|\\\\)*\"
NON_NEGATIVE_INTEGER                    {DIGIT}+

%%

{WHITESPACE}                            ;

"Import"                                { return IMPORT; }
"Ontology"                              { return ONTOLOGY; }
"Prefix"                                { return PREFIX; }
"Declaration"                           { return DECLARATION; }
"Annotation"                            { return ANNOTATION; }
"DatatypeDefinition"                    { return DATATYPE_DEFINITION; }
"HasKey"                                { return HAS_KEY; }

"Class"                                 { return CLASS; }
"Datatype"                              { return DATATYPE; }
"ObjectProperty"                        { return OBJECT_PROPERTY; }
"DataProperty"                          { return DATA_PROPERTY; }
"AnnotationProperty"                    { return ANNOTATION_PROPERTY; }
"NamedIndividual"                       { return NAMED_INDIVIDUAL; }

"DataIntersectionOf"                    { return DATA_INTERSECTION_OF; }
"DataUnionOf"                           { return DATA_UNION_OF; }
"DataComplementOf"                      { return DATA_COMPLEMENT_OF; }
"DataOneOf"                             { return DATA_ONE_OF; }
"DatatypeRestriction"                   { return DATATYPE_RESTRICTION; }
"DataSomeValuesFrom"                    { return DATA_SOME_VALUES_FROM; }
"DataAllValuesFrom"                     { return DATA_ALL_VALUES_FROM; }
"DataHasValue"                          { return DATA_HAS_VALUE; }
"DataMinCardinality"                    { return DATA_MIN_CARDINALITY; }
"DataMaxCardinality"                    { return DATA_MAX_CARDINALITY; }
"DataExactCardinality"                  { return DATA_EXACT_CARDINALITY; }

"ObjectInverseOf"                       { return OBJECT_INVERSE_OF; }
"ObjectIntersectionOf"                  { return OBJECT_INTERSECTION_OF; }
"ObjectUnionOf"                         { return OBJECT_UNION_OF; }
"ObjectComplementOf"                    { return OBJECT_COMPLEMENT_OF; }
"ObjectOneOf"                           { return OBJECT_ONE_OF; }
"ObjectSomeValuesFrom"                  { return OBJECT_SOME_VALUES_FROM; }
"ObjectAllValuesFrom"                   { return OBJECT_ALL_VALUES_FROM; }
"ObjectHasValue"                        { return OBJECT_HAS_VALUE; }
"ObjectHasSelf"                         { return OBJECT_HAS_SELF; }
"ObjectMinCardinality"                  { return OBJECT_MIN_CARDINALITY; }
"ObjectMaxCardinality"                  { return OBJECT_MAX_CARDINALITY; }
"ObjectExactCardinality"                { return OBJECT_EXACT_CARDINALITY; }

"SubClassOf"                            { return SUB_CLASS_OF; }
"EquivalentClasses"                     { return EQUIVALENT_CLASSES; }
"DisjointClasses"                       { return DISJOINT_CLASSES; }
"DisjointUnion"                         { return DISJOINT_UNION; }

"SubObjectPropertyOf"                   { return SUB_OBJECT_PROPERTY_OF; }
"EquivalentObjectProperties"            { return EQUIVALENT_OBJECT_PROPERTIES; }
"DisjointObjectProperties"              { return DISJOINT_OBJECT_PROPERTIES; }
"InverseObjectProperties"               { return INVERSE_OBJECT_PROPERTIES; }
"ObjectPropertyDomain"                  { return OBJECT_PROPERTY_DOMAIN; }
"ObjectPropertyRange"                   { return OBJECT_PROPERTY_RANGE; }
"FunctionalObjectProperty"              { return FUNCTIONAL_OBJECT_PROPERTY; }
"InverseFunctionalObjectProperty"       { return INVERSE_FUNCTIONAL_OBJECT_PROPERTY; }
"ReflexiveObjectProperty"               { return REFLEXIVE_OBJECT_PROPERTY; }
"IrreflexiveObjectProperty"             { return IRREFLEXIVE_OBJECT_PROPERTY; }
"SymmetricObjectProperty"               { return SYMMETRIC_OBJECT_PROPERTY; }
"AsymmetricObjectProperty"              { return ASYMMETRIC_OBJECT_PROPERTY; }
"TransitiveObjectProperty"              { return TRANSITIVE_OBJECT_PROPERTY; }
"ObjectPropertyChain"                   { return OBJECT_PROPERTY_CHAIN; }

"SubDataPropertyOf"                     { return SUB_DATA_PROPERTY_OF; }
"EquivalentDataProperties"              { return EQUIVALENT_DATA_PROPERTIES; }
"DisjointDataProperties"                { return DISJOINT_DATA_PROPERTIES; }
"DataPropertyDomain"                    { return DATA_PROPERTY_DOMAIN; }
"DataPropertyRange"                     { return DATA_PROPERTY_RANGE; }
"FunctionalDataProperty"                { return FUNCTIONAL_DATA_PROPERTY; }

"SameIndividual"                        { return SAME_INDIVIDUAL; }
"DifferentIndividuals"                  { return DIFFERENT_INDIVIDUALS; }
"ClassAssertion"                        { return CLASS_ASSERTION; }
"ObjectPropertyAssertion"               { return OBJECT_PROPERTY_ASSERTION; }
"NegativeObjectPropertyAssertion"       { return NEGATIVE_OBJECT_PROPERTY_ASSERTION; }
"DataPropertyAssertion"                 { return DATA_PROPERTY_ASSERTION; }
"NegativeDataPropertyAssertion"         { return NEGATIVE_DATA_PROPERTY_ASSERTION; }

"AnnotationAssertion"                   { return ANNOTATION_ASSERTION; }
"SubAnnotationPropertyOf"               { return SUB_ANNOTATION_PROPERTY_OF; }
"AnnotationPropertyDomain"              { return ANNOTATION_PROPERTY_DOMAIN; }
"AnnotationPropertyRange"               { return ANNOTATION_PROPERTY_RANGE; }

{NON_NEGATIVE_INTEGER} {
    yylval->NON_NEGATIVE_INTEGER = (ulib_uint)cowl_str_to_uint(yytext, (size_t)yyleng);
    return NON_NEGATIVE_INTEGER;
}

{IRI_REF} {
    yylval->IRI_REF = ustring_wrap(yytext + 1, (ulib_uint)(yyleng - 2));
    return IRI_REF;
}

{PNAME_NS} {
    yylval->PNAME_NS = ustring_wrap(yytext, (ulib_uint)yyleng);
    return PNAME_NS;
}

{PNAME_LN} {
    yylval->PNAME_LN = ustring_wrap(yytext, (ulib_uint)yyleng);
    return PNAME_LN;
}

{BLANK_NODE_LABEL} {
    yylval->BLANK_NODE_LABEL = ustring_wrap(yytext + 2, (ulib_uint)(yyleng - 2));
    return BLANK_NODE_LABEL;
}

{LANG_TAG} {
    yylval->LANG_TAG = ustring_wrap(yytext + 1, (ulib_uint)(yyleng - 1));
    return LANG_TAG;
}

{QUOTED_STRING} {
    yylval->QUOTED_STRING = ustring_wrap(yytext + 1, (ulib_uint)(yyleng - 2));
    return QUOTED_STRING;
}

"^^"                                    { return DOUBLE_CARET; }
"("                                     { return L_PAREN; }
")"                                     { return R_PAREN; }
"="                                     { return EQUALS; }

{COMMENT}                               ;
.                                       { return *yytext; }
