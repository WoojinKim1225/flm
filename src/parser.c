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

    if (parser->token->type == TOKEN_SUBS) {
        parserEat(parser, TOKEN_SUBS);
        ASTT* ast = initAst(AST_ASSIGNMENT);
        ast->name = value;
        
        ast->value = parserParseExpr(parser);
        return ast;
    } 

    if (parser->token->type == TOKEN_COLON) {
        ASTT* ast = initAst(AST_VARIABLE);
        ast->dataType = typename2int(parser->token->value);
        parserEat(parser, TOKEN_COLON);
        ast->dataSize = atoi(parser->token->value);
        parserEat(parser, TOKEN_INT);
        ast->name = parser->token->value;
        //parserEat(parser, TOKEN_ID);
        printf("%d, %d, %s \n", ast->dataType, ast->dataSize, ast->name);
        return ast;
    }
}

ASTT* parserParseList(parserT* parser){
    parserEat(parser, TOKEN_PAREN_L);

    ASTT* compound = initAst(AST_COMPOUND);

    listPush(compound->children, parserParseExpr(parser));
    printf("asdfasdf123");

    while(parser->token->type == TOKEN_COMMA) {
        printf("asdfasdf");
        parserEat(parser, TOKEN_COMMA);
        listPush(compound->children, parserParseExpr(parser));
    }

    parserEat(parser, TOKEN_PAREN_R);
    return compound;
}

ASTT* parserParseExpr(parserT* parser){
    printf("%d\n", parser->token->type);
    switch (parser->token->type) {
        case TOKEN_ID: return parserParseID(parser);
        case TOKEN_PAREN_L: {
            printf("entering parenthesis...\n");
            return parserParseList(parser);
        }
        default: 
            printf("[Parser]: Unexpected token '%s'\n", token2Str(parser->token));
            exit(1);
    }
}

ASTT* parserParseCompound(parserT* parser){
    ASTT* compound = initAst(AST_COMPOUND);

    while(parser->token->type != TOKEN_EOF) {
        listPush(compound->children, parserParseExpr(parser));
    }
    return compound;
}