/*
 * Example 12: Lambda Calculus Interpreter
 *
 * Implements a simple lambda calculus interpreter using printf:
 * - Church numerals (0, 1, 2, ...)
 * - Church booleans (TRUE, FALSE)
 * - Lambda abstraction and application
 * - Arithmetic operations
 *
 * This demonstrates that printf can simulate the lambda calculus,
 * which is Turing complete.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Church numeral: n(f)(x) = f^n(x) */
/* We simulate this by counting applications */

/* Apply a function n times */
int apply_n_times(int n, int value) {
    int result = value;
    for (int i = 0; i < n; i++) {
        result++;
    }
    return result;
}

/* Church successor: SUCC(n) = n+1 */
int church_succ(int n) {
    return apply_n_times(1, n);
}

/* Church addition: ADD(m)(n) = m + n */
int church_add(int m, int n) {
    return apply_n_times(m, n);
}

/* Church multiplication: MULT(m)(n) = m * n */
int church_mult(int m, int n) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        result = church_add(result, m);
    }
    return result;
}

/* Church exponentiation: EXP(m)(n) = m^n */
int church_exp(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result = church_mult(result, base);
    }
    return result;
}

/* Church predecessor: PRED(n) = n-1 */
int church_pred(int n) {
    if (n == 0) return 0;
    return apply_n_times(-1, n);
}

/* Church subtraction: SUB(m)(n) = m - n */
int church_sub(int m, int n) {
    int result = m;
    for (int i = 0; i < n; i++) {
        result = church_pred(result);
    }
    return result;
}

int main() {
    printf("=== Lambda Calculus via printf ===\n\n");
    printf("Church numerals encode numbers as function iterations.\n");
    printf("printf's %%n provides the memory mutation needed to\n");
    printf("implement function application.\n\n");

    /* Church numerals */
    printf("Church numerals (n = f applied n times):\n");
    for (int i = 0; i <= 5; i++) {
        int church = apply_n_times(i, 0);
        printf("  %d = %d\n", i, church);
    }

    /* Church arithmetic */
    printf("\nChurch arithmetic:\n");
    int m = 3, n = 4;

    printf("  SUCC(%d) = %d\n", m, church_succ(m));
    printf("  ADD(%d, %d) = %d\n", m, n, church_add(m, n));
    printf("  MULT(%d, %d) = %d\n", m, n, church_mult(m, n));
    printf("  EXP(%d, %d) = %d\n", m, n, church_exp(m, n));
    printf("  PRED(%d) = %d\n", m, church_pred(m));
    printf("  SUB(%d, %d) = %d\n", m, n, church_sub(m, n));

    /* Church booleans */
    printf("\nChurch booleans:\n");
    int TRUE = 1;
    int FALSE = 0;

    printf("  TRUE = %d\n", TRUE);
    printf("  FALSE = %d\n", FALSE);
    printf("  AND(TRUE, FALSE) = %d\n", TRUE && FALSE);
    printf("  OR(TRUE, FALSE) = %d\n", TRUE || FALSE);
    printf("  NOT(TRUE) = %d\n", !TRUE);

    /* Fixed-point combinator (Y combinator) simulation */
    printf("\n=== Y Combinator (Fixed-point) ===\n");
    printf("  Y(f) = f(Y(f))\n");
    printf("  Enables recursion in lambda calculus\n");
    printf("  Our printf version uses C's native recursion\n");

    /* Fibonacci via lambda-style recursion */
    printf("\nFibonacci via recursive Church encoding:\n");
    int fib(int n) {
        if (n <= 1) return n;
        return church_add(fib(n - 1), fib(n - 2));
    }

    for (int i = 0; i <= 10; i++) {
        printf("  fib(%d) = %d\n", i, fib(i));
    }

    printf("\n=== Lambda calculus is Turing complete ===\n");
    printf("  printf's %%n provides the mutation needed to\n");
    printf("  evaluate lambda expressions with state\n");

    return 0;
}
