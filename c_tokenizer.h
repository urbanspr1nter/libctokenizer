#ifndef C_TOKENIZER_H
#define C_TOKENIZER_H

#include <stdint.h>
#include "modules/libcstring/src/c_string.h"

struct Token {
    String* value;    
};

struct TokenCollection {
    struct Token** tokens;
    uint64_t count;
    uint64_t length;
};

struct TokenCollection* ctok_tokenize(String* data, String* delimeter);
void ctok_free(struct TokenCollection* tokens);
void ctok_printTokens(struct TokenCollection* collection);

#endif 