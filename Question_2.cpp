#include <iostream>
using namespace std;

// Helper: print the array nicely
void printArray(const int* arr, int n) {
    for (int i = 0; i < n; ++i) {
        if (i) cout << " ";
        cout << arr[i];
    }
    cout << "\n";
}

/**
 * Bubble Sort (simple and easy to follow)
 * - Repeatedly compares adjacent elements and swaps if they’re in the wrong order.
 * - After the i-th pass, the largest element among the unsorted part bubbles to the end.
 * - Time: O(n^2) in worst/average cases; O(n) if already sorted (with early-exit).
 */
void bubbleSort(int* arr, int n) {
    // Basic safety
    if (n <= 1) return;

    // Outer loop: number of passes
    for (int pass = 0; pass < n - 1; ++pass) {
        bool swapped = false; // track if any swap happened in this pass

        // Inner loop: compare adjacent pairs up to the unsorted boundary (n - 1 - pass)
        for (int j = 0; j < n - 1 - pass; ++j) {
            // If the left element is bigger, swap them
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // Optional: show array state after each pass (helps visualize)
        // Comment this out if you want cleaner output.
        cout << "After pass " << pass + 1 << ": ";
        printArray(arr, n);

        // If no swaps in this pass, the array is already sorted — bail out early
        if (!swapped) break;
    }
}

int main() {
    // Given elements
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original: ";
    printArray(arr, n);

    bubbleSort(arr, n);

    cout << "Sorted:   ";
    printArray(arr, n);

    return 0;
}
