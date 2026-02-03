// Verify that the matrix multiplication of original * inverse = identity (mod 26)
#include <stdio.h>
#include <stdlib.h>

void makehillkey(int seed, int** hillkey_out);

int mod(int a, int m) {
    int result = a % m;
    if (result < 0) result += m;
    return result;
}

int main() {
    int order = 25;
    
    // Original matrix
    int** original = (int**)malloc(25 * sizeof(int*));
    for (int i = 0; i < 25; i++)
        original[i] = (int*)malloc(25 * sizeof(int));
    
    makehillkey(12345, original);
    
    // Inverse matrix (from the output above)
    int inverse[25][25] = {
        {3,17,19,3,15,0,21,6,19,13,22,5,14,0,14,11,11,7,3,8,22,24,4,16,9},
        {10,3,16,0,16,8,16,7,9,24,2,23,10,1,2,7,1,4,21,12,2,11,24,7,8},
        {9,1,12,25,12,4,19,0,9,4,9,4,9,22,18,25,24,10,0,9,11,4,23,2,3},
        {16,23,23,15,25,22,23,15,4,25,4,13,21,12,14,17,1,15,18,13,17,6,17,25,7},
        {3,22,16,23,12,22,6,23,8,3,13,17,2,1,10,16,24,22,8,18,15,14,21,16,2},
        {20,0,8,8,15,18,19,23,24,15,13,18,9,8,3,9,0,0,16,3,4,12,3,18,13},
        {10,15,0,18,7,21,4,21,8,8,13,10,10,2,16,20,0,9,4,0,14,14,21,0,21},
        {20,25,10,0,9,9,12,0,25,2,19,7,12,20,4,11,18,12,5,13,20,19,11,4,14},
        {22,10,21,15,11,0,9,5,12,0,20,11,0,23,17,21,24,5,6,11,11,9,25,24,8},
        {0,0,13,14,3,15,12,6,7,11,15,11,1,7,9,14,18,4,13,4,10,17,11,16,3},
        {0,21,3,12,21,2,11,0,18,17,13,25,21,4,17,13,13,10,0,16,24,18,9,21,8},
        {17,12,6,4,21,25,19,20,5,11,24,23,14,10,6,17,24,7,19,4,13,5,22,14,10},
        {3,7,17,3,13,7,22,3,18,15,9,10,0,21,0,24,22,19,4,18,21,0,8,21,5},
        {17,24,20,4,0,10,20,12,1,16,24,14,9,22,8,19,6,6,2,0,15,11,6,8,19},
        {25,12,8,22,12,10,9,21,22,22,22,15,6,9,6,18,12,22,3,10,11,13,9,17,12},
        {25,9,24,16,2,11,12,4,4,9,9,22,5,5,3,17,2,3,5,18,2,9,2,8,5},
        {18,16,19,8,2,19,12,3,16,9,3,7,16,5,3,2,10,15,15,17,25,8,7,10,15},
        {19,3,7,21,1,3,2,14,8,16,9,17,20,13,14,11,18,20,10,24,12,6,9,15,6},
        {13,18,10,1,23,5,13,18,9,21,23,25,16,22,3,23,9,9,23,12,14,19,2,11,16},
        {12,18,24,16,16,13,10,11,7,22,7,20,15,5,0,15,3,7,4,24,14,25,4,10,14},
        {14,4,19,8,19,24,21,17,25,20,21,13,0,10,23,13,2,1,9,10,16,13,2,5,11},
        {1,5,11,13,7,3,18,17,4,14,23,19,20,20,1,11,24,3,25,3,20,23,7,21,11},
        {2,21,13,7,2,18,16,16,0,20,21,15,4,6,19,3,24,22,4,3,10,9,15,13,4},
        {10,23,13,14,5,12,25,6,16,20,13,11,5,2,24,12,17,10,24,9,21,13,11,20,3},
        {24,0,12,12,18,22,14,18,17,1,8,14,24,12,9,16,14,10,21,14,16,12,1,1,17}
    };
    
    // Result matrix
    int** result = (int**)malloc(25 * sizeof(int*));
    for (int i = 0; i < 25; i++)
        result[i] = (int*)malloc(25 * sizeof(int));
    
    // Multiply original * inverse
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            int sum = 0;
            for (int k = 0; k < 25; k++) {
                sum = (sum + original[i][k] * inverse[k][j]) % 26;
            }
            result[i][j] = mod(sum, 26);
        }
    }
    
    // Check if result is identity matrix
    printf("Verification: Original * Inverse (mod 26):\n");
    int is_identity = 1;
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            printf("%d ", result[i][j]);
            if (i == j && result[i][j] != 1) is_identity = 0;
            if (i != j && result[i][j] != 0) is_identity = 0;
        }
        printf("\n");
    }
    
    if (is_identity) {
        printf("\n✓ SUCCESS: The inverse is correct! Result is the identity matrix.\n");
    } else {
        printf("\n✗ ERROR: The inverse is incorrect. Result is not the identity matrix.\n");
    }
    
    // Free memory
    for (int i = 0; i < 25; i++) {
        free(original[i]);
        free(result[i]);
    }
    free(original);
    free(result);
    
    return 0;
}

// Copy makehillkey function from matrix_inverse.c
void makehillkey(int seed, int** hillkey_out) {
    srand(seed);

    int L[25][25] = {0};
    int U[25][25] = {0};

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j <= i; j++) {
            if (i == j) {
                L[i][j] = 1;
            } else {
                L[i][j] = rand() % 26;
            }
        }
    }

    for (int i = 0; i < 25; i++) {
        for (int j = i; j < 25; j++) {
            if (i == j) {
                int val = (rand() % 25) + 1;
                while (val % 2 == 0 || val % 13 == 0) {
                    val = (rand() % 25) + 1;
                }
                U[i][j] = val;
            } else {
                U[i][j] = rand() % 26;
            }
        }
    }

    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 25; j++) {
            int sum = 0;
            for (int k = 0; k < 25; k++) {
                sum = (sum + L[i][k] * U[k][j]) % 26;
            }
            hillkey_out[i][j] = sum;
        }
    }
}
