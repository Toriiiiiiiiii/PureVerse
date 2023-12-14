#include "include/lexer.h"
#include "include/token.h"
#include <string.h>

pv_lexer_t createLexer(char *source) {
  pv_lexer_t result = {0};

  result.line = result.col = 1;
  result.characterIndex = 0;

  result.source = source;
  result.status = LEXER_OK;

  return result;
}

char pvlex_getCurrentChar(pv_lexer_t *lexer) {
  return lexer->source[lexer->characterIndex];
}

char pvlex_getCurrentCharAndAdvance(pv_lexer_t *lexer) {
  char result = lexer->source[lexer->characterIndex];

  lexer->characterIndex++;
  lexer->col++;

  if(result == '\n') {
    lexer->line++;
    lexer->col = 1;
  }

  return result;
}

bool pvlex_analysisComplete(pv_lexer_t *lexer) {
  return (lexer->characterIndex == strlen((const char *)lexer->source));
}

pv_tokenlist_t tokenizeString(pv_lexer_t *lexer) {
  pv_tokenlist_t result = createTokenList();

  while(!pvlex_analysisComplete(lexer)) {
    char current = pvlex_getCurrentChar(lexer);

    printf("%c\n", current);
    pvlex_getCurrentCharAndAdvance(lexer);
  }

  return result;
}
