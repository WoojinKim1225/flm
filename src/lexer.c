#include "include/lexer.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdio.h"


lexer_T* init_lexer(char* contents)
{
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];

    return lexer;
}

void lexer_advance(lexer_T* lexer)
{
    if (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        lexer->i++;
        lexer->c = lexer->contents[lexer->i];
    }
}

void lexer_skip_whitespace(lexer_T* lexer)
{
    while (lexer->c == ' ' || lexer->c == 10 || lexer->c == 13) {
        lexer_advance(lexer);
    }
}


token_T* lexer_get_next_token(lexer_T* lexer)
{
    while (lexer->c != '\0' && lexer->i < strlen(lexer->contents)) {
        if (lexer->c == ' ' || lexer->c == 10 || lexer->c == 13) {
            lexer_skip_whitespace(lexer);
        }
        printf("\nlexer->c : %c\n", lexer->c);
        
        /*
        if (isalnum(lexer->c)) {
            printf("asdfa");
            return lexer_collect_id(lexer);
        }
        */

        if (isalpha(lexer->c)) {
            return lexer_collect_id(lexer);
        }

        if (isdigit(lexer->c)) {
            return lexer_collect_number(lexer);
        }
        

        if (lexer->c == '"') 
            return lexer_collect_string(lexer);
        
        switch (lexer->c)
        {
            case '=': 
                return lexer_advance_with_token(lexer, init_token(TOKEN_SUBS, lexer_get_current_char_as_string(lexer))); 
                break;
            
            case ';': 
                return lexer_advance_with_token(lexer, init_token(TOKEN_SEMICOLON, lexer_get_current_char_as_string(lexer))); 
                break;

            case '(':
                return lexer_advance_with_token(lexer, init_token(TOKEN_PAREN_L, lexer_get_current_char_as_string(lexer))); 
                break;
            
            case ')':
                return lexer_advance_with_token(lexer, init_token(TOKEN_PAREN_R, lexer_get_current_char_as_string(lexer))); 
                break;
            
            case ',':
                return lexer_advance_with_token(lexer, init_token(TOKEN_COMMA, lexer_get_current_char_as_string(lexer))); 
                break;
        }
    }
    return init_token(TOKEN_EOF, "\0");
}

token_T* lexer_collect_string(lexer_T* lexer) {
    lexer_advance(lexer);

    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (lexer->c != '"')
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    lexer_advance(lexer);
    printf("string value: %s\n", value);
    return init_token(TOKEN_STRING, value);
}

token_T* lexer_collect_number(lexer_T* lexer) {
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (isdigit(lexer->c))
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }
    printf("number value: %s\n", value);

    return init_token(TOKEN_NUMBER, value);
}

token_T* lexer_collect_id(lexer_T* lexer) {

    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while (isalnum(lexer->c))
    {
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    return init_token(TOKEN_ID, value);
}

token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token){
    lexer_advance(lexer);
    return token;
}

char* lexer_get_current_char_as_string(lexer_T* lexer) {
    char* str = calloc(2, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';
    return str;
}