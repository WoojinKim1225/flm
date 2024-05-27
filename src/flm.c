#include "include/flm.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"
#include "stdio.h"
#include <stdlib.h>

void flmCompile(char* src){
    lexerT* lexer = initLexer(src);
    parserT* parser = initParser(lexer);
    ASTT* root = parserParse(parser);
    printf("%p\n", root);
    printf("%d\n", root->children->size);
    
    tokenT* token = 0;

    while ((token = lexerNextToken(lexer))->type != TOKEN_EOF) {
        printf("%s", token2Str(token));
    }
    
}

void flmCompileFile(const char* filename){
    char* src = flmReadFile(filename);
    flmCompile(src);
    free(src);
}
