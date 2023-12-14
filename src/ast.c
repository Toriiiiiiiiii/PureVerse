#include "include/ast.h"

void printIndent(int amount) {
  for(int i = 0; i < amount; ++i) {
    printf("  ");
  }
}

void printNodeIndented(pv_astnode_t node, int indent) {
  printIndent(indent);
  printf("{\n");

  printIndent(indent + 1);
  printf("'line': %d,\n", node.line);

  printIndent(indent + 1);
  printf("'col': %d,\n", node.col);

  printIndent(indent + 1);
  printf("'type': %d,\n", node.type);

  printIndent(indent + 1);
  printf("'value': '%s',\n", node.value);

  printIndent(indent + 1);
  printf("'children': [\n");

  for(int index = 0; index < node.children.size; ++index) {
    printNodeIndented(getNodeListIndex(&node.children, index), indent + 2);

    if(index < node.children.size - 1) printf(",\n");
    else printf("\n");
  } 

  printIndent(indent + 1);
  printf("]\n");

  printIndent(indent);
  printf("}");
}

void printASTNode(pv_astnode_t node) {
  printNodeIndented(node, 0);
  printf("\n");
}

pv_astnodelist_t createNodeList() {
  pv_astnodelist_t result = {
    .capacity = 10,
    .size = 0,
    .head = (pv_astnode_t *)malloc(10 * sizeof(pv_astnode_t))
  };

  return result;
}

void destroyNodeList(pv_astnodelist_t *list) {
  list->capacity = 0;
  free(list->head);
}

void __reallocateNodeList(pv_astnodelist_t *list, int newsize) {
  list->head = realloc(list->head, newsize * sizeof(pv_astnode_t));
  list->capacity = newsize;
}

void appendNodeList(pv_astnodelist_t *list, pv_astnode_t node) {
  if(list->size >= list->capacity / 2) __reallocateNodeList(list, list->capacity * 2);

  list->head[list->size] = node;
  list->size++;
}

pv_astnode_t popNodeList(pv_astnodelist_t *list) {
  if(list->size < list->capacity / 2) __reallocateNodeList(list, list->capacity / 2);

  list->size--;
  return list->head[list->size];
}

void setNodeListIndex(pv_astnodelist_t *list, int index, pv_astnode_t node) {
  if(index >= list->size) return;

  list->head[index] = node;
}

pv_astnode_t getNodeListIndex(pv_astnodelist_t *list, int index) {
  if(index >= list->size) return (pv_astnode_t){0};

  return list->head[index];
}
