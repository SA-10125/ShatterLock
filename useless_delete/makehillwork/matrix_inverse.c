// C program to find the inverse of Matrix.

#include <stdio.h>
#include <stdlib.h>

void makehillkey(int seed, int** hillkey_out) { //github copilot made this. pls forgive.
    srand(seed);

    // Generate a 25x25 invertible matrix mod 26 using LU construction

    int L[25][25] = {0};
    int U[25][25] = {0};

    // Fill L (lower-triangular with 1s on diagonal)
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j) {
                L[i][j] = 1;
            } else {
                L[i][j] = rand() % 26;
            }
        }
    }

    // Fill U (upper-triangular with invertible diagonal)
    for (int i = 0; i < 25; i++) {
        for (int j = i; j < 25; j++) {
            if (i == j) {
                int val = (rand() % 25) + 1; // 1..25
                while (val % 2 == 0 || val % 13 == 0) {
                    val = (rand() % 25) + 1;
                }
                U[i][j] = val;
            } else {
                U[i][j] = rand() % 26;
            }
        }
    }

    // Multiply L and U to get key matrix (mod 26)
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            int sum = 0;
            for (int k = 0; k < 25; k++) {
                sum = (sum + L[i][k] * U[k][j]) % 26;
            }
            hillkey_out[i][j] = sum;
        }
    }

    // hillkey_out is guaranteed invertible mod 26

    // Now hillkey_out is a random invertible matrix mod 26, reproducible from the seed.
}

// Function to compute (a mod m)
int mod(int a, int m) {
    int result = a % m;
    if (result < 0) result += m;
    return result;
}

// Function to find modular multiplicative inverse of a under modulo m
// using Extended Euclidean Algorithm
int modInverse(int a, int m) {
    a = mod(a, m);
    for (int x = 1; x < m; x++) {
        if (mod(a * x, m) == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

// Function to Print matrix.
void PrintMatrix(int** ar, int n, int m)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d  ", ar[i][j]);
        }
        printf("\n");
    }
    return;
}

// Function to Print inverse matrix
void PrintInverse(int** ar, int n, int m)
{
    for (int i = 0; i < n; i++) {
        for (int j = n; j < m; j++) {
            printf("%d  ", ar[i][j]);
        }
        printf("\n");
    }
    return;
}

// Function to perform the inverse operation on the matrix modulo 26.
void InverseOfMatrix(int** matrix, int order)
{
    int temp;
    int modVal = 26;

    // PrintMatrix function to print the element of the matrix.
    printf("=== Original Matrix ===\n");
    PrintMatrix(matrix, order, order);

    // Create the augmented matrix
    // Add the identity matrix of order at the end of original matrix.
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < 2 * order; j++) {
            // Add '1' at the diagonal places to create identity matrix
            if (j == (i + order))
                matrix[i][j] = 1;
            else if (j >= order)
                matrix[i][j] = 0;
        }
    }

    printf("\n=== Augmented Matrix ===\n");
    PrintMatrix(matrix, order, order * 2);

    // Gauss-Jordan elimination with modular arithmetic
    for (int i = 0; i < order; i++) {
        // Find pivot element's modular inverse
        int pivot = mod(matrix[i][i], modVal);
        int pivotInv = modInverse(pivot, modVal);
        
        if (pivotInv == -1) {
            printf("\nMatrix is not invertible mod 26!\n");
            return;
        }

        // Multiply the current row by pivot inverse (mod 26)
        for (int j = 0; j < 2 * order; j++) {
            matrix[i][j] = mod(matrix[i][j] * pivotInv, modVal);
        }

        // Eliminate all other rows
        for (int k = 0; k < order; k++) {
            if (k != i) {
                int factor = mod(matrix[k][i], modVal);
                for (int j = 0; j < 2 * order; j++) {
                    matrix[k][j] = mod(matrix[k][j] - factor * matrix[i][j], modVal);
                }
            }
        }
    }

    // Print the resultant Inverse matrix.
    printf("\n=== Inverse Matrix (mod 26) ===\n");
    PrintInverse(matrix, order, 2 * order);

    return;
}

// Driver code
int main()
{
    int order;

    // Order of the matrix
    // The matrix must be a square matrix
    order = 25;

    int** matrix = (int**)malloc(25 * sizeof(int*));
    for (int i = 0; i < 25; i++)
        matrix[i] = (int*)malloc(50 * sizeof(int));

    // Initialize with a 25x25 matrix using makehillkey
    // This matrix is guaranteed invertible mod 26
    int seed = 12345; // You can change this seed value
    makehillkey(seed, matrix);

    // Get the inverse of matrix
    InverseOfMatrix(matrix, order);

    // Free allocated memory
    for (int i = 0; i < 25; i++)
        free(matrix[i]);
    free(matrix);

    return 0;
}

#define R1 5 //numpacks // number of rows in Matrix-1
#define C1 25 // number of columns in Matrix-1
#define R2 25 // number of rows in Matrix-2
#define C2 25 // number of columns in Matrix-2

void mulMat(int m1[R1][C1], int m2[R2][C2], int rslt[R1][C2]) {
    if (C1 != R2) {
       printf("Invalid Input");
       return;
    }  
  
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            rslt[i][j] = 0;

            // Changed R2 to C1 for correct multiplication
            for (int k = 0; k < C1; k++) { 
                rslt[i][j] = mod(rslt[i][j] + m1[i][k] * m2[k][j], 26);
            }
        }
    }
}