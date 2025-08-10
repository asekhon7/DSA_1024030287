#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

/*
  Helper: check square size and index bounds
*/
static inline void check_n(int n) {
    if (n <= 0) throw invalid_argument("n must be positive");
}
static inline void check_ij(int n, int i, int j) {
    if (i < 0 || i >= n || j < 0 || j >= n)
        throw out_of_range("index out of range");
}

/*
 (a) Diagonal Matrix
 - Only diagonal elements can be non-zero (i == j).
 - Space: n
 - Mapping: diag[i] stores A[i][i].
*/
struct Diagonal {
    int n;
    vector<int> diag;

    explicit Diagonal(int n): n(n), diag(n, 0) { check_n(n); }

    void set(int i, int j, int val) {
        check_ij(n, i, j);
        if (i == j) diag[i] = val;
        // else ignored (must be zero in a diagonal matrix)
    }
    int get(int i, int j) const {
        check_ij(n, i, j);
        return (i == j) ? diag[i] : 0;
    }
};

/*
 (b) Tri-diagonal Matrix
 - Non-zero possible only on main diagonal, upper diagonal, lower diagonal.
 - Space: 3n - 2 (n main + (n-1) lower + (n-1) upper)
 - Storage layout:
     lower[i] stores A[i][i-1] for i in [1..n-1]
     main[i]  stores A[i][i]   for i in [0..n-1]
     upper[i] stores A[i][i+1] for i in [0..n-2]
*/
struct Tridiagonal {
    int n;
    vector<int> lower, mainD, upper;

    explicit Tridiagonal(int n): n(n), lower(max(0, n-1), 0), mainD(n, 0), upper(max(0, n-1), 0) {
        check_n(n);
    }

    void set(int i, int j, int val) {
        check_ij(n, i, j);
        if (i == j) {
            mainD[i] = val;
        } else if (i == j + 1) {
            // below main diagonal
            lower[i - 1] = val;     // valid when i>=1
        } else if (j == i + 1) {
            // above main diagonal
            upper[i] = val;         // valid when i<=n-2
        } else {
            // must be zero in a tridiagonal matrix
            // ignore if val != 0
        }
    }
    int get(int i, int j) const {
        check_ij(n, i, j);
        if (i == j) return mainD[i];
        if (i == j + 1) return lower[i - 1];
        if (j == i + 1) return upper[i];
        return 0;
    }
};

/*
 (c) Lower Triangular Matrix (including diagonal)
 - Non-zero for i >= j.
 - Space: n(n+1)/2
 - Row-major compact mapping:
     Store row by row, taking only columns 0..i in row i.
     Index formula (0-based):
       idx(i,j) = i*(i+1)/2 + j, valid when i>=j
*/
struct LowerTriangular {
    int n;
    vector<int> data; // size = n(n+1)/2

    explicit LowerTriangular(int n): n(n), data(n*(n+1)/2, 0) { check_n(n); }

    static inline int idx(int i, int j) {
        // assumes i>=j
        return i*(i+1)/2 + j;
    }

    void set(int i, int j, int val) {
        check_ij(n, i, j);
        if (i >= j) data[idx(i, j)] = val;
        // else ignored (must be zero)
    }
    int get(int i, int j) const {
        check_ij(n, i, j);
        if (i >= j) return data[idx(i, j)];
        return 0;
    }
};

/*
 (d) Upper Triangular Matrix (including diagonal)
 - Non-zero for i <= j.
 - Space: n(n+1)/2
 - Row-major compact mapping:
     Store row by row, but only columns i..n-1 in row i.
     Number of stored elements before row i = sum_{r=0}^{i-1} (n - r) = i*n - i*(i-1)/2
     Then within row i, column j contributes offset (j - i)
     So:
       idx(i,j) = (i*n - i*(i-1)/2) + (j - i), valid when i<=j
*/
struct UpperTriangular {
    int n;
    vector<int> data;

    explicit UpperTriangular(int n): n(n), data(n*(n+1)/2, 0) { check_n(n); }

    inline int prefixCountBeforeRow(int i) const {
        // count of stored elements from rows 0..i-1
        // = sum_{r=0}^{i-1} (n - r) = i*n - i*(i-1)/2
        return i*n - (i*(i-1))/2;
    }
    inline int idx(int i, int j) const {
        // assumes i<=j
        return prefixCountBeforeRow(i) + (j - i);
    }

    void set(int i, int j, int val) {
        check_ij(n, i, j);
        if (i <= j) data[idx(i, j)] = val;
        // else ignored (must be zero)
    }
    int get(int i, int j) const {
        check_ij(n, i, j);
        if (i <= j) return data[idx(i, j)];
        return 0;
    }
};

/*
 (e) Symmetric Matrix
 - A[i][j] == A[j][i]
 - Only need to store lower (or upper) triangle including diagonal.
 - Space: n(n+1)/2
 - Use same mapping as LowerTriangular for convenience:
     Store min(i,j) as row, max(i,j) as col in lower triangle:
       i' = max(i,j), j' = min(i,j) so i'>=j'
       idx = i'*(i'+1)/2 + j'
*/
struct SymmetricMatrix {
    int n;
    vector<int> data;

    explicit SymmetricMatrix(int n): n(n), data(n*(n+1)/2, 0) { check_n(n); }

    static inline int lowerIdx(int i, int j) {
        int r = max(i, j), c = min(i, j);
        return r*(r+1)/2 + c;
    }

    void set(int i, int j, int val) {
        check_ij(n, i, j);
        data[lowerIdx(i, j)] = val;
    }
    int get(int i, int j) const {
        check_ij(n, i, j);
        return data[lowerIdx(i, j)];
    }
};

/*
  Demo: small tests for each structure.
  You can tweak n and values to see the compact storage in action.
*/
int main() {
    cout << "=== Diagonal Matrix ===\n";
    {
        int n = 4;
        Diagonal D(n);
        D.set(0,0,5); D.set(1,1,7); D.set(2,2,9); D.set(3,3,2);
        D.set(0,1,123); // ignored (off-diagonal)
        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++) cout << D.get(i,j) << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    cout << "=== Tridiagonal Matrix ===\n";
    {
        int n = 5;
        Tridiagonal T(n);
        // main diagonal
        for (int i=0;i<n;i++) T.set(i,i,10*(i+1));
        // upper diagonal
        for (int i=0;i<n-1;i++) T.set(i, i+1, 1);
        // lower diagonal
        for (int i=1;i<n;i++) T.set(i, i-1, -1);

        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++) cout << T.get(i,j) << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    cout << "=== Lower Triangular Matrix ===\n";
    {
        int n = 4;
        LowerTriangular L(n);
        // Fill with i*10 + j for i>=j
        for (int i=0;i<n;i++)
            for (int j=0;j<=i;j++)
                L.set(i, j, i*10 + j);

        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++) cout << L.get(i,j) << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    cout << "=== Upper Triangular Matrix ===\n";
    {
        int n = 4;
        UpperTriangular U(n);
        // Fill with i*10 + j for i<=j
        for (int i=0;i<n;i++)
            for (int j=i;j<n;j++)
                U.set(i, j, i*10 + j);

        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++) cout << U.get(i,j) << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    cout << "=== Symmetric Matrix ===\n";
    {
        int n = 4;
        SymmetricMatrix S(n);
        // Define upper triangle values, symmetry auto-applies
        // Set S(i,j) = i+j (for i<=j), but we can call set in any order
        for (int i=0;i<n;i++)
            for (int j=i;j<n;j++)
                S.set(i, j, i + j);

        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++) cout << S.get(i,j) << " ";
            cout << "\n";
        }
        cout << "\n";
    }

    return 0;
}
