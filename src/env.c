#include "include/env.h"

pv_runtimestack_t createRuntimeStack() {
  return (pv_runtimestack_t) {
    .capacity = 10,
    .size = 0,
    .head = (pv_runtimevalue_t *)malloc(10 * sizeof(pv_runtimevalue_t))
  };
}

void __runtimeRealloc(pv_runtimestack_t *stack, int newSize) {
  stack->capacity = newSize;
  stack->head = (pv_runtimevalue_t *)realloc(stack->head, newSize * sizeof(pv_runtimevalue_t));
}

void runtimePush(pv_runtimestack_t *stack, pv_runtimevalue_t value) {
  if(stack->size > stack->capacity / 2) __runtimeRealloc(stack, stack->capacity * 2);

  stack->head[stack->size] = value;
  stack->size++;
}

pv_runtimevalue_t runtimePop(pv_runtimestack_t *stack) {
  if(stack->size <= stack->capacity / 2) __runtimeRealloc(stack, stack->capacity / 2);

  stack->size--;
  return stack->head[stack->size];
}
