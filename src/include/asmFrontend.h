#ifndef ASMFRONTEND_H
#define ASMFRONTEND_H
#include "AST.h"

char* asmFCompound(ASTT* ast);

char* asmFAssignment(ASTT* ast);

char* asmFVariable(ASTT* ast);

char* asmFCall(ASTT* ast);

char* asmFInt(ASTT* ast);

char* asmF(ASTT* ast);

#endif