/*
 * Example 7: Pointer Arithmetic with printf
 *
 * Demonstrates how printf can be used to:
 * - Read and write arbitrary memory locations
 * - Implement array operations
 * - Simulate a pointer-based data structure
 */
#include <stdio.h>
#include <string.h>

int main() {
    int array[10] = {0};
    int *ptr = array;

    printf("=== Pointer Arithmetic with printf ===\n\n");

    /* Initialize array using printf */
    /* array[0] = 10, array[1] = 20, ..., array[9] = 100 */
    for (int i = 0; i < 10; i++) {
        int *target = ptr + i;
        /* Print exactly (i+1)*10 characters, store count in target */
        printf("%*d%n", (i + 1) * 10, 0, target);
    }

    printf("Array contents:\n  ");
    for (int i = 0; i < 10; i++) {
        printf("[%d]=%d ", i, array[i]);
        if (i == 4) printf("\n  ");
    }
    printf("\n\n");

    /* Sum all elements using printf */
    int sum = 0;
    for (int i = 0; i < 10; i++) {
        printf("%*d", array[i], 0);
    }
    printf("%n", &sum);
    printf("Sum of array (via printf): %d\n", sum);

    /* Matrix multiplication simulation */
    int A[2][2] = {{1, 2}, {3, 4}};
    int B[2][2] = {{5, 6}, {7, 8}};
    int C[2][2] = {{0, 0}, {0, 0}};

    printf("\nMatrix multiplication (2x2):\n");
    printf("  A = [%d %d; %d %d]\n", A[0][0], A[0][1], A[1][0], A[1][1]);
    printf("  B = [%d %d; %d %d]\n", B[0][0], B[0][1], B[1][0], B[1][1]);

    /* C[i][j] = sum(A[i][k] * B[k][j]) for k=0..1 */
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int cell_sum = 0;
            for (int k = 0; k < 2; k++) {
                int product = 0;
                printf("%*d", A[i][k] * B[k][j], 0);
            }
            printf("%n", &cell_sum);
            C[i][j] = cell_sum;
        }
    }

    printf("  C = A*B = [%d %d; %d %d]\n", C[0][0], C[0][1], C[1][0], C[1][1]);

    printf("\n=== Pointer operations via printf enable data structures ===\n");

    return 0;
}
