#include <iostream>
using namespace std;

// Function to count inversions in array A of size n
int countInversions(int A[], int n) {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (A[i] > A[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    int n;
    cout << "Enter number of elements:\n";
    cin >> n;

    int A[100];  // max 100 elements
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    int inversions = countInversions(A, n);
    cout << "Number of inversions: " << inversions << endl;

    return 0;
}
