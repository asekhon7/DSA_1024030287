#include <iostream>
using namespace std;

// Function to count distinct elements in array A of size n
int countDistinct(int A[], int n) {
    int distinctCount = 0;
    
    for (int i = 0; i < n; i++) {
        bool found = false;
        // Check if A[i] appeared before in the array
        for (int j = 0; j < i; j++) {
            if (A[i] == A[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            distinctCount++;
        }
    }
    
    return distinctCount;
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

    int result = countDistinct(A, n);
    cout << "Number of distinct elements: " << result << endl;

    return 0;
}
