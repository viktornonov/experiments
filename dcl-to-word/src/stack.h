#ifndef STACK_H
#define STACK_H
#include "mystring.h"
#include <stdlib.h>

struct Stack {
  char **items;
  int current_position;
  int size;
};

typedef struct Stack Stack;

struct Stack *create_stack();

void push(Stack *stack, char *token);

char *pop(Stack *stack);

#endif
