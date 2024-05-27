#include "include/AST.h"
#include <stdlib.h>

ASTT* initAst(int type){
    ASTT* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;

    if (type == AST_COMPOUND) {
        ast->children = initList(sizeof(struct AST_STRUCT*));
    }

    return ast;
}