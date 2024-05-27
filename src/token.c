#include "include/token.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

tokenT* initToken(char* value, int type){
    tokenT* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->value = value;
    token->type = type;

    return token;
}

const char* tokenType2Str(int type) {
    switch(type) {
        case TOKEN_ID:
            return "TOKEN_ID";
        case TOKEN_ASSIGNMENT:
            return "TOKEN_ASSIGNMENT";
        case TOKEN_PAREN_L:
            return "TOKEN_PAREN_L";
        case TOKEN_PAREN_R:
            return "TOKEN_PAREN_R";
        case TOKEN_BRACE_L:
            return "TOKEN_BRACE_L";
        case TOKEN_BRACE_R:
            return "TOKEN_BRACE_R";
        case TOKEN_BRACKET_L:
            return "TOKEN_BRACKET_L";
        case TOKEN_BRACKET_R:
            return "TOKEN_BRACKET_R";
        case TOKEN_SEMICOLON:
            return "TOKEN_SEMICOLON";
        case TOKEN_COLON:
            return "TOKEN_COLON";
        case TOKEN_COMMA:
            return "TOKEN_COMMA";
        case TOKEN_LT:
            return "TOKEN_LT";
        case TOKEN_GT:
            return "TOKEN_GT";
        case TOKEN_OF:
            return "TOKEN_OF";
        case TOKEN_INT:
            return "TOKEN_INT";
        case TOKEN_EOF:
            return "TOKEN_EOF";
        default:
            return "NULL";
    }
}

char* token2Str(tokenT* token){
    const char* typeStr = tokenType2Str(token->type);
    const char* template = "<type=%s, int_type=%d, value='%s'>";

    char* str = calloc(strlen(typeStr) + strlen(template) + 8, sizeof(char));
    sprintf(str, template, typeStr, token->type, token->value);
    return str;
}