#include <stdio.h>
#include <stdlib.h>
#include "c_tokenizer.h"

#ifndef MAX_WORD_BUFFER_LENGTH
#define MAX_WORD_BUFFER_LENGTH 512
#endif

static void* safeMalloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "safeMalloc - couldn't allocate pointer of %ld bytes.\n", size);
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

static void freeTokens(struct Token** tokens, uint64_t count) {
    for (size_t i = 0; i < count; i++) {
        cstring_free(tokens[i]->value);
        safeFree(tokens[i]);
    }
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

        // Update tokens to point to the new collection
        collection->tokens = newTokens; 
        collection->length = newLength;
    }

    collection->tokens[collection->count] = token;
    collection->count++;
}

struct TokenCollection* ctok_tokenize(String* data, String* delimeter) {
    uint64_t initialTokensCollectionLength = 32;

    uint8_t delimeterTable[256] = {0};
    for (size_t i = 0; i < delimeter->length; i++) {
        delimeterTable[(uint8_t)delimeter->text[i]] = 1;
    }

    struct TokenCollection* collection = (struct TokenCollection*)safeMalloc(sizeof(struct TokenCollection));
    collection->tokens = (struct Token**)safeMalloc(sizeof(struct Token*) * initialTokensCollectionLength);
    collection->count = 0;
    collection->length = initialTokensCollectionLength;

    char* wordBuffer = (char*)safeMalloc(sizeof(char) * MAX_WORD_BUFFER_LENGTH);
    size_t wordBufferIdx = 0;

    for (size_t i = 0; i < data->length; i++) {
        char c = data->text[i];
        if (delimeterTable[(uint8_t)c]) {
            if (wordBufferIdx > 0) {
                String* wordStr;
                wordStr = cstring_create(wordStr, wordBuffer);

                push(collection, createToken(wordStr));
            }

            // add the delimeter
            String* delimStr;
            delimStr = cstring_charToString(delimStr, c);
            push(collection, createToken(delimStr));

            // reset 
            wordBufferIdx = 0;
            wordBuffer[0] = '\0';
        } else if (i + 1 == data->length) {
            String* wordStr;
            wordStr = cstring_create(wordStr, wordBuffer);

            push(collection, createToken(wordStr));

            wordBufferIdx = 0;
            wordBuffer[0] = '\0';
        } else {
            wordBuffer[wordBufferIdx] = c;
            wordBufferIdx++;
            wordBuffer[wordBufferIdx] = '\0';
        }
    }

    safeFree(wordBuffer);

    return collection;
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