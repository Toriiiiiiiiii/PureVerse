#include "include/lexer.h"
#include "include/token.h"
#include <string.h>

static const char *pvlex_keywordStart = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char *pvlex_keywordBody  = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static const char *pvlex_numberStart  = "0123456789";
static const char *pvlex_numberBody   = "0123456789.";
static const char *pvlex_binaryOps    = "+-*/%<>=!";
static const char *pvlex_whitespace   = " \t\n";


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

bool pvlex_charInString(const char *str, char c) {
  int stringLength = strlen(str);

  for(int i = 0; i < stringLength; ++i) {
    if(str[i] == c) return true;
  }

  return false;
}

pv_token_t pvlex_buildKeyword(pv_lexer_t *lexer) {
  pv_token_t result = {
    .line  = lexer->line,
    .col   = lexer->col,
    .type  = TOKEN_KEYWORD,
    .value = ""
  };

  char buffer[2] = {' ', '\0'}; 
  char current = pvlex_getCurrentChar(lexer);

  while( !pvlex_analysisComplete(lexer) && pvlex_charInString(pvlex_keywordBody, current) ) {
    pvlex_getCurrentCharAndAdvance(lexer);  

    buffer[0] = current;
    strncat(result.value, buffer, 1);

    //printf("%d %c %s\n", result.type, current, result.value);
    current = pvlex_getCurrentChar(lexer);
  }

  return result;
}

pv_token_t pvlex_buildNumber(pv_lexer_t *lexer) {
  pv_token_t result = {
    .line  = lexer->line,
    .col   = lexer->col,
    .type  = TOKEN_NUMBERLITERAL,
    .value = ""
  };

  char buffer[2] = {' ', '\0'}; 
  char current = pvlex_getCurrentChar(lexer);

  while( !pvlex_analysisComplete(lexer) && pvlex_charInString(pvlex_numberBody, current) ) {
    pvlex_getCurrentCharAndAdvance(lexer);  

    buffer[0] = current;
    strncat(result.value, buffer, 1);

    //printf("%d %c %s\n", result.type, current, result.value);
    current = pvlex_getCurrentChar(lexer);
  }

  return result;
}

pv_token_t pvlex_buildBinaryOp(pv_lexer_t *lexer) {
  pv_token_t result = {
    .line  = lexer->line,
    .col   = lexer->col,
    .type  = TOKEN_BINARYOPERATOR,
    .value = ""
  };

  char buffer[2] = {' ', '\0'}; 
  char current = pvlex_getCurrentChar(lexer);

  while( !pvlex_analysisComplete(lexer) && pvlex_charInString(pvlex_binaryOps, current) ) {
    pvlex_getCurrentCharAndAdvance(lexer);  

    buffer[0] = current;
    strncat(result.value, buffer, 1);

    //printf("%d %c %s\n", result.type, current, result.value);
    current = pvlex_getCurrentChar(lexer);
  }

  return result;
}

pv_tokenlist_t tokenizeString(pv_lexer_t *lexer) {
  pv_tokenlist_t result = createTokenList();

  while(!pvlex_analysisComplete(lexer)) {
    char current = pvlex_getCurrentChar(lexer);

    if(pvlex_charInString(pvlex_whitespace, current)) {
      pvlex_getCurrentCharAndAdvance(lexer);
      continue;
    }

    if(pvlex_charInString(pvlex_keywordStart, current)) {
      appendToTokenList(&result, pvlex_buildKeyword(lexer));
    } else if(pvlex_charInString(pvlex_numberStart, current)) {
      appendToTokenList(&result, pvlex_buildNumber(lexer));
    } else if(pvlex_charInString(pvlex_binaryOps, current)) {
      appendToTokenList(&result, pvlex_buildBinaryOp(lexer));
    }
  }

  return result;
}
