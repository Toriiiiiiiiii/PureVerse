#ifndef PV_INCLUDE_TOKEN_H
#define PV_INCLUDE_TOKEN_H

#include <stdio.h>

enum _pv_tokentype_t {
  TOKEN_KEYWORD,
  TOKEN_NUMBERLITERAL,
  TOKEN_BINARYOPERATOR,
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_LCURLY,
  TOKEN_RCURLY,
};

typedef enum _pv_tokentype_t pv_tokentype_t;

struct _pv_token_t {
  int line, col;
  pv_tokentype_t type;

  char value[512];
};

typedef struct _pv_token_t pv_token_t;

static inline void printTokenInformation(pv_token_t token) {
  printf("Token{%d:%d, %d, %s}\n", token.line, token.col, token.type, token.value);
}

struct _pv_tokenlist_t {
  pv_token_t *head;

  int size, capacity;
};

typedef struct _pv_tokenlist_t pv_tokenlist_t;

pv_tokenlist_t createTokenList();
void destroyTokenList(pv_tokenlist_t *tokenList);

void appendToTokenList(pv_tokenlist_t *tokenList, pv_token_t tok);
pv_token_t popFromTokenList(pv_tokenlist_t *tokenList);

void setTokenListIndex(pv_tokenlist_t *tokenList, int index, pv_token_t tok);
pv_token_t getTokenListIndex(pv_tokenlist_t *tokenList, int index);

#endif // PV_INCLUDE_TOKEN_H
