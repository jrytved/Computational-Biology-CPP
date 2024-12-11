#include "FASTAParser.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>

// Use a larger type for memoization to avoid overflow
std::vector<long long> factorial_cache;

long long memoized_factorial(int n) {
    if (n < 0) {
        throw std::invalid_argument("Factorial is not defined for negative numbers.");
    }

    // Ensure the cache is large enough
    if (factorial_cache.size() <= n) {
        factorial_cache.resize(n + 1, -1); // Resize and initialize with -1 (means not computed)
    }

    // If factorial is already computed, return the cached value
    if (factorial_cache[n] != -1) {
        return factorial_cache[n];
    }

    // Base case: 0! = 1 and 1! = 1
    if (n == 0 || n == 1) {
        factorial_cache[n] = 1;
        return 1;
    }

    // Otherwise, calculate and store the result in cache
    factorial_cache[n] = n * memoized_factorial(n - 1);
    return factorial_cache[n];
}

int main(void) {
    int na { 0 };
    int nc { 0 };
    int ng { 0 };
    int nu { 0 };

    auto sequences = parse_FASTA("PMCH_INP.txt");

    // Use the FASTA-parser to load in the single sequence.
    std::string sequence = sequences[0][1];

    for (int i = 0; i < sequence.size(); i++) {
        switch (sequence[i]) {
            case 'A':
                na++;
                break;
            case 'C':
                nc++;
                break;
            case 'G':
                ng++;
                break;
            case 'U':
                nu++;
                break;
            default:
                std::cerr << "An unrecognized character: " << sequence[i] << " was found." << std::endl;
        }
    }

    std::printf("The sequence contains the following counts :: A: %i, C: %i, G: %i, U: %i.\n", na, nc, ng, nu);

    if (!(na == nu) || !(nc == ng)) {
        std::cerr << "Bases A:U and G:C are not present in equivalent numbers." << std::endl;
    }

    // Now prints the result for the matchings, which should handle large values correctly
    std::printf("There are %lld possible unique matchings on the graph.\n", memoized_factorial(na) * memoized_factorial(nc));

    return 0;
}
