#include <iostream>
using namespace std;

const int MAX = 100;  // max number of non-zero elements

struct Triplet {
    int row;
    int col;
    int val;
};

// Read sparse matrix from user input
void readMatrix(int &rows, int &cols, int &nonZero, Triplet elements[]) {
    cout << "Enter rows, cols, number of non-zero elements:\n";
    cin >> rows >> cols >> nonZero;
    cout << "Enter non-zero elements (row col val):\n";
    for (int i = 0; i < nonZero; i++) {
        cin >> elements[i].row >> elements[i].col >> elements[i].val;
    }
}

// Display sparse matrix
void displayMatrix(const Triplet elements[], int nonZero) {
    cout << "Row Col Value\n";
    for (int i = 0; i < nonZero; i++) {
        cout << elements[i].row << "   " << elements[i].col << "   " << elements[i].val << "\n";
    }
}

// Transpose sparse matrix
void transpose(int rows, int cols, int nonZero, const Triplet elements[], Triplet result[], int &resNonZero) {
    resNonZero = 0;
    // For each column, collect elements with that column and swap row and col
    for (int c = 0; c < cols; c++) {
        for (int i = 0; i < nonZero; i++) {
            if (elements[i].col == c) {
                result[resNonZero].row = elements[i].col;
                result[resNonZero].col = elements[i].row;
                result[resNonZero].val = elements[i].val;
                resNonZero++;
            }
        }
    }
}

// Add two sparse matrices
bool add(int r1, int c1, int n1, const Triplet m1[],
         int r2, int c2, int n2, const Triplet m2[],
         Triplet result[], int &resNonZero) {
    
    if (r1 != r2 || c1 != c2) {
        cout << "Addition not possible due to dimension mismatch.\n";
        return false;
    }

    resNonZero = 0;
    int i = 0, j = 0;

    while (i < n1 && j < n2) {
        int pos1 = m1[i].row * c1 + m1[i].col;
        int pos2 = m2[j].row * c2 + m2[j].col;

        if (pos1 < pos2) {
            result[resNonZero++] = m1[i++];
        } else if (pos1 > pos2) {
            result[resNonZero++] = m2[j++];
        } else {
            int valSum = m1[i].val + m2[j].val;
            if (valSum != 0) {
                result[resNonZero++] = {m1[i].row, m1[i].col, valSum};
            }
            i++; j++;
        }
    }

    while (i < n1) {
        result[resNonZero++] = m1[i++];
    }
    while (j < n2) {
        result[resNonZero++] = m2[j++];
    }

    return true;
}

// Multiply two sparse matrices
bool multiply(int r1, int c1, int n1, const Triplet m1[],
              int r2, int c2, int n2, const Triplet m2[],
              Triplet result[], int &resNonZero) {
    
    if (c1 != r2) {
        cout << "Multiplication not possible due to dimension mismatch.\n";
        return false;
    }

    resNonZero = 0;
    // We'll store intermediate sums in a temporary array indexed by (row, col)
    // Since max size unknown, use a fixed array with large enough size (assuming matrix <= 10x10)
    int temp[10][10] = {0};

    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (m1[i].col == m2[j].row) {
                temp[m1[i].row][m2[j].col] += m1[i].val * m2[j].val;
            }
        }
    }

    // Convert temp back to triplet form
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            if (temp[i][j] != 0) {
                result[resNonZero].row = i;
                result[resNonZero].col = j;
                result[resNonZero].val = temp[i][j];
                resNonZero++;
            }
        }
    }

    return true;
}

int main() {
    Triplet m1[MAX], m2[MAX], result[MAX];
    int r1, c1, n1, r2, c2, n2;

    cout << "Matrix 1:\n";
    readMatrix(r1, c1, n1, m1);

    cout << "Matrix 2:\n";
    readMatrix(r2, c2, n2, m2);

    cout << "\nMatrix 1:\n";
    displayMatrix(m1, n1);

    cout << "\nMatrix 2:\n";
    displayMatrix(m2, n2);

    // Transpose of Matrix 1
    int transNonZero;
    Triplet transposed[MAX];
    transpose(r1, c1, n1, m1, transposed, transNonZero);
    cout << "\nTranspose of Matrix 1:\n";
    displayMatrix(transposed, transNonZero);

    // Addition
    int addNonZero;
    if (add(r1, c1, n1, m1, r2, c2, n2, m2, result, addNonZero)) {
        cout << "\nAddition of Matrix 1 and 2:\n";
        displayMatrix(result, addNonZero);
    }

    // Multiplication
    int mulNonZero;
    if (multiply(r1, c1, n1, m1, r2, c2, n2, m2, result, mulNonZero)) {
        cout << "\nMultiplication of Matrix 1 and 2:\n";
        displayMatrix(result, mulNonZero);
    }

    return 0;
}
