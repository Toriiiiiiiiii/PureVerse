#include "include/token.h"
#include <stdlib.h>

#define TOKENLIST_DEFAULT_CAPACITY 10

pv_tokenlist_t createTokenList() {
  pv_tokenlist_t result = {0};

  result.size = 0;

  result.head = (pv_token_t *)malloc(TOKENLIST_DEFAULT_CAPACITY * sizeof(pv_token_t));
  if(result.head != NULL) result.capacity = TOKENLIST_DEFAULT_CAPACITY;

  return result;
}

void destroyTokenList(pv_tokenlist_t *tokenList) {
  free(tokenList->head);

  tokenList->size = tokenList->capacity = 0;
}

void __reallocateTokenList(pv_tokenlist_t *tokenList, int newSize) {
  tokenList->head = (pv_token_t *)realloc(tokenList->head, newSize * sizeof(pv_token_t));
  tokenList->capacity = (tokenList->head == NULL)? 0 : newSize;
}

void appendToTokenList(pv_tokenlist_t *tokenList, pv_token_t tok) {
  if(tokenList->size >= tokenList->capacity / 2) __reallocateTokenList(tokenList, 2*tokenList->capacity);

  tokenList->head[tokenList->size] = tok;
  tokenList->size++;
}

pv_token_t popFromTokenList(pv_tokenlist_t *tokenList) {
  if(tokenList->size <= tokenList->capacity / 2) __reallocateTokenList(tokenList, tokenList->capacity/2);

  tokenList->size--;
  return tokenList->head[tokenList->size];
}

void setTokenListIndex(pv_tokenlist_t *tokenList, int index, pv_token_t tok) {
  if(index >= tokenList->size) return;

  tokenList->head[index] = tok;
}

pv_token_t getTokenListIndex(pv_tokenlist_t *tokenList, int index) {
  if(index >= tokenList->size) return (pv_token_t){0};

  return tokenList->head[index]; 
}
