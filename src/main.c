#include <stdio.h>
#include "include/lexer.h"
#include "include/token.h"

int main() {
  pv_lexer_t lexer = createLexer((char *)"Hello World 123"); 
  pv_tokenlist_t tokenList = tokenizeString(&lexer);

  for(int i = 0; i < tokenList.size; ++i) {
    printTokenInformation(getTokenListIndex(&tokenList, i));
    //printf("%s\n", getTokenListIndex(&tokenList, i).value);
  }

  printf("%d\n", TOKEN_KEYWORD);
  destroyTokenList(&tokenList);
  return 0;
}
