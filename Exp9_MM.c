#include <stdio.h>
#include <limits.h>

// Function to find the minimum number of multiplications
void matrixChainOrder(int p[], int n) {
    int m[n][n];

    // Initialize the cost of multiplying one matrix as zero
    for (int i = 1; i < n; i++)
        m[i][i] = 0;

    // Fill the table for chains of length L
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++) {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }

    printf("Minimum number of multiplications is %d\n", m[1][n - 1]);
}

int main() {
    int arr[] = {1, 2, 3, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    matrixChainOrder(arr, n);
    return 0;
}
