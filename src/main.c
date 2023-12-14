#include <stdio.h>
#include <stdlib.h>

#include "include/lexer.h"
#include "include/token.h"

char *readFileContents(char *path) {
  FILE *file = fopen(path, "r");

  if(file == NULL) return NULL;

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = (char *)malloc(size + 1);
  fread(buffer, 1, size, file);

  buffer[size] = '\0';
  return buffer;
}

int main(int argc, char **argv) {
  if(argc < 2) {
    printf("Usage : %s <path>\n", argv[0]);
    return 1;
  }

  char *fileContents = readFileContents(argv[1]);

  if(fileContents == NULL) {
    printf("Usage : %s <path>\n", argv[0]);
    return 1;
  }

  pv_lexer_t lexer = createLexer(fileContents); 
  pv_tokenlist_t tokenList = tokenizeString(&lexer);

  for(int i = 0; i < tokenList.size; ++i) {
    printTokenInformation(getTokenListIndex(&tokenList, i));
  }

  destroyTokenList(&tokenList);
  return 0;
}
