#ifndef DCL_H
#define DCL_H
#include "mystring.h"
#include "stack.h"

extern Stack *STACK;

char **tokenize(char *);

void parse_declarator(char *token, int n);

void parse_direct_declarator(char *token, int size);

#endif /* DCL_H */
