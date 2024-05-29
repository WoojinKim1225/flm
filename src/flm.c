#include "include/flm.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"
#include "include/asmFrontend.h"
#include "stdio.h"
#include <stdlib.h>

static char* sh(char* cmd) {
    char* output = (char*)calloc(1, sizeof(char));
    output[0] = '\0';

    FILE *fp;
    fp = popen(cmd, "r");

    if (fp == NULL) {
        printf("Failed to run command\n")
        ///----
    }
}

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
