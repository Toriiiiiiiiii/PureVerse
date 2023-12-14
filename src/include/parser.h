#ifndef PV_INCLUDE_PARSER_H
#define PV_INCLUDE_PARSER_H

#include "ast.h"
#include "token.h"

#include <stdbool.h>

struct _pv_parser_t {
  pv_tokenlist_t tokens;

  int tokenIndex;
};

typedef struct _pv_parser_t pv_parser_t;

pv_parser_t createParser(pv_tokenlist_t tokens);
pv_astnodelist_t parseTokens(pv_parser_t *parser);

pv_token_t pvparse_getCurrentToken(pv_parser_t *parser);
pv_token_t pvparse_getCurrentTokenAndAdvance(pv_parser_t *parser);
bool pvparse_parseComplete(pv_parser_t *parser);

#endif // PV_INCLUDE_PARSER_H
