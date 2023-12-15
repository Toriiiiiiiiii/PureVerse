#include "include/parser.h"
#include "include/ast.h"
#include "include/token.h"
#include <string.h>

pv_parser_t createParser(pv_tokenlist_t tokens) {
  return (pv_parser_t) {
    .tokens = tokens,
    .tokenIndex = 0
  };
}

pv_token_t pvparse_getCurrentToken(pv_parser_t *parser) {
  return getTokenListIndex(&parser->tokens, parser->tokenIndex);
}

pv_token_t pvparse_getCurrentTokenAndAdvance(pv_parser_t *parser) {
  pv_token_t result = getTokenListIndex(&parser->tokens, parser->tokenIndex);
  parser->tokenIndex++;

  return result;
}

bool pvparse_parseComplete(pv_parser_t *parser) {
  return (parser->tokenIndex >= parser->tokens.size);
}

pv_astnode_t parseNode(pv_parser_t *parser) {
  pv_astnode_t result = {0};
  result.children = createNodeList();

  pv_token_t token = pvparse_getCurrentTokenAndAdvance(parser);

  result.line = token.line;
  result.col = token.col;

  if(token.type == TOKEN_NUMBERLITERAL) {
    result.type = AST_NUMBERLIT;
    strncpy(result.value, token.value, 512);
  }
  else if(token.type == TOKEN_KEYWORD) {
    pv_token_t next = pvparse_getCurrentToken(parser);
    strncpy(result.value, token.value, 512);

    if(next.type == TOKEN_BINARYOPERATOR && strcmp(next.value, "=>") == 0) {
      // ASSIGNMENT
      pvparse_getCurrentTokenAndAdvance(parser);
      next = pvparse_getCurrentToken(parser);

      if(next.type == TOKEN_LPAREN) {
        // FUNCTION DEFINITION
        result.type = AST_FNDEF;

        pv_astnode_t paramNode = parseNode(parser);
        pv_astnode_t codeNode = parseNode(parser);
        
        appendNodeList(&result.children, paramNode);
        appendNodeList(&result.children, codeNode);
      } else if(next.type == TOKEN_LCURLY) {
        // VARIABLE ASSIGNMENT
        result.type = AST_VARASSIGN;

        pv_astnode_t codeNode = parseNode(parser);
        appendNodeList(&result.children, codeNode);
      }
    } else {
      result.type = AST_IDENTIFIER;
    }
  }
  else if(token.type == TOKEN_LPAREN) {
    result.type = AST_BLOCK_PAREN;
    pv_token_t next = pvparse_getCurrentToken(parser);

    while(!pvparse_parseComplete(parser) && next.type != TOKEN_RPAREN) {
      appendNodeList(&result.children, parseNode(parser));
      next = pvparse_getCurrentToken(parser);
    }

    pvparse_getCurrentTokenAndAdvance(parser);
  }
  else if(token.type == TOKEN_LCURLY) {
    result.type = AST_BLOCK_CURLY;
    pv_token_t next = pvparse_getCurrentToken(parser);

    while(!pvparse_parseComplete(parser) && next.type != TOKEN_RCURLY) {
      appendNodeList(&result.children, parseNode(parser));
      next = pvparse_getCurrentToken(parser);
    }

    pvparse_getCurrentTokenAndAdvance(parser);
  }
  else if(token.type == TOKEN_BINARYOPERATOR) {
    if( strcmp(token.value, "/*") == 0 ) {
      // COMMENT
      pv_token_t next = pvparse_getCurrentTokenAndAdvance(parser);

      while( strcmp(next.value, "*/") != 0 ) {
        next = pvparse_getCurrentTokenAndAdvance(parser);
      }

      //pvparse_getCurrentTokenAndAdvance(parser);
      return parseNode(parser);
    }

    result.type = AST_BINARY_OP;
    strncpy(result.value, token.value, 512);
  }

  return result;
}

pv_astnode_t parseTokens(pv_parser_t *parser) {
  pv_astnode_t result = {
    .line = 1,
    .col = 1,
    .type = AST_PROGRAM,
    .value = "",
    .children = createNodeList()
  };

  while(!pvparse_parseComplete(parser)) {
    appendNodeList(&result.children, parseNode(parser));
  }

  return result;
}
