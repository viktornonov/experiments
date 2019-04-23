#include "stack.h"
#include <stdlib.h>

Stack *create_stack() {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->items = (char **)malloc(50*sizeof(char *));
  stack->current_position = 0;
  return stack;
}

void push(Stack *stack, char *token) {
  *(stack->items + stack->current_position) = (char *)malloc(sizeof(char) * 30);
  **(stack->items + stack->current_position) = '\0';
  string_copy(*(stack->items + stack->current_position), token);
  stack->current_position++;
}

char *pop(Stack *stack) {
  if (stack->current_position == 0) {
    return NULL;
  }
  stack->current_position--;
  char* item = *(stack->items + stack->current_position);

  return item;
}

