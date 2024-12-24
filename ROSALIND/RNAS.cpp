/*
Given: An RNA string s (of length at most 200 bp).

Return: The total number of distinct valid matchings of basepair edges in the bonding graph of s.
Assume that wobble base pairing is allowed.

// We need to use boosts multiprecision lib, as we are not returning the result MOD 10^6 anymore,
// and therefore for inputs > 10 we will start to see some huge integer results, that would overflow
// a long long very quickly.

*/

const int MOD = 1000000;

#include "FASTAParser.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>


bool base_pair_matches(char a, char b) {

    // Ret true if RNA-base pairing is possible (A :: U, G :: C). Ret false otherwise.

    return (
           ((a=='A' && b=='U') || (a=='U' && b == 'A'))\
        || ((a=='G' && b=='C') || (a=='C' && b == 'G'))\
        || ((a=='G' && b=='U') || (a=='U' && b == 'G'))\
        
    );

};


boost::multiprecision::cpp_int count_nc_perfect_matchings(int start, int end, const std::string &seq, std::vector<std::vector<boost::multiprecision::cpp_int>> &memo) {

    // Base Case
    if (start >= end){return 1;};

    // Values that have already been calculated are saved in memo. Values that are not, are set to (-1) at the beginning.
    if(memo[start][end] != -1) {
        return memo[start][end];
    };

    boost::multiprecision::cpp_int total { 0 };

    memo[start][end] = count_nc_perfect_matchings(start+1, end, seq, memo);

    // Iterate over all possible matchings.
    // The new constraint that differs from the exercise with ID: MOTZ, is that we now only look at
    // possible base pairs between bases that are 4 bases apart!

    for(int k=start+4; k<end+1; k++) {

        char start_base = seq[start];
        char end_base = seq[k];

        if(base_pair_matches(start_base, end_base)) {
            
            // Only print the bonding string for small inputs, otherwise prog. will take forever:)
            //print_bonding_string(seq, start, k);

            boost::multiprecision::cpp_int left = count_nc_perfect_matchings(start+1, k-1, seq, memo);
            boost::multiprecision::cpp_int right = count_nc_perfect_matchings(k+1, end, seq, memo);
            
            memo[start][end] += (left*right);
        };

    };

    return memo[start][end];
};



int main(void) {

    std::string path = "./RNAS_INP.txt";
    std::vector<std::vector<std::string>> fasta = parse_FASTA(path);
    std::string seq = fasta[0][1];

    int n = seq.size();

    std::printf("COMPUTING ALL NON-CROSSING-NON-PERFECT MATCHING ON BONDING GRAPH OF SEQUENCE:\n%s\n\n", seq.c_str());

     std::vector<std::vector<boost::multiprecision::cpp_int>> memo(n, std::vector<boost::multiprecision::cpp_int>(n, -1));

    memo[0][0] = 1;

    boost::multiprecision::cpp_int res = count_nc_perfect_matchings(0, n-1, seq, memo);

    std::cout << res << std::endl;




}

