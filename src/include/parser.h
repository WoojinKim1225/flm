#ifndef PARSER_H
#define PARSER_H
#include "lexer.h"
#include "AST.h"

typedef struct PARSER_STRUCT{
    lexerT* lexer;
    tokenT* token;
} parserT;

parserT* initParser(lexerT* lexer);

tokenT* parserEat(parserT* parser, int type);

ASTT* parserParse(parserT* parser);

ASTT* parserParseID(parserT* parser);

ASTT* parserParseExpr(parserT* parser);

ASTT* parserParseBlock(parserT* parser);

ASTT* parserParseList(parserT* parser);

ASTT* parserParseInt(parserT* parser);

ASTT* parserParseCompound(parserT* parser);

#endif