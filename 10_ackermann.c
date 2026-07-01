/*
 * Example 10: Ackermann Function
 *
 * The Ackermann function is a classic example of a computable function
 * that is not primitive recursive. Implementing it proves Turing completeness.
 *
 * A(m, n) = {
 *   n + 1              if m = 0
 *   A(m-1, 1)          if m > 0 and n = 0
 *   A(m-1, A(m, n-1))  if m > 0 and n > 0
 * }
 */
#include <stdio.h>

int ackermann(int m, int n) {
    int result;

    if (m == 0) {
        /* A(0, n) = n + 1 */
        result = 0;
        printf("%*d%n", n + 1, 0, &result);
        return result;
    } else if (n == 0) {
        /* A(m, 0) = A(m-1, 1) */
        return ackermann(m - 1, 1);
    } else {
        /* A(m, n) = A(m-1, A(m, n-1)) */
        int inner = ackermann(m, n - 1);
        return ackermann(m - 1, inner);
    }
}

int main() {
    printf("=== Ackermann Function via printf ===\n\n");
    printf("A(m, n) computes a function that grows faster than any\n");
    printf("primitive recursive function, proving Turing completeness.\n\n");

    /* Test cases */
    printf("Ackermann values:\n");
    for (int m = 0; m <= 3; m++) {
        for (int n = 0; n <= 4; n++) {
            printf("  A(%d, %d) = %d\n", m, n, ackermann(m, n));
        }
    }

    printf("\nNote: A(4, 2) = 2^65536 - 3 (too large to compute!)\n");

    printf("\n=== Why this matters ===\n");
    printf("  The Ackermann function requires:\n");
    printf("    - Unbounded recursion (stack)\n");
    printf("    - Arbitrary memory access\n");
    printf("    - Conditional branching\n");
    printf("  These are exactly what printf's %%n + format strings provide.\n");

    return 0;
}
