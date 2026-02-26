#include <stdio.h>
#include <stdlib.h>
#include "rcadder.h"

void rippleCarryAdd(BitResult* results, unsigned int width, unsigned int a, unsigned int b);
void rippleCarrySubtract(BitResult* results, unsigned int width, unsigned int a, unsigned int b);
void rippleMultiply(BitResult* results, unsigned int width, unsigned int a, unsigned int b);

int main(int argc, char** argv) {
    if (argc !=4) {
        printf("This program expects 3 arguments: a width, and a pair of numbers to sum.\n");
        return 0;
    }

    // Just using atoi for simplicity
    unsigned int width = atoi(argv[1]);
    unsigned int a = strtoul(argv[2], NULL, 0);
    unsigned int b = strtoul(argv[3], NULL, 0);

    // Add the two numbers and get an array of BitResult back.
    BitResult add_results[width] = {};

    rippleCarryAdd(add_results, width, a, b);

    // There is an overflow if the carry in to the MSB does not equal the carry out
    // (meaning that negative numbers should stay negative, and
    //  positive numbers should not turn negative)
    if (add_results[0].carry != add_results[1].carry) {
        printf("OF ");
    }
    // Print out the result
    for (int i = 0; i < width; ++i) {
        printf("%u", add_results[i].sum);
    }
    printf("\n");

    // Subtract the two numbers and get an array of BitResult back.
    BitResult sub_results[width] = {};

    rippleCarrySubtract(sub_results, width, a, b);

    // There is an overflow if the carry in to the MSB does not equal the carry out
    // (meaning that negative numbers should stay negative, and
    //  positive numbers should not turn negative)
    if (sub_results[0].carry != sub_results[1].carry) {
        printf("OF ");
    }
    // Print out the result
    for (int i = 0; i < width; ++i) {
        printf("%u", sub_results[i].sum);
    }
    printf("\n");

    // Multiply the two numbers and get an array of BitResult back.
    BitResult mult_results[width] = {};

    rippleMultiply(mult_results, width, a, b);

    // Print out the product
    for (int i = 0; i < width; ++i) {
        printf("%u", mult_results[i].sum);
    }
    printf("\n");

    return 0;
}
