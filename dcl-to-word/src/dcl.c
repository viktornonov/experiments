/* Example
 * char *c
 *   c: pointer to char
 * char **argv
 *   argv: pointer to pointer to char
 * int (*daytab)[13]
 *   daytab: pointer to array[13] of int
 * int *daytab[13]
 *   daytab: array[13] of pointer to int
 * void *comp()
 *   comp: function returning pointer to void
 * void (*comp)()
 *   comp: pointer to function returing void
 * char (*(*x())[])()
 *   x: function returning pointer to array[] of pointer to function returning char
 * char (*(*x[3])())[5]
 *   x: array[3] of pointer to function returning pointer to array[5] of char
 * void func(void (*callback)(void *))
 *  func: function returning void accepting argument pointer to function returning void accepting argument pointer to void
 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "dcl.h"

#define MAX_TOKENS 5
#define MAX_SYMBOLS_PER_TOKEN 20

Stack *STACK;

char **tokenize(char *string) {
  char **tokens = (char **)malloc(MAX_TOKENS * sizeof(char *));
  int token_array_idx = 0;
  char *current_char = string;
  char *token  = (char *)malloc(MAX_SYMBOLS_PER_TOKEN * sizeof(char));
  int token_idx = 0;
  int in_expression = 0;
  while (*current_char != '\0') {
    if (*current_char == ' ' || *current_char == '\t' || *current_char == '\n') {
      token[token_idx] = '\0';
      *(tokens+token_array_idx) = (char *)malloc(sizeof(char) * (token_idx+1));
      **(tokens+token_array_idx) = '\0';
      string_copy(*(tokens+token_array_idx), token);
      token_array_idx++;
      token_idx = 0;
    }
    else {
      token[token_idx++] = *current_char;
    }
    current_char++;
  }
  token[token_idx] = '\0';
  *(tokens+token_array_idx) = (char *)malloc(sizeof(char) * (token_idx+1));
  **(tokens+token_array_idx) = '\0';
  string_copy(*(tokens + token_array_idx), token);

  return tokens;
}

/*
Process declarator as defined in K&R book:
declarator:
  pointer_opt direct-declarator

pointer:
  *type-qualifier-list_opt
  *type-qualifier-list_opt pointer

type-qualifier-list:
  type-qualifier
  type-qualifier-list type-qualifier
 */
void parse_declarator(char *token, int n) {
  //printf("token = %s\n", token);
  int k = 0;
  while (token[k] == '*') {
    push(STACK, "pointer to");
    for (int i = k + 1; i < n; i++) {
      token[i - 1] = token[i];
    }
    token[n - 1] = '\0';
    n = n - 1;
  }

  //printf("token = %s\n", token);
  parse_direct_declarator(token, n);
}

/*
Process direct-declarator as defined in K&R book:
direct-declarator:
  identifier
  (declarator)
  direct-declarator[constant-expression_opt]
  direct-declarator(parameter-type-list)
 */
void parse_direct_declarator(char *token, int size) {
  //printf("parsing %s, size - %d\n", token, size);
  if (size >= 2 && token[size-2] == '(' && token[size-1] == ')') {
    //printf("looks like function\n");
    push(STACK, "function returning");
    token[size - 2] = '\0';
    parse_direct_declarator(token, size - 2);
  }
  else if (token[size - 1] == ']') {
    //printf("looks like array\n");
    int i = size - 1;
    while(token[i] != '[') {
      i--;
    }
    char *array_size_string = (char *)malloc(sizeof(char)*20);
    *array_size_string = '\0';
    string_copy(array_size_string, "array");
    int array_size_str_index = string_length("array"); //start after array
    for(int j = i; j < size; j++) {
      array_size_string[array_size_str_index++] = token[j];
    }
    array_size_string[array_size_str_index++] = ' ';
    array_size_string[array_size_str_index++] = 'o';
    array_size_string[array_size_str_index++] = 'f';
    array_size_string[array_size_str_index] = '\0';
    push(STACK, array_size_string);

    token[i] = '\0';
    parse_direct_declarator(token, i);
  }
  else if (token[0] == '(' && token[size - 1] == ')') {
    //printf("looks like (declarator)\n");
    for(int i = 1; i < size-1; i++) { //remove the wrapping (...)
      token[i - 1] = token[i];
    }
    token[size - 2] = '\0';
    parse_declarator(token, size - 2);
  }
  else {
    //printf("looks like identifier\n");
    push(STACK, token);
  }
}
