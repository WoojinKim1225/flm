#ifndef AST_H
#define AST_H
#include "list.h"

typedef struct AST_STRUCT{
    enum{
        AST_COMPOUND,
        AST_FUNCTION,
        AST_CALL,
        AST_ASSIGNMENT,
        AST_VARIABLE,
        AST_STATEMENT,
        AST_INT,
        AST_DEFINITION_TYPE,
        AST_NO_OPERATION = -1,
    }type;

    listT* children;
    char* name;
    struct AST_STRUCT* value;

    int dataType;
    size_t dataSize;

    int intValue;

    int isPointer;
    int isArray;
} ASTT;

ASTT* initAst(int type);

#endif