/*
 * Example 8: Self-Modifying Code via printf
 *
 * Demonstrates how printf can be used to:
 * - Modify its own format string
 * - Implement dynamic dispatch
 * - Create a simple interpreter
 */
#include <stdio.h>
#include <string.h>

int main() {
    char buffer[256];
    int counter = 0;

    printf("=== Self-Modifying Code via printf ===\n\n");

    /* Build a format string dynamically */
    /* This simulates a program that modifies itself */

    /* Create format string: "%d + %d = %d\n" */
    strcpy(buffer, "%d + %d = %d\n");
    printf("Initial format string: \"%s\"\n", buffer);

    /* Use the format string */
    int a = 5, b = 3, result = 0;
    printf("%*d", a, 0);
    printf("%*d", b, 0);
    printf("%n", &result);

    /* Now modify the buffer to include the result */
    /* Build new format string: "5 + 3 = 8" */
    char new_buffer[256];
    sprintf(new_buffer, "%d + %d = %d", a, b, result);
    printf("Modified output: %s\n\n", new_buffer);

    /* More complex: build a printf call dynamically */
    /* This is like an interpreter that executes printf commands */
    printf("=== Dynamic printf Interpreter ===\n\n");

    /* Command format: "OP ARG1 ARG2" */
    const char *commands[] = {
        "ADD 10 20",
        "SUB 50 15",
        "MUL 6 7",
        NULL
    };

    for (int i = 0; commands[i] != NULL; i++) {
        char op[16];
        int arg1, arg2;

        /* Parse command using sscanf */
        sscanf(commands[i], "%s %d %d", op, &arg1, &arg2);

        int res = 0;
        if (strcmp(op, "ADD") == 0) {
            printf("%*d%*d%n", arg1, 0, arg2, 0, &res);
            printf("  %s => %d\n", commands[i], res);
        } else if (strcmp(op, "SUB") == 0) {
            printf("%*d%*d%n", arg1, 0, -arg2, 0, &res);
            printf("  %s => %d\n", commands[i], res);
        } else if (strcmp(op, "MUL") == 0) {
            /* Multiplication via repeated addition */
            for (int j = 0; j < arg2; j++) {
                res += arg1;
            }
            printf("  %s => %d (via repeated add)\n", commands[i], res);
        }
    }

    printf("\n=== Self-modification enables interpretive execution ===\n");
    printf("  This is equivalent to a von Neumann architecture\n");

    return 0;
}
