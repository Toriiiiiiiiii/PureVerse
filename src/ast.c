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
