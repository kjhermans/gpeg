#include <gpeg/lib/gpeg/gpeg_capturelist.h>
#include <stdio.h>
extern int gpegc_grammar_process_node(gpeg_capture_t*,void*);
extern int gpegc_handle_GRAMMAR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_GRAMMAR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_S(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_S(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_MULTILINECOMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_MULTILINECOMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_COMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_COMMENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_END(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_END(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_DEFINITION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_DEFINITION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_RULE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_RULE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_EXPRESSION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_EXPRESSION(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_EXPRESSION_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_EXPRESSION_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_TERMS(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_TERMS(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_TERM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_TERM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SCANMATCHER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SCANMATCHER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_QUANTIFIEDMATCHER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_QUANTIFIEDMATCHER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_QUANTIFIER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_QUANTIFIER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_ZEROORONE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_ZEROORONE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_ONEORMORE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_ONEORMORE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_ZEROORMORE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_ZEROORMORE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_FROMTO(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_FROMTO(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_FROMTO_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_FROMTO_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_FROMTO_1(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_FROMTO_1(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_UNTIL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_UNTIL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_UNTIL_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_UNTIL_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_FROM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_FROM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_FROM_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_FROM_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_SPECIFIC(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_SPECIFIC(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_SPECIFIC_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_SPECIFIC_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_Q_VAR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_Q_VAR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_MATCHER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_MATCHER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_BITMASK(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_BITMASK(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_VARCAPTURE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_VARCAPTURE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_CAPTURETYPE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_CAPTURETYPE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_TYPE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_TYPE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_CAPTURE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_CAPTURE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_GROUP(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_GROUP(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SET(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SET(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SET_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SET_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SET_1(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SET_1(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SET_2(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SET_2(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SET_3(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SET_3(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_VARREFERENCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_VARREFERENCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_REFERENCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_REFERENCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_LIMITEDCALL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_LIMITEDCALL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_LCMODES(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_LCMODES(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_LCPARAM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_LCPARAM(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_LEFTARROW(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_LEFTARROW(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_NOT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_NOT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_AND(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_AND(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_MACRO(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_MACRO(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_ENDFORCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_ENDFORCE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_HEXLITERAL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_HEXLITERAL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_NUMBER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_NUMBER(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_STRING(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_STRING(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_OR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_OR(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_ANY(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_ANY(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_IMPORTDECL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_IMPORTDECL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_KW_IMPORT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_KW_IMPORT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_OPTNAMESPACE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_OPTNAMESPACE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_KW_AS(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_KW_AS(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_STRINGLITERAL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_STRINGLITERAL(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_STRINGLITERAL_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_STRINGLITERAL_0(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_IDENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_IDENT(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_BOPEN(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_BOPEN(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_BCLOSE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_BCLOSE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_CBOPEN(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_CBOPEN(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_CBCLOSE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_CBCLOSE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_ABOPEN(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_ABOPEN(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_ABCLOSE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_ABCLOSE(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_COLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_COLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_SEMICOLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
extern int gpegc_handle_post_SEMICOLON(gpeg_capture_t*,unsigned,gpeg_capture_t*,void*);
