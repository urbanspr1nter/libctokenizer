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

void ctok_free(struct TokenCollection* collection) {
    for (size_t i = 0; i < collection->count; i++) {
        cstring_free(collection->tokens[i]->value);
        safeFree(collection->tokens[i]);
    }
    safeFree(collection->tokens);
    safeFree(collection);
}