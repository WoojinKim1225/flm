#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT
{
    enum
    {
        TOKEN_ID,
        TOKEN_SUBS,
        TOKEN_NUMBER,
        TOKEN_STRING,
        TOKEN_SEMICOLON,
        TOKEN_PAREN_L,
        TOKEN_PAREN_R,
        TOKEN_COMMA,
        TOKEN_EOF = -1,
    } type;

    char* value;
} token_T;

token_T* init_token(int type, char* value);
#endif