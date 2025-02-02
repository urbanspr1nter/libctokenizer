#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "modules/libcstring/src/c_string.h"
#include "c_tokenizer.h"

#define MAX_LINE_SIZE 32768

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: tokenizer [FILE] [DELIM]\n");
        exit(1);
    }

    char* filepath = argv[1];
    char* delimeters = argv[2];
    
    String* delimStr = NULL;
    delimStr = cstring_create(delimStr, delimeters);

    FILE* fp;
    fp = fopen(filepath, "r");
    if (fp == NULL) {
        fprintf(stderr, "Could not open file: %s\n", filepath);
        exit(1);
    }

    String* content = NULL;
    content = cstring_create(content, "");

    int64_t bytesRead;
    size_t lineBytesRead;
    char* line = NULL;
    while ((bytesRead = getline(&line, &lineBytesRead, fp)) != -1) {
        // Remove the excess \n
        *(line + bytesRead) = '\0'; 

        String* lineStr = NULL;
        lineStr = cstring_create(lineStr, line);

        content = cstring_concat(content, 2, content, lineStr);
        
        cstring_free(lineStr);
    }

    fclose(fp);

    struct TokenCollection* tokens = ctok_tokenize(content, delimStr);
    ctok_printTokens(tokens);

    ctok_free(tokens);  
    cstring_free(content);    
    cstring_free(delimStr);

    free(line);
    
    return 0;
}
