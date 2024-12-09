#include <iostream>
#include <string>

/*

ROSALIND EXERCISE
ID: LEXP

Given: A collection of at most 10 symbols defining an ordered alphabet, and a positive integer n (n≤10).

Return: All strings of length n that can be formed from the alphabet, ordered lexicographically.

Example output:

AA
AC
AG
AT
CA
CC
CG
CT
GA
GC
GG
GT
TA
TC
TG
TT


This exercise asks us to select all k-size subset of the A-size alphabet and return them lexicographically sorted.

What is the expected number of outputs? :: This relates to alphabet size A and k-mer size k, by k^(A).

Approach 1 :: Recursive Solution

    The first idea that comes to mind is to implement a recursive solution of the general form:

    For each letter in the set, call the function kmer_recur(letter, k, set)
    where letter is the letter, k is the length of the wanted subsets and set is the set.

    kmer_recur performs the following ::
    
        if k > 1 then it calls itself len(set) times, passing the value:

            kmer_recur(concat(letter, set[i]), k-1, set)

        if k == 1 then it prints the now full k-length string:

            std::cout << letter

    
    It should be apparent from this, that as the recursion expands, each initial letter will be contenated with all possible
    combinations of the len(alphabet) remaining letters, to yield a length k string. Because we call the recursive function in the chronological/
    lexicographically sorted order of the original alphabet (in terms of parameter letter), the returned k-length subsets/strings will always
    be sorted accordingly.

    If we wanted to return the strings in reverse-lexicographical order, we could call the original function on a reversed copy of
    the alphabet string.
    

*/

void k_mer_recur(std::string str, int k, std::string alphabet) {


    if (k == 1) {
        std::cout << str << std::endl;

    } else {

        for (int i=0; i < alphabet.length(); i++) {

            k_mer_recur(str+alphabet[i], (k-1), alphabet);
        }

    };

};

int main(void) {

    std::string str, alphabet { "ABCDEFGHI" };

    int k { 3 };

    for (int i = 0; i < alphabet.length(); i++) {

        k_mer_recur(alphabet.substr(i, 1), k, alphabet);
    }

    return 0;
}