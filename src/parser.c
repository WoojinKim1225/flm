#include "include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

parser_T* init_parser(lexer_T* lexer) {
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->currentToken = lexer_get_next_token(lexer);
    parser->prevToken = parser->currentToken;

    return parser;
}

void parser_eat(parser_T* parser, int token_type){
    if (parser->currentToken->type == token_type) {
        parser->prevToken = parser->currentToken;
        parser->currentToken = lexer_get_next_token(parser->lexer);
        printf("(%d, %s) => (%d, %s)\n",parser->prevToken->type, parser->prevToken->value, parser->currentToken->type, parser->currentToken->value);
    } else {
        printf("Unexpected token '%s', with type %d",
            parser->currentToken->value,
            parser->currentToken->type);
        exit(1);
    }
}

AST_T* parser_parse(parser_T* parser){
    return parser_parse_statements(parser);
}

AST_T* parser_parse_statement(parser_T* parser){
    switch (parser->currentToken->type) {
        case TOKEN_ID: return parser_parse_id(parser);
    }

    return init_ast(AST_NO_OPERATION);
}

AST_T* parser_parse_statements(parser_T* parser){
    AST_T* compound = init_ast(AST_COMPOUND);
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));

    AST_T* ast_statement = parser_parse_statement(parser);
    compound->compound_value[0] = ast_statement;
    compound->compound_size++;

    while (parser->currentToken->type == TOKEN_SEMICOLON) {
        parser_eat(parser, TOKEN_SEMICOLON);
        
        AST_T* ast_statement = parser_parse_statement(parser);

        if (ast_statement) {
            compound->compound_size++;
            compound->compound_value = realloc(compound->compound_value, compound->compound_size * sizeof(struct AST_STRUCT*));
            compound->compound_value[compound->compound_size - 1] = ast_statement;
        }
    }
    return compound;
}

AST_T* parser_parse_expr(parser_T* parser){
    switch(parser->currentToken->type)
    {
        case TOKEN_STRING: return parser_parse_string(parser);
        case TOKEN_NUMBER: return parser_parse_number(parser);
        case TOKEN_ID: return parser_parse_id(parser);
    }

    return init_ast(AST_NO_OPERATION);
}

AST_T* parser_parse_factor(parser_T* parser){
    
}

AST_T* parser_parse_term(parser_T* parser){
    
}

AST_T* parser_parse_function_call(parser_T* parser){
    // printf("func name %s\n", parser->prevToken->value);

    AST_T* functionCall = init_ast(AST_FUNCTION_CALL);
    functionCall->function_call_name = parser->prevToken->value;
    parser_eat(parser, TOKEN_PAREN_L);

    functionCall->function_call_arguments = calloc(1, sizeof(struct AST_STRUCT*));

    AST_T* ast_expr = parser_parse_expr(parser);
    functionCall->function_call_arguments[0] = ast_expr;
    functionCall->function_call_arguments_size++;

    while (parser->currentToken->type == TOKEN_COMMA) {
        parser_eat(parser, TOKEN_COMMA);

        AST_T* ast_expr = parser_parse_statement(parser);
        functionCall->function_call_arguments_size++;
        functionCall->function_call_arguments = realloc(functionCall->function_call_arguments, functionCall->function_call_arguments_size * sizeof(struct AST_STRUCT*));
        functionCall->function_call_arguments[functionCall->function_call_arguments_size-1] = ast_expr;
    }
    parser_eat(parser, TOKEN_PAREN_R);
    return functionCall;
}

AST_T* parser_parse_variable_definition(parser_T* parser) {
    printf("defining variable");
    parser_eat(parser, TOKEN_ID);
    char* variableDefName = parser->currentToken->value;
    parser_eat(parser, TOKEN_ID);
    parser_eat(parser, TOKEN_SUBS);

    AST_T* variableDefValue = parser_parse_expr(parser);

    AST_T* variableDefinition = init_ast(AST_VARIABLE_DEFINITION);
    variableDefinition->variable_definition_var_name = variableDefName;
    variableDefinition->variable_definition_value = variableDefValue;

    return variableDefinition;
}

AST_T* parser_parse_variable(parser_T* parser){
    char* tokenValue = parser->currentToken->value;
    parser_eat(parser, TOKEN_ID);

    if (parser->currentToken->type == TOKEN_PAREN_L)
        return parser_parse_function_call(parser);
    
    AST_T* ast_variable = init_ast(AST_VARIABLE);
    ast_variable->variable_name = tokenValue;
    return ast_variable;
}

AST_T* parser_parse_string(parser_T* parser){
    AST_T* astString = init_ast(AST_STRING);
    astString->string_value = parser->currentToken->value;
    parser_eat(parser, TOKEN_STRING);

    return astString;
}

AST_T* parser_parse_number(parser_T* parser){
    AST_T* astNumber = init_ast(AST_NUMBER);
    astNumber->number_value = parser->currentToken->value;
    parser_eat(parser, TOKEN_NUMBER);

    return astNumber;
}

AST_T* parser_parse_id(parser_T* parser){
    if (strcmp(parser->currentToken->value, "var") == 0 || strcmp(parser->currentToken->value, "int") == 0 || strcmp(parser->currentToken->value, "str") == 0) {
        return parser_parse_variable_definition(parser);
    } else {
        return parser_parse_variable(parser);
    }
}