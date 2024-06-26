#include "include/io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* flmReadFile(const char* filename){
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    size_t read;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Could not read file '%s'\n", filename);
        exit(1);
    }

    char* buffer = (char*) calloc(1, sizeof(char));
    buffer[0] = '\0';

    while ((read = getline(&line, &len, fp))!= -1)
    {
        buffer = (char*) realloc(buffer, (strlen(buffer) + strlen(line) + 1) * sizeof(char));
        strcat(buffer, line);
    }

    fclose(fp);
    if (line) {
        free(line);
    }
    return buffer;   
}

void flmWriteFile(const char* filename, char* outBuffer){
    FILE* fp;
    char* line = NULL;

    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open file for writing '%s'\n", filename);
        exit(1);
    }

    fputs(outBuffer, fp);
    
    fclose(fp);
}