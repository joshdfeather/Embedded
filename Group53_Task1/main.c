#include "F28x_Project.h" // Includes necessary device headers and libraries
#include <stdio.h>
#include <stdint.h>

int main() {

    // Multiply two 16-bit signed integers
    int16_t signed_a = 16384;
    int16_t signed_b = -16384;
    int64_t signed_result = (int64_t)signed_a * (int64_t)signed_b;
    printf("Multiplication of int: 16384 * -16384 = %lld\n", signed_result);

    // Multiply two 16-bit unsigned integers
    uint16_t unsigned_a = 16384;
    uint16_t unsigned_b = 16384;
    uint64_t unsigned_result = (uint64_t)unsigned_a * (uint64_t)unsigned_b;
    printf("Multiplication of unsigned int: 16384 * 16384 =: %llu\n", unsigned_result);

    // Multiply two 32-bit floating-point numbers
    float float_a = 0.5f;
    float float_b = 0.5f;
    float float_result = float_a * float_b;
    printf("Multiplication of float: 0.5 * 0.5 = %g\n", float_result);

    return 0;
}

