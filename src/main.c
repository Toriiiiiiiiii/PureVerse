#include <stdio.h>
#include "include/lexer.h"
#include "include/token.h"

int main() {
  pv_lexer_t lexer = createLexer((char *)"Hello World"); 
  pv_tokenlist_t tokenList = tokenizeString(&lexer);

  destroyTokenList(&tokenList);
  return 0;
}
