/*
 * Example 8: Self-Modifying Code via printf
 *
 * Demonstrates how printf can be used to:
 * - Build and execute format strings dynamically
 * - Implement an interpreter driven by data
 * - Create a von Neumann style stored-program machine
 */
#include <stdio.h>
#include <string.h>

int main() {
    char buffer[256];

    printf("=== Self-Modifying Code via printf ===\n\n");

    /* Build a format string dynamically */
    strcpy(buffer, "%d + %d = %d\n");
    printf("Initial format string: \"%s\"\n", buffer);

    /* Use printf to compute 5 + 3 via character counting */
    int a = 5, b = 3, result = 0;
    printf("%*s%*s%n", a, "", b, "", &result);

    /* Modify the buffer to include the computed result */
    char new_buffer[256];
    sprintf(new_buffer, "%d + %d = %d", a, b, result);
    printf("Modified output: %s\n\n", new_buffer);

    /* Interpreter: execute data-driven printf commands */
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

        sscanf(commands[i], "%s %d %d", op, &arg1, &arg2);

        int res = 0;
        if (strcmp(op, "ADD") == 0) {
            printf("%*s%*s%n", arg1, "", arg2, "", &res);
            printf("  %s => %d\n", commands[i], res);
        } else if (strcmp(op, "SUB") == 0) {
            printf("%*s%n", arg1, "", &res);
            res -= arg2;
            printf("  %s => %d\n", commands[i], res);
        } else if (strcmp(op, "MUL") == 0) {
            for (int j = 0; j < arg2; j++) {
                res = res + arg1;
            }
            printf("  %s => %d (via repeated add)\n", commands[i], res);
        }
    }

    printf("\n=== Self-modification enables interpretive execution ===\n");
    printf("  Data (commands array) drives code (printf calls)\n");
    printf("  This is equivalent to a von Neumann architecture\n");

    return 0;
}
