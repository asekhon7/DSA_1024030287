#include <iostream>
using namespace std;

/**
 * Binary Search on a raw array (iterative)
 * @param arr pointer to the first element
 * @param n   number of elements
 * @param target value to find
 * @return index of target if found, else -1
 */
int binarySearch(const int* arr, int n, int target) {
    if (n <= 0) return -1; 

    int left = 0;
    int right = n - 1;

    while (left <= right) {
        // Safe mid calculation (avoids potential overflow)
        int mid = left + (right - left) / 2;
        int midVal = arr[mid];

        if (midVal == target) {
            return mid; // found it
        } else if (midVal < target) {
            left = mid + 1;  // search right half
        } else {
            right = mid - 1; // search left half
        }
    }
    return -1; // not found
}

int main() {
    // Sorted array (must be ascending)
    int a[] = {-5, -1, 0, 3, 4, 7, 9, 12};
    int n = sizeof(a) / sizeof(a[0]);

    cout << binarySearch(a, n, 7) << "\n";  // 5
    cout << binarySearch(a, n, 8) << "\n";  // -1
    return 0;
}
