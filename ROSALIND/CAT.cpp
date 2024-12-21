/*
Given: An RNA string s
 having the same number of occurrences of 'A' as 'U' and the same number of occurrences of 'C' as 'G'. The length of the string is at most 300 bp.

Return: The total number of noncrossing perfect matchings of basepair edges in the bonding graph of s
, modulo 1,000,000.

Reccurence relation : cn = sum[k=1 -> k=n] (c_(k-1) * c_(n-k))

*/

const int MOD = 1000000;

#include "FASTAParser.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <map>

bool base_pair_matches(char a, char b) {

    // Ret true if RNA-base pairing is possible (A :: U, G :: C). Ret false otherwise.

    return (((a=='A' && b=='U') || (a=='U' && b == 'A'))) || (((a=='G' && b=='C') || (a=='C' && b == 'G')));

};


long long count_nc_perfect_matchings(int start, int end, const std::string &seq, std::vector<std::vector<long long>> &memo) {

    // Base Case
    if (start >= end){return 1;};

    // Values that have already been calculated are saved in memo. Values that are not, are set to (-1) at the beginning.
    if(memo[start][end] != -1) {
        return memo[start][end];
    };

    long long total { 0 };

    // Iterate over all possible 

    for(int k=start+1; k<end+1; k+=2) {

        char start_base = seq[start];
        char end_base = seq[k];

        if(base_pair_matches(start_base, end_base)) {

            long long left = count_nc_perfect_matchings(start+1, k-1, seq, memo);
            long long right = count_nc_perfect_matchings(k+1, end, seq, memo);

            total += left*right;
            total %= MOD;
        };

    };

    memo[start][end] = total;
    return total;
};




int main(void){

    std::cout << "INITIALIZING PROGRAM CAT: NUMBER OF NON-CROSSING PERFECT MATCHINGS OF BASEPAIR EDGES" << std::endl;

    std::vector<std::vector<std::string>> fasta = parse_FASTA("./CAT_INP.txt");
    std::vector<std::string> sequences(0);

    for (auto line : fasta) {
        std::string seq = line[1];
        sequences.push_back(seq);
        std::cout << "Loaded sequence: " << seq << std::endl;
    };

    std::string seq = sequences[0];

    int n = seq.size();

    std::vector<std::vector<long long>> memo(n, std::vector<long long>(n, -1));
    memo[0][0] = 1;

    int res = count_nc_perfect_matchings(0, n-1, seq, memo);

    std::printf("THERE ARE %i PERFECT NON-CROSSING MATCHINGS\n", res);

};