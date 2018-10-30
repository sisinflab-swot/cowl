%option 8bit reentrant bison-bridge bison-locations
%option warn nodefault
%option yylineno batch
%option noyywrap nounput noinput

%top{
    #include "cowl_std.h"
    #include "cowl_functional_parser.h"
}

%{
    #define YY_USER_ACTION ((yylloc)->first_line = (yylloc)->last_line = yylineno);
%}

WHITE_SPACE                             [ \t\r\n]+
COMMENT                                 "#"[^\n]*
DIGIT                                   [0-9]
DIGITS                                  {DIGIT}+
PN_CHARS_BASE                           [A-Za-z]
PN_CHARS_U                              ({PN_CHARS_BASE}|_)
PN_CHARS                                ({PN_CHARS_U}|-|{DIGIT})
PN_PREFIX                               {PN_CHARS_BASE}(({PN_CHARS}|\.)*{PN_CHARS})?
PN_LOCAL                                ({PN_CHARS_U}|{DIGIT})(({PN_CHARS}|\.)*{PN_CHARS})?
PNAME_NS                                {PN_PREFIX}?:
PNAME_LN                                {PNAME_NS}{PN_LOCAL}
IRI_REF                                 <[^<>"{}|\^`\\ ]{-}[\x00-\x20]*>
BLANK_NODE_LABEL                        _:{PN_LOCAL}
LANG_TAG                                @[A-Za-z]+(-[A-Za-z0-9]+)*
QUOTED_STRING                           \"([^\"\\]|\\\"|\\\\)*\"
NON_NEGATIVE_INTEGER                    {DIGITS}

%%

{WHITE_SPACE}                           ;

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

{NON_NEGATIVE_INTEGER}                  {
                                            yylval->NON_NEGATIVE_INTEGER = atoi(yytext);
                                            return NON_NEGATIVE_INTEGER;
                                        }
{IRI_REF}                               {
                                            yylval->IRI_REF =
                                                COWL_YY_STRING_INIT(yytext + 1, yyleng - 2);
                                            return IRI_REF;
                                        }
{PNAME_NS}                              {
                                            yylval->PNAME_NS =
                                                COWL_YY_STRING_INIT(yytext, yyleng);
                                            return PNAME_NS;
                                        }
{PNAME_LN}                              {
                                            yylval->PNAME_LN =
                                                COWL_YY_STRING_INIT(yytext, yyleng);
                                            return PNAME_LN;
                                        }
{BLANK_NODE_LABEL}                      {
                                            yylval->BLANK_NODE_LABEL =
                                                COWL_YY_STRING_INIT(yytext + 2, yyleng - 2);
                                            return BLANK_NODE_LABEL;
                                        }
{LANG_TAG}                              {
                                            yylval->LANG_TAG =
                                                COWL_YY_STRING_INIT(yytext + 1, yyleng - 1);
                                            return LANG_TAG;
                                        }
{QUOTED_STRING}                         {
                                            yylval->QUOTED_STRING =
                                                COWL_YY_STRING_INIT(yytext + 1, yyleng - 2);
                                            return QUOTED_STRING;
                                        }

"^^"                                    { return DOUBLE_CARET; }
"("                                     { return L_PAREN; }
")"                                     { return R_PAREN; }
"="                                     { return EQUALS; }

{COMMENT}                               ;
.                                       { return *yytext; }
