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
    char* s = calloc(1, sizeof(char));
    if (ast->value->type == AST_FUNCTION){
        const char* template =  ".globl %s\n"
                                "%s:\n";
        s = realloc(s, (strlen(template) + strlen(ast->name) * 2 + 1) * sizeof(char));
        sprintf(s, template, ast->name, ast->name);

        ASTT* astValue = ast->value;

        char* astVV = asmF(astValue->value);

        s = realloc(s, (strlen(s) + strlen(astVV) + 1) * sizeof(char));
        strcat(s, astVV);
    }

    return s;
}

char* asmFVariable(ASTT* ast){

}

char* asmFCall(ASTT* ast){
    char* s = calloc(1, sizeof(char));
    if (strcmp(ast->name, "return") == 0) {
        ASTT* arg1 = (ASTT*)(ast->value->children->size ? ast->value->children->items[0] : (void*)0);
        const char* template =  "mov $%d, %%eax\n"
                                "ret\n";
        const char* retS = calloc(strlen(template) + 128, sizeof(char));
        sprintf(retS, template, arg1? arg1->intValue : 0);
        s = realloc(s, (strlen(retS) + 1) * sizeof(char));
        strcat(s, retS);

    }
    return s;
}

char* asmFInt(ASTT* ast){

}

char* asmFRoot(ASTT* ast){
#if defined(__x86_64__) || defined(_M_X64)
    const char* sectionText = ".section .text\n"
                                ".globl _start\n"
                                "_start:\n"
                                "call main\n"
                                "mov %eax, %ebx\n"
                                "mov $60, %eax\n"
                                "syscall\n\n"; // For 64-bit
#else
    const char* sectionText = ".section .text\n"
                                ".globl _start\n"
                                "_start:\n"
                                "call main\n"
                                "mov %eax, %ebx\n"
                                "mov $1, %eax\n"
                                "int $0x80\n\n"; // For 32-bit
#endif

    char* value = (char*) calloc((strlen(sectionText) + 128), sizeof(char));
    strcpy(value, sectionText);

    char* nextValue = asmF(ast);
    value =(char*) realloc(value, (strlen(value) + strlen(nextValue) + 1) * sizeof(char));
    strcat(value, nextValue);

    return value;
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
    value =(char*) realloc(value, (strlen(nextValue) + 1) * sizeof(char));
    strcat(value, nextValue);

    return value;
}