/*
 * Example 4: printf Calculator
 *
 * Implements basic arithmetic operations using printf's format string:
 * - Addition: printf("%*d%*d%n", a, 0, b, 0, &result)
 * - Subtraction: printf("%*d%*d%n", a, 0, -b, 0, &result)  
 * - Multiplication: via repeated addition
 * - Division: via repeated subtraction
 */
#include <stdio.h>

/* Addition using printf */
int add(int a, int b) {
    int result = 0;
    printf("%*d%*d%n", a, 0, b, 0, &result);
    return result;
}

/* Subtraction using printf */
int sub(int a, int b) {
    int result = 0;
    printf("%*d%*d%n", a, 0, -b, 0, &result);
    return result;
}

/* Multiplication via repeated addition using printf */
int mul(int a, int b) {
    int result = 0;
    for (int i = 0; i < b; i++) {
        result = add(result, a);
    }
    return result;
}

/* Division via repeated subtraction */
int div_op(int a, int b) {
    int result = 0;
    int remaining = a;
    while (remaining >= b) {
        remaining = sub(remaining, b);
        result = add(result, 1);
    }
    return result;
}

/* Modulo via repeated subtraction */
int mod(int a, int b) {
    int remaining = a;
    while (remaining >= b) {
        remaining = sub(remaining, b);
    }
    return remaining;
}

/* Power via repeated multiplication */
int power(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result = mul(result, base);
    }
    return result;
}

int main() {
    printf("=== printf Calculator ===\n\n");

    int a = 15, b = 7;

    printf("Operations with a=%d, b=%d:\n", a, b);
    printf("  a + b = %d\n", add(a, b));
    printf("  a - b = %d\n", sub(a, b));
    printf("  a * b = %d\n", mul(a, b));
    printf("  a / b = %d\n", div_op(a, b));
    printf("  a %% b = %d\n", mod(a, b));
    printf("  2^10  = %d\n", power(2, 10));

    printf("\n=== Each operation implemented via printf format strings ===\n");
    printf("  add:  printf(\"%%*d%%*d%%n\", a, 0, b, 0, &result)\n");
    printf("  sub:  printf(\"%%*d%%*d%%n\", a, 0, -b, 0, &result)\n");
    printf("  mul:  repeated add\n");
    printf("  div:  repeated sub\n");

    return 0;
}
