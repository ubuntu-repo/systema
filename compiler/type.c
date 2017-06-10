#include <stdlib.h>
#include <string.h>

#include "common.h"

type_t *parse_type() {
    /* type: type_specifier type_modifiers */
    type_t *type = alloc_type();
    expr_t *expr;
    /* type specifier */
    get_lexeme();
    if (!strcmp(lex.val, "void")) {
        /* void type */
        type->specifier = TYPE_VOID;
        type->complete = 0;
        type->subcount = 0;
        type->subtype = NULL;
    } else if (!strcmp(lex.val, "byte")) {
        /* byte type */
        type->specifier = TYPE_BYTE;
        type->complete = 1;
        type->subcount = 0;
        type->subtype = NULL;
    } else if (!strcmp(lex.val, "twin")) {
        /* half type */
        type->specifier = TYPE_HALF;
        type->complete = 1;
        type->subcount = 0;
        type->subtype = NULL;
    } else if (!strcmp(lex.val, "quad")) {
        /* word type */
        type->specifier = TYPE_WORD;
        type->complete = 1;
        type->subcount = 0;
        type->subtype = NULL;
    } else if (!strcmp(lex.val, "octt")) {
        /* dobl type */
        type->specifier = TYPE_DOBL;
        type->complete = 1;
        type->subcount = 0;
        type->subtype = NULL;
    } else if (!strcmp(lex.val, "func")) {
        /* func type */
        type = parse_func_header();
    } else if (!strcmp(lex.val, "text")) {
        /* string type */
        type->specifier = TYPE_STRING;
        type->complete = 1;
        type->subcount = 0;
        type->subtype = NULL;
    } else if (!strcmp(lex.val, "record")) {
        type->specifier = TYPE_RECORD;
        type->complete = 1;
        type->subcount = 0;
        type->subtype = NULL;
        /* parse_record() */
    } else if (!strcmp(lex.val, "[")) {
        /* array */
        type->specifier = TYPE_ARRAY;
        /* look ahead */
        get_lexeme();
        unget_lexeme();
        /* size specified? */
        if (!strcmp("(", lex.val)) {
            /* expression */
            expr = parse_factor();
        } else if (lex.val[0] >= '0' && lex.val[0] <= '9') {
            /* numerical */
            expr = parse_factor();
        } else {
            expr = NULL;
        }
        /* evaluate size */
        if (expr) {
            /* expression must be literal word */
            if (!expr->literal) {
                print_err("array size must be literal", 0);
                type->subcount = 0;
            } else if (expr->type->specifier != TYPE_WORD) {
                print_err("array size must be an integral word", 0);
                type->subcount = 0;
            } else {
                type->subcount = expr->word_literal_val;
            }
            type->complete = 1;
        } else {
            /* size is not specified */
            type->subcount = 0;
            type->complete = 0;
        }
        /* subtype */
        type->subtype = parse_type();
        /* inner type must be completely specified */
        if (!type->subtype->complete) {
            print_err("inner array type must be completely specified",0);
        } 
        /* ] */
        get_lexeme();
        if (strcmp(lex.val, "]")) {
           print_err("expected ]",0);
           unget_lexeme();
        }
    } else if (!strcmp(lex.val, "@")) {
        /* pointer */
        type->specifier = TYPE_PTR;
        type->complete = 1;
        type->subcount = 1;
        type->subtype = parse_type();
    } else {
        /* error? */
        type->specifier = TYPE_VOID;
        type->complete = 0;
        type->subcount = 0;
        type->subtype = NULL;
        print_err("expected type specifier", 0);
    }
    /* finished */
    return type;
}
