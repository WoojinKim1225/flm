#include "include/visitor.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

static AST_T* builtin_function_print(visitor_T* visitor, AST_T** args, int args_size)
{
    for (int i = 0; i < args_size; i++) {
        AST_T* visitedAst = visitor_visit(visitor, args[i]);

        switch (visitedAst->type)
        {
            case AST_STRING: 
                printf("%s", visitedAst->string_value); 
                break;
            case AST_NUMBER:
                printf("%s", visitedAst->number_value);
            default:
                printf("%p", visitedAst);
                break;

        }
    }
    return init_ast(AST_NO_OPERATION);
}

visitor_T* init_visitor()
{
    visitor_T* visitor = calloc(1, sizeof(struct VISITOR_STRUCT));
    visitor->variable_definitions = (void*)0;
    visitor->variable_definitions_size = 0;

    return visitor;
}

AST_T* visitor_visit(visitor_T* visitor, AST_T* node){
    printf("%d\n", node->type);
    switch (node->type)
    {
        case AST_VARIABLE_DEFINITION: return visitor_visit_variable_definition(visitor, node); break;
        case AST_VARIABLE: return visitor_visit_variable(visitor, node); break;
        case AST_FUNCTION_CALL: return visitor_visit_function_call(visitor, node); break;
        case AST_NUMBER: return visitor_visit_number(visitor, node); break;
        case AST_STRING: return visitor_visit_string(visitor, node); break;
        case AST_COMPOUND: return visitor_visit_compound(visitor, node); break;
        case AST_NO_OPERATION: return node; break;
    }

    printf("Uncaught statement of type '%d'\n", node->type);
    exit(1);
}

AST_T* visitor_visit_variable_definition(visitor_T* visitor, AST_T* node){
    
    if (visitor->variable_definitions == (void*)0) {
        visitor->variable_definitions = calloc(1, sizeof(struct AST_STRUCT*));
        visitor->variable_definitions[0] = node;
        visitor->variable_definitions_size++;
    } else {
        visitor->variable_definitions_size++;
        visitor->variable_definitions = realloc(visitor->variable_definitions, visitor->variable_definitions_size * sizeof(struct AST_STRUCT*));
        visitor->variable_definitions[visitor->variable_definitions_size-1] = node;
    }

    return node;
}

AST_T* visitor_visit_variable(visitor_T* visitor, AST_T* node){
    for (int i = 0; i < visitor->variable_definitions_size; i++)
    {
        AST_T* vardef = visitor->variable_definitions[i];

        if (strcmp(vardef->variable_definition_var_name, node->variable_name) == 0) {
            return visitor_visit(visitor, vardef->variable_definition_value);
        }
    }

    printf("Undefined variable '%s'\n", node->variable_name);
    return node;
}

AST_T* visitor_visit_function_call(visitor_T* visitor, AST_T* node){
    if (strcmp(node->function_call_name, "print") == 0)
    {
        return builtin_function_print(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }
    printf("Undefined method '%s'\n", node->function_call_name);
    exit(1);
}

AST_T* visitor_visit_string(visitor_T* visitor, AST_T* node){
    return node;
}

AST_T* visitor_visit_number(visitor_T* visitor, AST_T* node){
    printf("!!!1");
    return node;
}

AST_T* visitor_visit_compound(visitor_T* visitor, AST_T* node){
    for (int i = 0; i < node->compound_size; i++)
    {
        visitor_visit(visitor, node->compound_value[i]);
    }

    return init_ast(AST_NO_OPERATION);
}