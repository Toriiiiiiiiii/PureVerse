#ifndef PV_INCLUDE_LEXER_H
#define PV_INCLUDE_LEXER_H

#include "token.h"

#include <stdbool.h>
#include <string.h>

struct _pv_lexer_t {
  int line, col;
  int characterIndex;

  char *source;

  enum {
    LEXER_OK,
    LEXER_ERROR
  } status;
};

typedef struct _pv_lexer_t pv_lexer_t;

pv_lexer_t createLexer(char *source);

char pvlex_getCurrentChar(pv_lexer_t *lexer);
char pvlex_getCurrentCharAndAdvance(pv_lexer_t *lexer);
bool pvlex_analysisComplete(pv_lexer_t *lexer);

pv_tokenlist_t tokenizeString(pv_lexer_t *lexer);

#endif // PV_INCLUDE_LEXER_H
