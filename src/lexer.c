#include "include/lexer.h"
#include "include/marco.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdio.h"


lexerT* initLexer(char* src){
    lexerT* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->srcSize = strlen(src);
    lexer->i = 0;
    lexer->c = src[lexer->i];

    return lexer;
}

void lexerAdvance(lexerT* lexer){
    if (lexer->c != '\0' && lexer->i < lexer->srcSize){
        lexer->i++;
        lexer->c = lexer->src[lexer->i];
    }
}

char lexerPeek(lexerT* lexer, int offset){
    return lexer->src[MIN(lexer->i + offset, lexer->srcSize)];
}

tokenT* lexerAdvanceWith(lexerT* lexer, tokenT* token){
    lexerAdvance(lexer);
    return token;
}

tokenT* lexerAdvanceCurrent(lexerT* lexer, int type){
    char* value = calloc(2, sizeof(char));
    value[0] = lexer->c;
    value[1] = '\0';

    tokenT* token = initToken(value, type);
    lexerAdvance(lexer);

    return token;
}

void lexerSkipWhitespace(lexerT* lexer){
    while (lexer->c == ' ' || lexer->c == 10 || lexer->c == 13 || lexer->c == '\t') {
        lexerAdvance(lexer);
    }
}

tokenT* lexerParseID(lexerT* lexer){
    char* value = calloc(1, sizeof(char));

    while (isalnum(lexer->c)) {
        value = realloc(value, (strlen(value)+ 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexerAdvance(lexer);
    }
    return initToken(value, TOKEN_ID);
}

tokenT* lexerParseNum(lexerT* lexer){
    char* value = calloc(1, sizeof(char));

    while (isalnum(lexer->c)) {
        value = realloc(value, (strlen(value)+ 2) * sizeof(char));
        strcat(value, (char[]){lexer->c, 0});
        lexerAdvance(lexer);
    }
    return initToken(value, TOKEN_INT);
}

tokenT* lexerNextToken(lexerT* lexer){
    while (lexer->c != '\0') {
        
        lexerSkipWhitespace(lexer);

        if (isalpha(lexer->c)) {
            return lexerParseID(lexer);
        }

        if (isdigit(lexer->c)) {
            return lexerAdvanceWith(lexer, lexerParseNum(lexer));
        }

        switch (lexer->c)
        {
        case '-':
            if (lexerPeek(lexer, 1) == '>'){
                return lexerAdvanceWith(lexer, initToken("->", TOKEN_ARROW_R));
            }
            break;

        case '=':
            return lexerAdvanceCurrent(lexer, TOKEN_SUBS);
            break;

        case '(': return lexerAdvanceCurrent(lexer, TOKEN_PAREN_L); break;

        case ')': return lexerAdvanceCurrent(lexer, TOKEN_PAREN_R); break;

        case '{': return lexerAdvanceCurrent(lexer, TOKEN_BRACE_L); break;

        case '}': return lexerAdvanceCurrent(lexer, TOKEN_BRACE_R); break;

        case ':': return lexerAdvanceCurrent(lexer, TOKEN_COLON); break;

        case ',': return lexerAdvanceCurrent(lexer, TOKEN_COMMA); break;

        case '<': return lexerAdvanceCurrent(lexer, TOKEN_LT); break;

        case '>': return lexerAdvanceCurrent(lexer, TOKEN_GT); break;

        case ';': return lexerAdvanceCurrent(lexer, TOKEN_SEMICOLON); break;

        case '\0': break;
        default:
            printf("[Lexer]: Unexpected character '%c'\n", lexer->c);
            exit(1);
            break;
        }
    }
    return initToken(0, TOKEN_EOF);
}
