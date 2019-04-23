#include <stdio.h>
#include "dcl.h"

//extern Stack *STACK;

int main(void) {
    //char declaration[] = "char (*(*x[3])())[5]";
    char declaration[] = "char **a";

    char **tokens = tokenize(declaration);
    STACK = create_stack();
    push(STACK, *tokens);

    //char a[] = "**c";
    int token_length = string_length(*(tokens + 1));
    parse_declarator(*(tokens+1), token_length);

    char *item;
    while ((item = pop(STACK)) != NULL) {
        printf("%s ", item);
    }
    printf("\n");

    return 0;
}
