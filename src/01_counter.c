/*
 * Example 1: Basic Counter using %n
 * 
 * %n writes the number of characters printed so far to an integer pointer.
 * By combining multiple %n specifiers, we can perform arithmetic.
 */
#include <stdio.h>

int main() {
    int a = 0, b = 0;

    /*
     * Step-by-step:
     * "%10d" prints 10 characters (spaces/padding)
     * "%n" writes 10 to 'a'
     * "%20d" prints 20 more characters
     * "%n" writes 30 (10+20) to 'b'
     */
    printf("%10d%n%20d%n", 0, &a, 0, &b);

    printf("After first printf:\n");
    printf("  a = %d (printed 10 chars)\n", a);
    printf("  b = %d (printed 10+20 = 30 chars)\n", b);

    /*
     * Now 'a' holds 10, 'b' holds 30.
     * We can use these values as arguments for future printf calls.
     * This creates a feedback loop: printf modifies memory,
     * and those modifications affect subsequent calls.
     */
    printf("%*d%n", a, 42, &a);
    printf("After using 'a' as width specifier:\n");
    printf("  a = %d (was 10, printed 10 chars for width, total = 10+10 = 20)\n", a);

    printf("\n=== Key insight: printf is an ALU ===\n");
    printf("  - Width specifiers (%%*d) use values as parameters\n");
    printf("  - %%n writes results back to memory\n");
    printf("  - This is a read-modify-write cycle\n");

    return 0;
}
