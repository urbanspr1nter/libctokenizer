#include <stdio.h>
#include <stdlib.h>
#include "c_tokenizer.h"

static void* safeMalloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "safeMalloc - couldn't allocate pointer of %d bytes.\n", size);
        exit(1);
    }

    return ptr;
}

static void safeFree(void* ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "safeFree - attempting to free a NULL pointer.\n");
        exit(1);
    }

    free(ptr);
}

static struct Token* createToken(String* text) {
    struct Token* token = safeMalloc(sizeof(struct Token));

    token->value = text;

    return token;
}

static void push(struct TokenCollection* collection, struct Token* token) {
    float lf = (float)collection->count / collection->length;
    if (lf > 0.75) {
        uint64_t newLength = collection->length * 2;

        struct Token** newTokens = safeMalloc(newLength * sizeof(struct Token*));
        for (size_t i = 0; i < collection->count; i++) {
            String* newTokenText;
            newTokenText = cstring_create(newTokenText, collection->tokens[i]->value->text);
            newTokens[i] = createToken(newTokenText);
        }

        freeTokens(collection->tokens, collection->count);
        safeFree(collection->tokens);

        collection->tokens = newTokens; 
        collection->length = newLength;
    }

    collection->tokens[collection->count] = token;
    collection->count++;
}

static void freeTokens(struct Token** tokens, uint64_t count) {
    for (size_t i = 0; i < count; i++) {
        cstring_free(tokens[i]->value);
        safeFree(tokens[i]);
    }
}

void ctok_free(struct TokenCollection* collection) {
    freeTokens(collection->tokens, collection->count);
    safeFree(collection->tokens);
    safeFree(collection);
}

void ctok_printTokens(struct TokenCollection* collection) {
    for (size_t i = 0; i < collection->count; i++) {
        printf("%s\n", collection->tokens[i]->value->text);
    }
}