#include "power-of-two-lib.h"
// the function is implemented based on the property:
// 2^power = '1' + power*'0'
// 2^1 = 10
// 2^2 = 100
// 2^3 = 1000
// O(power)
char* power_of_two_binary(unsigned int power) {
    char *a;
    a = (char *)malloc(sizeof(char)*power + 1 + 1);
    a[0] = '1';
    int i;
    for(i = 1; i <= power; i++) {
        a[i] = '0';
    }
    a[i] = '\0';
    return a;
}

//how many 1s are in the number's binary form
//O(number)
int get_ones_count(unsigned int number) {
    int number_size_in_bits = sizeof(number) * 8; //32 bits
    int i = 0;
    int count = 0;
    for (i = 0; i < number_size_in_bits; i++) {
        if (number & 1) {
            count += 1;
        }
        number = number >> 1;
    }
    return count;
}

// if there's only one 1 in the number's binary form then it's a power of 2
// O(n)
bool is_power_of_two(unsigned int number) {
    return (1 == get_ones_count(number)) ? TRUE : FALSE;
}

//get which power of 2 is the number
//AKA lg number
int get_power_of_two(unsigned int number) {
    int power = 0;
    while((number & 1) == 0) {
        power += 1;
        number = number >> 1;
    }
    return power;
}

