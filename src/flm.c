#include "include/flm.h"
#include "include/lexer.h"
#include "include/parser.h"
#include "include/io.h"
#include "include/asmFrontend.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>

static char* sh(char* cmd) {
    char* output = (char*)calloc(1, sizeof(char));
    output[0] = '\0';

    FILE *fp;
    char path[1035];
    fp = popen(cmd, "r");

    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    while (fgets(path, sizeof(path), fp) != NULL) {
        output = (char*)realloc(output, (strlen(output) + strlen(path) + 1) * sizeof(char));
    }

    pclose(fp);

    return output;
}

void flmCompile(char* src){
    lexerT* lexer = initLexer(src);
    parserT* parser = initParser(lexer);
    ASTT* root = parserParse(parser);
    
    char* s = asmFRoot(root);
    //printf("%s\n", s);
    
    flmWriteFile("a.s", s);
    sh("as a.s -o a.o");
    sh("ld a.o -o a.out");
}

void flmCompileFile(const char* filename){
    char* src = flmReadFile(filename);
    flmCompile(src);
    free(src);
}
