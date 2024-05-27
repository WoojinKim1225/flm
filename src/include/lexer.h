#ifndef LEXER_H
#define LEXER_H
#include "token.h"
#include <stdlib.h>

typedef struct LEXER_STRUCT
{
    char* src;
    size_t srcSize;
    unsigned int i;
    char c;
} lexerT;

lexerT* initLexer(char* src);

void lexerAdvance(lexerT* lexer);

char lexerPeek(lexerT* lexer, int offset);

tokenT* lexerAdvanceWith(lexerT* lexer, tokenT* token);

tokenT* lexerAdvanceCurrent(lexerT* lexer, int type);

void lexerSkipWhitespace(lexerT* lexer);

tokenT* lexerParseID(lexerT* lexer);

tokenT* lexerParseNum(lexerT* lexer);

tokenT* lexerNextToken(lexerT* lexer);

#endif
