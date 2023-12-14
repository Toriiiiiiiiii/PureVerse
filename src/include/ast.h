#ifndef PV_INCLUDE_AST_H
#define PV_INCLUDE_AST_H

#include "token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

enum _pv_astnode_type_t {
  AST_PROGRAM,
  AST_NUMBERLIT,
  AST_FNDEF,
  AST_FUNCTION,
  AST_BLOCK_CURLY,
  AST_BLOCK_PAREN,
};

typedef enum _pv_astnode_type_t pv_astnode_type_t;

struct _pv_astnode_t;
struct _pv_astnodelist_t {
  int capacity, size;
  struct _pv_astnode_t *head;
};

typedef struct _pv_astnodelist_t pv_astnodelist_t;

struct _pv_astnode_t {
  int line, col;
  pv_astnode_type_t type;

  pv_astnodelist_t children;
  char value[512];
};

typedef struct _pv_astnode_t pv_astnode_t;

void printASTNode(pv_astnode_t nodes);

pv_astnodelist_t createNodeList();
void destroyNodeList(pv_astnodelist_t *list);

void appendNodeList(pv_astnodelist_t *list, pv_astnode_t node);
pv_astnode_t popNodeList(pv_astnodelist_t *list);

void setNodeListIndex(pv_astnodelist_t *list, int index, pv_astnode_t node);
pv_astnode_t getNodeListIndex(pv_astnodelist_t *list, int index);

#endif // PV_INCLUDE_AST_H
