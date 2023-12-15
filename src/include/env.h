#ifndef PV_INCLUDE_ENV_H
#define PV_INCLUDE_ENV_H

#include <stdio.h>
#include <stdlib.h>

enum _pv_runtimevaluetype_t {
  VALUE_NUMBER,
  VALUE_STRING,
  VALUE_FUNCTION,
};

typedef enum _pv_runtimevaluetype_t pv_runtimevaluetype_t;

struct _pv_runtimevalue_t {
  pv_runtimevaluetype_t type;

  union {
    char *str;
    float num;
  } value;
};

typedef struct _pv_runtimevalue_t pv_runtimevalue_t;

struct _pv_runtimestack_t {
  int size, capacity;
  pv_runtimevalue_t *head;
};

typedef struct _pv_runtimestack_t pv_runtimestack_t;

pv_runtimestack_t createRuntimeStack();

void runtimePush(pv_runtimestack_t *stack, pv_runtimevalue_t value);
pv_runtimevalue_t runtimePop(pv_runtimestack_t *stack);

#endif // PV_INCLUDE_ENV_H
