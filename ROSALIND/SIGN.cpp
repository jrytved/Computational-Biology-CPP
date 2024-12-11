/*


A signed permutation of length n is some ordering of the positive integers {1,2,…,n}
in which each integer is then provided with either a positive or negative sign.
For example, π=(5,−3,−2,1,4) is a signed permutation of length 5. 

Given: A positive integer n≤6. 
Return: The total number of signed permutations of length n, followed by a list of all such permutations (in any order).

Intuition:

For any integer n we have set S for which |S|=n. We can make n! permutations of size k of this set. 
For any resultant size k set, S', |S'|=k, we have a binary choice for each element, to either sign it or unsigning.
We therefore have 2^n possible signings of the set.

So we have the general solution:

n!*2^n

For example, for n=2:

2! * 2^2 = 2*4 = 8.

Next, we have to actually print all the signed permutations. To first generate all the possible permutations, we can use an array.

*/

#include <iostream>
#include <cmath>
#include <vector>

unsigned long long factorial(int n) {


    unsigned long long result { 1 };

    for (int i = 0; i<n; ++i) {

        result *= (n-i); 

    }

    return result;

};

void heapPermutation(std::vector<int>& arr, int n, std::vector<std::vector<int>>& permutations) {
    // If n becomes 1, we store the current permutation
    if (n == 1) {
        permutations.push_back(arr);
        return;
    }

    // Recur for generating permutations
    for (int i = 0; i < n; i++) {
        heapPermutation(arr, n - 1, permutations);

        // If n is odd, swap the first and last element
        // If n is even, swap the ith and last element
        if (n % 2 == 1) {
            std::swap(arr[0], arr[n - 1]);
        } else {
            std::swap(arr[i], arr[n - 1]);
        }
    }
};

void generateSignedVersions(const std::vector<int>& arr, std::vector<std::vector<int>>& result, std::vector<int> current, int index) {
    // If we've processed all elements, add the current signed version to the result
    
    if (index == arr.size()) {
        result.push_back(current);
        return;
    }

    // For each element, try both its positive and negative version

    // Keep the element as it is
    current.push_back(arr[index]);
    generateSignedVersions(arr, result, current, index + 1);

    // Change the sign of the element (negate it)
    current.back() = -arr[index];
    generateSignedVersions(arr, result, current, index + 1);
};


int main(void) {

    int n { 3 };

    unsigned long long result = factorial(n) * std::pow(2, n);
    std::cout << result << std::endl;

    std::vector<int> arr(0);

    for(int i=0; i<n; i++) {
        arr.push_back((i+1));
    };

    std::vector<std::vector<int>> permutations;
    std::vector<std::vector<int>> signed_versions;



    heapPermutation(arr, n, permutations);

    int n_permutations = permutations.size();

    for (const auto& permutation : permutations) {

        signed_versions.clear();
        generateSignedVersions(permutation, signed_versions, {}, 0);

        for (const auto& version: signed_versions) {

            for (const auto& integer : version) {
                std::cout << integer << " ";
            };

            std::cout << std::endl;

        };
    };
};