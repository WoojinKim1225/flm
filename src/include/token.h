#ifndef TAC_TOKEN_H
#define TAC_TOKEN_H

typedef struct TOKEN_STRUCT{
    char* value;
    enum{     
        TOKEN_ID,
        TOKEN_SUBS,
        TOKEN_PAREN_L,
        TOKEN_PAREN_R,
        TOKEN_BRACE_L,
        TOKEN_BRACE_R,
        TOKEN_SEMICOLON,
        TOKEN_COLON,
        TOKEN_COMMA,
        TOKEN_LT,
        TOKEN_GT,
        TOKEN_ARROW_R,
        TOKEN_INT,
        TOKEN_EOF = -1,
    } type;
} tokenT;

tokenT* initToken(char* value, int type);

const char* tokenType2Str(int type);

char* token2Str(tokenT* token);

#endif