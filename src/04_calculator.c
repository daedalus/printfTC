/*
 * Example 4: printf Calculator
 *
 * Implements arithmetic using printf's format string:
 * - Addition: printf("%*s%*s%n", a, "", b, "", &result) → a+b
 * - Subtraction: printf stores a, C subtracts b, printf stores result
 * - Multiplication: via repeated addition
 * - Division: via repeated subtraction
 *
 * printf's %n provides STORE (write to memory).
 * %*s provides LOAD (read stored value as width).
 * These two primitives, combined with C's control flow,
 * form a Turing-complete system.
 */
#include <stdio.h>

/* Addition: pure printf — print a+b spaces, capture total */
int add(int a, int b) {
    int result = 0;
    printf("%*s%*s%n", a, "", b, "", &result);
    return result;
}

/* Subtraction: printf can only ADD to the running character count,
 * so a-b requires loading a via %n, then C subtracts b.
 * printf still mediates all memory access. */
int sub(int a, int b) {
    int result = 0;
    printf("%*s%n", a, "", &result);
    result -= b;
    return result;
}

/* Multiplication via repeated addition */
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
    int remaining = 0;
    printf("%*s%n", a, "", &remaining);
    while (remaining >= b) {
        remaining = sub(remaining, b);
        result = add(result, 1);
    }
    return result;
}

/* Modulo via repeated subtraction */
int mod(int a, int b) {
    int remaining = 0;
    printf("%*s%n", a, "", &remaining);
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

    /* Edge cases */
    printf("\nEdge cases:\n");
    printf("  0 + 0 = %d\n", add(0, 0));
    printf("  0 + 5 = %d\n", add(0, 5));
    printf("  5 + 0 = %d\n", add(5, 0));
    printf("  10 - 10 = %d\n", sub(10, 10));
    printf("  7 - 0 = %d\n", sub(7, 0));

    printf("\n=== How it works ===\n");
    printf("  add:  printf(\"%%*s%%*s%%n\", a, \"\", b, \"\", &r)  // r = a+b\n");
    printf("  sub:  printf(\"%%*s%%n\", a, \"\", &r); r -= b;   // r = a-b\n");
    printf("  mul:  repeated add\n");
    printf("  div:  repeated sub\n");

    return 0;
}
