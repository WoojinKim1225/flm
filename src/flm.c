#include "include/flm.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"
#include "include/asmFrontend.h"
#include "stdio.h"
#include <stdlib.h>

void flmCompile(char* src){
    lexerT* lexer = initLexer(src);
    parserT* parser = initParser(lexer);
    ASTT* root = parserParse(parser);
    
    char* s = asmFRoot(root);
    printf("%s\n", s);
    
}

void flmCompileFile(const char* filename){
    char* src = flmReadFile(filename);
    flmCompile(src);
    free(src);
}
