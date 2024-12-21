/*
ID: SSET

Given: A positive integer n (n≤1000).

Return: The total number of subsets of {1,2,…,n} modulo 1,000,000.

Intuition: For any element i of the subset S that has size |S|=n, we have the binary choice
of inclusion or exclusion from a possible subset. We keep in mind that any set is a subset
of itself, and that the empty set, Ø, is a subset of any set. By this logic, the number of subset
of a set of size n is 2^n.

n | number of subsets
0 | 2^0=1 (The empty set = the set itself is the only subset)
1 | 2^1 = 2 (The empty set, and the set itself are the only two subset)
2 | 2^2 = 4 (The set containing either of the two elements alone, the set containing both elements and finally Ø!)

And so on and so forth!

*/

#include <iostream>
#include <cmath>


const int MOD = 1000000;

int modular_exponentiation(int base, int exponent, int mod) {
    long long result = 1;
    long long base_mod = base % mod;

    while (exponent > 0) {
        // If the current exponent bit is 1, multiply result with base_mod
        if (exponent % 2 == 1) {
            result = (result * base_mod) % mod;
        }
        // Square the base and reduce it modulo mod
        base_mod = (base_mod * base_mod) % mod;
        // Divide the exponent by 2
        exponent /= 2;
    }
    return static_cast<int>(result);
}

int main() {
    int n = 823;

    // Calculate (2^n) % 1000000
    int result = modular_exponentiation(2, n, MOD);

    std::cout << result << '\n';
    return 0;
}