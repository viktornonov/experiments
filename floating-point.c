#include <stdio.h>
#include <stdlib.h>

short find_sign(float);
short* find_exponent(float);
short* find_mantissa(unsigned long, int);
short* find_mantissa_through_float(float);

int main()
{
    float number = -0.75;

    short sign = find_sign(number);

    short* exponent;
    exponent = (short *)malloc(8*sizeof(short));
//    exponent = find_exponent(number);

    short* mantissa;
    mantissa = (short *)malloc(23*sizeof(short));
    mantissa = find_mantissa(135703125ul, 9);
    int i;
    printf("mantissa = ");
    for(i = 0; i < 23; i++) {
        printf("%d", mantissa[i]);
    }
    printf("\n");

    short* mantissa_float;
    mantissa_float = (short *)malloc(23*sizeof(short));
    mantissa_float = find_mantissa_through_float(1.35703125);
    printf("mantissa (calculated through float) = ");
    for(i = 0; i < 23; i++) {
        printf("%d", mantissa_float[i]);
    }
    printf("\n");

    short result[32]; //32-bit float
    free(exponent);
    free(mantissa);
    return 0;
}


short find_sign(float number)
{
    if (number < 0) {
        return 1;
    }
    else {
        return 0;
    }
}

short* find_exponent(float number)
{
    int power = 0;
    float res = number;
    short* exponent;
    exponent = (short *)malloc(8*sizeof(short));
    if (number < 1.0) {
    }
    else { //>= 1
        while(res > 1.0) {
            res /= 2.0;
            power += 1;
        }
    }

    //res == 1.xxxxx

    short biased_exponent = 127 + power;
    //convert to biased exponent to binary
    return exponent;
}

short* find_mantissa(unsigned long number_in_scientific, int count_digits)
{
    unsigned long one = 1ul;
    int i;
    for(i = 0; i < count_digits-1; i++) {
        one *= 10;
    }

    if (number_in_scientific > one) {
        number_in_scientific -= one;
    }

    short *mantissa;
    mantissa = (short *)malloc(23*sizeof(short));
    short mantissa_index = 0;

    unsigned long results[23];
    int res_index = 0;

    unsigned long res = number_in_scientific;
    short result_repeating = 0;
    int result_repeat_start = 0;
    while(mantissa_index <= 23 && res != 0 && result_repeating == 0) {
        res *= 2;
        if (res >= one) {
            mantissa[mantissa_index] = 1;
        }
        else { //< one
            mantissa[mantissa_index] = 0;
        }
        mantissa_index++;

        if (res >= one) {
            res -= one;
        }

        if (res > 10) {
            res /= 10;
            one /= 10;
        }

//      printf("%lu, ", one);
//      printf("%lu", res);
//      printf("\n");

        for(i = 0; i < res_index; i++) {
            if (results[i] == res) {
                result_repeat_start = i + 1;
                result_repeating = 1;
                break;
            }
        }
        if (result_repeating == 0) {
            results[res_index] = res;
            res_index++;
        }
    }
//    printf("%d ", mantissa_index);
//    printf("%d", result_repeat_start);

    if (res != 0 && result_repeating == 1) {
        for(i = result_repeat_start; i <= 23; i++) {
            mantissa[mantissa_index] = mantissa[i];
            mantissa_index++;
        }
    }

    if (res == 0 && result_repeating == 0) {
        for(i = mantissa_index; i < 23; i++) {
            mantissa[i] = 0;
        }
    }

    return mantissa;
}

short* find_mantissa_through_float(float number_in_scientific)
{
    float results[23];
    int results_index = 0;
    short *mantissa;
    mantissa = (short *)malloc(23*sizeof(short));
    short mantissa_index = 0;
    int i = 0;

    if (number_in_scientific >= 1.0) {
        number_in_scientific--;
    }

    float res = number_in_scientific;
    short result_repeating = 0;
    int result_repeat_start = 0;
    while (mantissa_index <= 23 && res != 0 && result_repeating == 0) {
        res *= 2;
        if (res >= 1) {
            mantissa[mantissa_index] = 1;
        }
        else { //< 1
            mantissa[mantissa_index] = 0;
        }
        mantissa_index++;

        if (res >= 1) {
            res--;
        }

        for(i = 0; i < results_index; i++) {
            if (results[i] == res) {
                result_repeat_start = i;
                result_repeating = 1;
                break;
            }
        }
        if (result_repeating == 0) {
            results[results_index] = res;
            results_index++;
        }
    }

    if (res != 0 && result_repeating == 1) {
        for(i = result_repeat_start; i < 23; i++) {
            mantissa[mantissa_index] = mantissa[i];
            mantissa_index++;
        }
    }

    if (res == 0 && result_repeating == 0) {
        for(i = mantissa_index; i < 23; i++) {
            mantissa[i] = 0;
        }
    }

    return mantissa;
}
