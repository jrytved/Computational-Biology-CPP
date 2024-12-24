/*
Given: An RNA string s of length at most 300 bp.

Return: The total number of noncrossing matchings of basepair edges in the bonding graph of s, modulo 1,000,000.

Ideas for solving.

Consider we have s='AUAU'.

We have the recurrence relation:

    m_n := m_{n-1} + sum_{k=2}^{n}{m_{k-2}*m_{n-k}}

    and the base condition m_0=m_1=0;

Two things immediately come apparent: 1) A recursive solution is in place and 2) we likely need to apply memoization for performance,
as we will be calculating similar values again and again.

We also need to consider in the solution, that we can only allow base-pairs (edges) A :: U and G :: C. Therefore the problem fails to be solved analytically,
and we need to compute, as the result depends on the content of symbols in the RNA-string.


*/

const int MOD = 1000000;

#include "FASTAParser.hpp"
#include <string>
#include <vector>
#include <iostream>


bool base_pair_matches(char a, char b) {

    // Ret true if RNA-base pairing is possible (A :: U, G :: C). Ret false otherwise.

    return (((a=='A' && b=='U') || (a=='U' && b == 'A'))) || (((a=='G' && b=='C') || (a=='C' && b == 'G')));

};

void print_bonding_string(std::string s, int i, int j) {

    // Prints the string s with symbols representing a bond from base i to base j.

    for(char base : s){
        std::cout<<base<<"|";
    };

    std::cout << std::endl;

    for(int k=0; k<s.size(); k++){

        std::string symbol {};

        if(k<i) {
            symbol = " ";
        };

        if((k>i) && (k<j)) {
            symbol = "━";
        };

        if(k==i) {
            symbol = "┗";
        };

        if(k==j){
            symbol = "┛";
        };

        std::printf("%s ", symbol.c_str());

    };

    std::cout << std::endl;
    std::cout << std::endl;

};


long long count_nc_perfect_matchings(int start, int end, const std::string &seq, std::vector<std::vector<long long>> &memo) {

    // Base Case
    if (start >= end){return 1;};

    // Values that have already been calculated are saved in memo. Values that are not, are set to (-1) at the beginning.
    if(memo[start][end] != -1) {
        return memo[start][end];
    };

    long long total { 0 };

    memo[start][end] = count_nc_perfect_matchings(start+1, end, seq, memo);

    // Iterate over all possible 

    for(int k=start+1; k<end+1; k++) {

        char start_base = seq[start];
        char end_base = seq[k];

        if(base_pair_matches(start_base, end_base)) {
            
            // Only print the bonding string for small inputs, otherwise prog. will take forever:)
            //print_bonding_string(seq, start, k);

            long long left = count_nc_perfect_matchings(start+1, k-1, seq, memo);
            long long right = count_nc_perfect_matchings(k+1, end, seq, memo);
            memo[start][end] += (left*right);
        };

    };

    memo[start][end] %= MOD;

    return memo[start][end];
};



int main(void) {

    std::string path = "./MOTZ_INP.txt";
    std::vector<std::vector<std::string>> fasta = parse_FASTA(path);
    std::string seq = fasta[0][1];

    int n = seq.size();

    std::printf("COMPUTING ALL NON-CROSSING-NON-PERFECT MATCHING ON BONDING GRAPH OF SEQUENCE:\n%s\n\n", seq.c_str());

    std::vector<std::vector<long long>> memo(n, std::vector<long long>(n, -1));
    memo[0][0] = 1;

    long long res = count_nc_perfect_matchings(0, n-1, seq, memo);

    std::printf("\nRESULT: %lli\n", res);




}

