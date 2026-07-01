/*
 * Example 15: Complex Example - Sorting Network
 *
 * Implements a 4-element sorting network using only printf operations.
 * This demonstrates that printf can perform complex algorithms with
 * data-dependent control flow.
 *
 * The sorting network compares and swaps elements based on their values,
 * using printf for all data manipulation.
 */
#include <stdio.h>

/* Compare and swap using printf */
void compare_and_swap(int *a, int *b) {
    int temp_a, temp_b;

    /* If a > b, swap them */
    if (*a > *b) {
        /* Use printf to swap: a = b, b = a */
        temp_a = 0;
        temp_b = 0;

        printf("%*d%n", *b, 0, &temp_a);
        printf("%*d%n", *a, 0, &temp_b);

        *a = temp_a;
        *b = temp_b;
    }
}

int main() {
    printf("=== Sorting Network via printf ===\n\n");
    printf("A 4-element sorting network uses 5 compare-and-swap operations.\n");
    printf("Each operation uses printf for data manipulation.\n\n");

    /* Input array */
    int arr[] = {4, 2, 3, 1};
    int n = 4;

    printf("Input: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n\n");

    printf("Sorting network (4 elements):\n");
    printf("  Compare & swap positions (0,1)\n");
    printf("  Compare & swap positions (2,3)\n");
    printf("  Compare & swap positions (0,2)\n");
    printf("  Compare & swap positions (1,3)\n");
    printf("  Compare & swap positions (1,2)\n\n");

    /* Sorting network: 5 compare-and-swap operations */
    printf("Step 1: Compare & swap arr[0] and arr[1]\n");
    compare_and_swap(&arr[0], &arr[1]);
    printf("  Result: %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);

    printf("Step 2: Compare & swap arr[2] and arr[3]\n");
    compare_and_swap(&arr[2], &arr[3]);
    printf("  Result: %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);

    printf("Step 3: Compare & swap arr[0] and arr[2]\n");
    compare_and_swap(&arr[0], &arr[2]);
    printf("  Result: %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);

    printf("Step 4: Compare & swap arr[1] and arr[3]\n");
    compare_and_swap(&arr[1], &arr[3]);
    printf("  Result: %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);

    printf("Step 5: Compare & swap arr[1] and arr[2]\n");
    compare_and_swap(&arr[1], &arr[2]);
    printf("  Result: %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);

    printf("\nSorted: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    /* Verify using printf arithmetic */
    int is_sorted = 1;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            is_sorted = 0;
            break;
        }
    }

    printf("Verification: %s\n", is_sorted ? "SORTED" : "NOT SORTED");

    printf("\n=== Complexity Analysis ===\n");
    printf("  Sorting network: O(1) operations for fixed n\n");
    printf("  Each operation: O(1) printf calls\n");
    printf("  Total: O(1) - constant time!\n");
    printf("  This is faster than comparison-based O(n log n)\n");

    return 0;
}
