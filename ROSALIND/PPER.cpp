/*

ID: PPER

Given: Positive integers n and k such that 100≥n>0 and 10≥k>0.

Return: The total number of partial permutations P(n,k), modulo 1,000,000.

Intuition: A partial permutation of a set with parameters (n, k) is the number of ordered arrangements of
a subset of size k, from a set of size n.

If we choose any element i from the original set of size |S|=n, we now have (n-1) elements, and we now need to choose
another (k-1) elements to complete our subset. We continue this untill the subset is of size |s|=k.

A general solution is the equation n!/(n-k)!. Consider n=10 and k=4. Then n-k = 10-4 = 6.We only want to calculate 10*9*8*7.

(10*9*8*7*6*5*4*3*2*1)/(6*5*4*3*2*1)= (10*9*8*7).


*/

#include <iostream>

unsigned long long partial_permutations(int n, int k) {


    unsigned long long result { 1 };

    for (int i = 0; i<k; ++i) {

        result *= (n-i); 

    }

    return result;

};

int main(void) {

    int n { 96 };
    int k { 9 };

    unsigned long long result = partial_permutations(n, k) % 1000000;

    std::printf("The number of partial permutations for parameters n: %i and k: %i is %llu", n, k, result);

}
