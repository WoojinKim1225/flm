#include "include/parser.h"
#include "include/types.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

parserT* initParser(lexerT* lexer){
    parserT* parser = calloc(1, sizeof(struct PARSER_STRUCT));\
    parser->lexer = lexer;
    parser->token = lexerNextToken(lexer);

    return parser;
}

tokenT* parserEat(parserT* parser, int type){
    if (parser->token->type != type) {
        printf("[Parser]: Unexpected token: '%s', was expecting: '%s'\n", token2Str(parser->token), tokenType2Str(type));
        exit(1);
    }

    parser->token = lexerNextToken(parser->lexer);
    return parser->token;
}

ASTT* parserParse(parserT* parser){
    return parserParseCompound(parser);
    //return initAst(AST_NO_OPERATION);
}

ASTT* parserParseID(parserT* parser){
    char* value = calloc(strlen(parser->token->value), sizeof(char));
    strcpy(value, parser->token->value);
    parserEat(parser, TOKEN_ID);

    ASTT* ast = initAst(AST_VARIABLE);
    ast->name = value;

    if (parser->token->type == TOKEN_COLON) {
        ast->dataType = typename2int(parser->token->value);
        parserEat(parser, TOKEN_COLON);
        ast->dataSize = atoi(parser->token->value);
        parserEat(parser, TOKEN_INT);

        if (parser->token->type == TOKEN_POINTER) {
            ast->isPointer++;
            parserEat(parser, TOKEN_POINTER);
        }

        if (parser->token->type == TOKEN_ID) {
            ast->name = parser->token->value;
            value = parser->token->value;
        }
        parserEat(parser, TOKEN_ID);


        if (parser->token->type == TOKEN_BRACKET_L) {
            parserEat(parser, TOKEN_BRACKET_L);
            ast->isArray = 1;
            parserEat(parser, TOKEN_BRACKET_R);
        }

    } else {
        if (parser->token->type == TOKEN_PAREN_L) {
            ast->type = AST_CALL;
            ast->value = parserParseList(parser);
        }
    }

    if (parser->token->type == TOKEN_ASSIGNMENT) {
        parserEat(parser, TOKEN_ASSIGNMENT);
        ASTT* ast = initAst(AST_ASSIGNMENT);
        ast->name = value;
        
        ast->value = parserParseExpr(parser);
        return ast;
    } 

    return ast;
}

ASTT* parserParseList(parserT* parser){
    parserEat(parser, TOKEN_PAREN_L);

    ASTT* ast = initAst(AST_COMPOUND);
    listPush(ast->children, parserParseExpr(parser));
    while(parser->token->type == TOKEN_COMMA) {
        parserEat(parser, TOKEN_COMMA);
        listPush(ast->children, parserParseExpr(parser));
    }

    parserEat(parser, TOKEN_PAREN_R);
    /*
    if (parser->token->type == TOKEN_ARROW_R){
        parserEat(parser, TOKEN_ARROW_R);
        ast->type = AST_FUNCTION;
        ast->value = parserParseCompound(parser);
    }
    */
    if (parser->token->type == TOKEN_BRACE_L){
        ast->type = AST_FUNCTION;
        ast->value = parserParseCompound(parser);
    }
    return ast;
}

ASTT* parserParseInt(parserT* parser){
    int int_value = atoi(parser->token->value);
    parserEat(parser, TOKEN_INT);

    ASTT* ast = initAst(AST_INT);
    ast->intValue = int_value;

    return ast;
}

ASTT* parserParseExpr(parserT* parser){
    switch (parser->token->type) {
        case TOKEN_ID: 
            return parserParseID(parser);
        case TOKEN_PAREN_L: 
            return parserParseList(parser);
        case TOKEN_INT:
            return parserParseInt(parser);
        default: 
            printf("[Parser]: Unexpected token '%s'\n", token2Str(parser->token));
            exit(1);
    }
}

ASTT* parserParseCompound(parserT* parser){
    unsigned int shouldClose = 0;

    if (parser->token->type == TOKEN_BRACE_L){
        parserEat(parser, TOKEN_BRACE_L);
        shouldClose = 1;
    }
    ASTT* ast = initAst(AST_COMPOUND);

    while(parser->token->type != TOKEN_EOF && parser->token->type != TOKEN_BRACE_R) {
        listPush(ast->children, parserParseExpr(parser));

        if (parser->token->type == TOKEN_SEMICOLON) {
            parserEat(parser, TOKEN_SEMICOLON);
        }
    }

    if (shouldClose) {
        parserEat(parser, TOKEN_BRACE_R);
    }
    return ast;
}