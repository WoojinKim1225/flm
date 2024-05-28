#include "include/asmFrontend.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* asmFCompound(ASTT* ast){
    char* value = calloc(1, sizeof(char));
    for (int i = 0; i < (int)ast->children->size; i++) {
        ASTT* childAST = (ASTT*)ast->children->items[i];
        char* nextValue = asmF(childAST);
        value = realloc(value, (strlen(nextValue) + 1)*sizeof(char));
        strcat(value, nextValue);
    }
    return value;
}

char* asmFAssignment(ASTT* ast){
    const char* example = "mov $128, %eax";
    char* s = calloc(strlen(example) + 1, sizeof(char));
    strcpy(s, example);
    return s;
}

char* asmFVariable(ASTT* ast){

}

char* asmFCall(ASTT* ast){

}

char* asmFInt(ASTT* ast){

}

char* asmF(ASTT* ast){
    char* value = calloc(1, sizeof(char));
    char* nextValue = 0;
    switch (ast->type){
    case AST_COMPOUND:
        nextValue = asmFCompound(ast);
        break;
    case AST_ASSIGNMENT: 
        nextValue = asmFAssignment(ast);
        break;
    case AST_VARIABLE:
        nextValue = asmFVariable(ast);
        break;
    case AST_CALL:
        nextValue = asmFCall(ast);
        break;
    case AST_INT:
        nextValue = asmFInt(ast);
        break;
    default:
        printf("[ASM Frontend]: No frontend for AST of type '%d'\n", ast->type);
        exit(1);
        break;
    }
    value = realloc(value, (strlen(nextValue) + 1) * sizeof(char));
    strcat(value, nextValue);

    return value;
}