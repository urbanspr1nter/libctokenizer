#ifndef C_TOKENIZER_H
#define C_TOKENIZER_H

#include <stdint.h>
#include "modules/libcstring/src/c_string.h"

struct Token {
    String* value;    
};

struct TokenCollection {
    struct Token** tokens;

};

#endif 