/*
This problem is solved by dynamic programming, and even has a generic name: The Nussinov Algorithm!
*/

#include <string>
#include <vector>
#include <iostream>
#include "FASTAParser.hpp"

bool base_pair_allowed(const char &a, const char &b) {
    return ((a == 'A' && b == 'U') || (a == 'U' && b == 'A')) || ((a == 'G' && b == 'C') || (a == 'C' && b == 'G'));
};



int main(void) {

    std::vector<std::vector<std::string>> fasta = parse_FASTA("./MMCH_INP.txt");

    std::string seq = fasta[0][1];
    int n = seq.size();


    std::printf("Generating Optimal Base Pairing for string: %s\n", seq.c_str());

    std::vector<std::vector<int>> scoring_mat(n, std::vector<int>(n));



};