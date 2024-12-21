#include <iostream>
#include <vector>

const int MOD = 1000000;

// Function to compute C(n, k) using dynamic programming
std::vector<std::vector<int>> compute_binomial_coeff(int n) {
    std::vector<std::vector<int>> C(n + 1, std::vector<int>(n + 1, 0));
    for (int i = 0; i <= n; ++i) {
        C[i][0] = 1; // Base case: C(i, 0) = 1
        for (int j = 1; j <= i; ++j) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD; // Pascal's rule
        }
    }
    return C;
}

int main() {
    int n = 1895; // Replace with input
    int m = 645; // Replace with input

    // Precompute all binomial coefficients up to n
    std::vector<std::vector<int>> C = compute_binomial_coeff(n);

    // Calculate the sum of C(n, k) for m <= k <= n
    long long result = 0;
    for (int k = m; k <= n; ++k) {
        result = (result + C[n][k]) % MOD;
    }

    std::printf("For n=%i and m=%i, the sum of combinations modulo %d is %lli\n", n, m, MOD, result);

    return 0;
}
