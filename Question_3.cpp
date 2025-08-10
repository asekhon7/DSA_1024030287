#include <bits/stdc++.h>
using namespace std;

// Find the single missing number in a sorted array containing numbers 1..n (one missing).
// arr length = n-1
int findMissing_1_to_n(const int* arr, int n_minus_1) {
    int l = 0, r = n_minus_1 - 1;
    // We look for the first index where arr[i] != i+1
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (arr[mid] == mid + 1) {
            // Perfect up to mid, hole is to the right
            l = mid + 1;
        } else {
            // Mismatch here or before
            r = mid - 1;
        }
    }
    // l is the first mismatch index; missing number is l+1
    return l + 1;
}

int main1() {
    int a[] = {1, 2, 3, 5, 6};
    int n_minus_1 = sizeof(a) / sizeof(a[0]); // here n would be 6
    cout << "Missing (1..n): " << findMissing_1_to_n(a, n_minus_1) << "\n"; // 4
    return 0;
}
