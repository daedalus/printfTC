/*
 * Example 5: Conditional Logic with printf
 *
 * Demonstrates how to implement conditional behavior using:
 * - Ternary operators with format strings
 * - Argument position selectors (%n$)
 * - Width/precision specifiers that vary based on conditions
 */
#include <stdio.h>

int main() {
    int x = 42;
    int result = 0;

    printf("=== Conditional Logic with printf ===\n\n");

    /* Conditional selection: choose between two values */
    /* If x > 0, result = 100, else result = 200 */
    int cond = (x > 0);
    printf("x = %d, x > 0 is %s\n", x, cond ? "true" : "false");

    /* Using printf to set result based on condition */
    /* Print 100 chars if true, 200 chars if false */
    printf("%*d%n", cond ? 100 : 200, 0, &result);
    printf("Result (via conditional width): %d\n", result);

    /* Min/Max using printf */
    int a = 15, b = 23;
    int max_result = 0, min_result = 0;

    /* max(a,b): print max(a,b) spaces */
    printf("%*d%n", a > b ? a : b, 0, &max_result);
    printf("max(%d, %d) = %d\n", a, b, max_result);

    /* min(a,b): print min(a,b) spaces */
    printf("%*d%n", a < b ? a : b, 0, &min_result);
    printf("min(%d, %d) = %d\n", a, b, min_result);

    /* Absolute value using printf */
    int val = -42;
    int abs_val = 0;
    printf("%*d%n", val < 0 ? -val : val, 0, &abs_val);
    printf("abs(%d) = %d\n", val, abs_val);

    /* Sign function */
    int sign = 0;
    printf("%*d%n", val > 0 ? 1 : (val < 0 ? -1 : 0), 0, &sign);
    printf("sign(%d) = %d\n", val, sign);

    printf("\n=== Conditional operations enable decision-making ===\n");
    printf("  Combined with loops, this gives us:\n");
    printf("    - Branching (if/else)\n");
    printf("    - Loops (while/for)\n");
    printf("    - Memory (via variables modified by %%n)\n");
    printf("    This is sufficient for Turing completeness!\n");

    return 0;
}
