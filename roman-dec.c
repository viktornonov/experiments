#include <stdio.h>
//reference http://literacy.kent.edu/Minigrants/Cinci/romanchart.htm

int ROMAN_NUMBERS_COUNT = 7;
int ROMAN_NUMBERS[] = {
    1000, //'M'
    100, //'C'
    5, //'V'
    1, //'I'
    10, //'X'
    500, //'D'
    50 //L
};

//stupid hash function used to hash the roman numbers using their ascii code
//uses N instead of C, so we get load factor == 1
//I = 73 hashed 3
//V = 86 hashed 2
//X = 88 hashed 4
//L = 76 hashed 6
//C = 67 check N
//D = 68 hashed 5
//M = 77 hashed 0
//N = 78 hashed 1
int hash_char(char roman_number) {
    if(roman_number == 'C') {
        return (int)'N' % ROMAN_NUMBERS_COUNT;
    }
    else {
        return (int)roman_number % ROMAN_NUMBERS_COUNT;
    }
}

int convert_roman_to_decimal(char *roman, int chars_count) {
    int i;
    int result = 0;
    int prev = 0;
    int roman_as_value;
    int index;
    for(i = 0; i < chars_count; i++) {
        index = hash_char(roman[i]);
        roman_as_value = ROMAN_NUMBERS[index];
        if (prev != 0 && prev < roman_as_value) {
            result -= 2 * prev;
        }
        result += roman_as_value;
        prev = roman_as_value;
    }
    return result;
}

int main()
{
    char *roman = "MDCLXXIV";
    int decimal = convert_roman_to_decimal(roman, 7);
    printf("%s = %d\n", roman, decimal);
}
