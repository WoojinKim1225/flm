#ifndef AST_H
#define AST_H
#include "stddef.h"

typedef struct AST_STRUCT
{
    enum {
        AST_VARIABLE_DEFINITION,
        AST_VARIABLE,
        AST_FUNCTION_CALL,
        AST_NUMBER,
        AST_STRING,
        AST_COMPOUND,
        AST_NO_OPERATION = -1,
    } type;

    /* AST_VARIABLE_DEFINITION */
    char* variable_definition_var_name;
    struct AST_STRUCT* variable_definition_value;

    /* AST_VARIABLE */
    char* variable_name;

    /* AST_FUNCTION_CALL */
    char* function_call_name;
    struct AST_STRUCT** function_call_arguments;
    size_t function_call_arguments_size;

    /* AST_INTEGER */
    char* number_value;

    /* AST_STRING */
    char* string_value;

    /* AST_COMPOUND */
    struct AST_STRUCT** compound_value;
    size_t compound_size;
} AST_T;

AST_T* init_ast(int type);

#endif