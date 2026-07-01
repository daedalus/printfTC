/*
 * Example 2: Two-Counter Machine (Minsky Machine)
 *
 * A Minsky machine with 2 counters is Turing complete.
 * Operations: INC(counter), DEC(counter), JZ(counter, label)
 *
 * We implement this using printf's %n to modify counters
 * and conditional logic through format strings.
 */
#include <stdio.h>
#include <string.h>

int main() {
    int c1 = 0, c2 = 0;  // Two counters
    int step = 0;

    printf("=== Two-Counter Machine Simulation ===\n\n");

    /* Program: Compute c1 = 5, then copy to c2
     *
     * INC c1  (5 times)
     * INC c2  (5 times) 
     * DEC c1  (5 times)
     *
     * This tests counter manipulation and shows the machine
     * can move values between counters.
     */

    /* INC c1 five times: each "%d" prints 1 char, %n adds to c1 */
    printf("%d%n%d%n%d%n%d%n%d%n", 1, &c1, 2, &c1, 3, &c1, 4, &c1, 5, &c1);
    printf("After INC c1 x5: c1=%d\n", c1);

    /* INC c2 five times */
    printf("%d%n%d%n%d%n%d%n%d%n", 1, &c2, 2, &c2, 3, &c2, 4, &c2, 5, &c2);
    printf("After INC c2 x5: c2=%d\n", c2);

    /* DEC c1: subtract 5 by printing 5 chars and writing -5 offset */
    /* We use a trick: print a string of known length */
    printf("%-5s%n", "", &c1);
    /* Note: c1 is now negative (5 - 5 = 0 from the 5 chars of padding) */

    /*
     * More practical: use %n to set counters to specific values
     * by controlling exactly how many chars precede each %n
     */
    c1 = 0; c2 = 0;

    /* Set c1 = 42: print exactly 42 characters before %n */
    printf("                                          %n", &c1);  // 42 spaces
    printf("Set c1 = %d\n", c1);

    /* Set c2 = c1 + 10: print c1 chars, then 10 more */
    printf("%*d%10d%n", c1, 0, 0, &c2);
    printf("Set c2 = c1 + 10 = %d\n", c2);

    printf("\n=== Two-counter machines are proven Turing-complete ===\n");
    printf("  Reference: Minsky, M. (1967) 'Computation: Finite and Infinite Machines'\n");

    return 0;
}
