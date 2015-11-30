#include <stdio.h>
#include "power-of-two-lib.h"

//implents multipling, dividing and modulo for numbers power of 2
int main() {
    unsigned int operator1;
    unsigned int operator2;

    printf("op1=");
    scanf("%u", &operator1);
    printf("op2=");
    scanf("%u", &operator2);

    if (!is_power_of_two(operator2)) {
        printf("op2=%u is not power of 2\n", operator2);
        return -1;
    }

    printf("multiplying\n");
    printf("op1 * op2 = %u\n", operator1 << get_power_of_two(operator2));

    printf("dividing\n");
    printf("op1 / op2 = %u\n", operator1 >> get_power_of_two(operator2));

    printf("modulo\n");
    printf("op1 %% op2 = %u\n", operator1 & (operator2 - 1));

    printf("binary value of number 2^%u in binary is %s\n", operator2, power_of_two_binary(operator2));

    return 0;
}
