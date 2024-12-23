/*

GCON

Given: Two protein strings s and t in FASTA format (each of length at most 1000 aa).

Return: The maximum alignment score between s and t. Use:

The BLOSUM62 scoring matrix.
Constant gap penalty equal to 5.

This problem is identical to the problem 'GLOB' except now the gap penalty will be 5 regardless of the length of the gap.

We therefore need to make two changes: 
1) when initializing the scoring matrix the non-zero index elements of the first row and column should no longer
be i*gap_penalty or j*gap_penalty respectively, but just equal to the gap penalty.

2) When considering the max score for each cell, we should only add the gap penalty if a new gap is being opened.
   That is, if the previous best score came from opening a gap, we don't need to penalize further extension of the gap.
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include "FASTAParser.hpp"
#include <vector>
#include <string>
#include <algorithm>

// Utility Function To Print Score And Backtracking Matrix

void print_mat(const std::vector<std::vector<int>> &mat){

    for(auto col : mat){
        for(auto val : col) {
            std::printf("%4d ", val);
        };
        std::cout << std::endl;
    };

};

// Hash Map For Converting A Residue To It's Index in The Blosum62 Scoring Matrix

std::pair<std::vector<std::vector<int>>, std::unordered_map<char, int>> createBlosum62() {
    // Amino acid residues
    std::string residues = "ACDEFGHIKLMNPQRSTVWY";

    // Map residues to their indices
    std::unordered_map<char, int> residueToIndex;
    for (size_t i = 0; i < residues.size(); ++i) {
        residueToIndex[residues[i]] = i;
    }

    // BLOSUM62 scores (row-major order)
    std::vector<std::vector<int>> blosum62 = {
        { 4,  0, -2, -1, -2,  0, -2, -1, -1, -1, -1, -2, -1, -1, -1,  1,  0,  0, -3, -2},
        { 0,  9, -3, -4, -2, -3, -3, -1, -3, -1, -1, -3, -3, -3, -3, -1, -1, -1, -2, -2},
        {-2, -3,  6,  2, -3, -1, -1, -3, -1, -4, -3,  1, -1,  0, -2,  0, -1, -3, -4, -3},
        {-1, -4,  2,  5, -3, -2,  0, -3,  1, -3, -2,  0, -1,  2,  0,  0, -1, -2, -3, -2},
        {-2, -2, -3, -3,  6, -3, -1,  0, -3,  0,  0, -3, -4, -3, -3, -2, -2, -1,  1,  3},
        { 0, -3, -1, -2, -3,  6, -2, -4, -2, -4, -3,  0, -2, -2, -2,  0, -2, -3, -2, -3},
        {-2, -3, -1,  0, -1, -2,  8, -3, -1, -3, -2,  1, -2,  0,  0, -1, -2, -3, -2,  2},
        {-1, -1, -3, -3,  0, -4, -3,  4, -3,  2,  1, -3, -3, -3, -3, -2, -1,  3, -3, -1},
        {-1, -3, -1,  1, -3, -2, -1, -3,  5, -2, -1,  0, -1,  1,  2,  0, -1, -2, -3, -2},
        {-1, -1, -4, -3,  0, -4, -3,  2, -2,  4,  2, -3, -3, -2, -2, -2, -1,  1, -2, -1},
        {-1, -1, -3, -2,  0, -3, -2,  1, -1,  2,  5, -2, -2,  0, -1, -1, -1,  1, -1, -1},
        {-2, -3,  1,  0, -3,  0,  1, -3,  0, -3, -2,  6, -2,  0,  0,  1,  0, -3, -4, -2},
        {-1, -3, -1, -1, -4, -2, -2, -3, -1, -3, -2, -2,  7, -1, -2, -1, -1, -2, -4, -3},
        {-1, -3,  0,  2, -3, -2,  0, -3,  1, -2,  0,  0, -1,  5,  1,  0, -1, -2, -2, -1},
        {-1, -3, -2,  0, -3, -2,  0, -3,  2, -2, -1,  0, -2,  1,  5, -1, -1, -3, -3, -2},
        { 1, -1,  0,  0, -2,  0, -1, -2,  0, -2, -1,  1, -1,  0, -1,  4,  1, -2, -3, -2},
        { 0, -1, -1, -1, -2, -2, -2, -1, -1, -1, -1,  0, -1, -1, -1,  1,  5,  0, -2, -2},
        { 0, -1, -3, -2, -1, -3, -3,  3, -2,  1,  1, -3, -2, -2, -3, -2,  0,  4, -3, -1},
        {-3, -2, -4, -3,  1, -2, -2, -3, -3, -2, -1, -4, -4, -2, -3, -3, -2, -3, 11,  2},
        {-2, -2, -3, -2,  3, -3,  2, -1, -2, -1, -1, -2, -3, -1, -2, -2, -2, -1,  2,  7}
    };

    return {blosum62, residueToIndex};
};

int main() {

    // Loading Data

    std::string PATH = "GCON_INP.txt";
    std::vector<std::vector<std::string>> fasta = parse_FASTA(PATH);

    std::string s = fasta[0][1];
    std::string t = fasta[1][1];
    
    // Parameters
    int gap_penalty { 5 };
    auto [blosum62, residueToIndex] = createBlosum62();

    int n = s.size();
    int m = t.size();

    std::vector<std::vector<int>> score_mat(n+1, std::vector<int>(m+1));
    std::vector<std::vector<char>> backtrack_mat(n+1, std::vector<char>(m+1));

    for(int i = 1; i<n+1; i++){
        score_mat[i][0] = -(gap_penalty);
    };

    for(int j = 1; j<m+1; j++){
        score_mat[0][j] = -(gap_penalty);
    };

    std::printf("INITIALIZED SCORING MATRIX\n\n");

    print_mat(score_mat);
    std::cout << std::endl;


    // Now to Fill Out The Scoring And Backtracking Matrices
    // We maintain score_mat for scores and backtrack_mat to make backtracking easier.
    // In this case we do not care about ambiguous aligments, and just choose a single alignment arbitrarily. 

    std::printf("FILLING SCORING AND BT MATRIX\n\n");

    for(int i=1; i<(n+1); i++) {
        for(int j=1; j<(m+1); j++) {

            char s_char = s[i-1];
            char t_char = t[j-1];
            int s_idx = residueToIndex[s_char];
            int t_idx = residueToIndex[t_char];

            // Scores for the three courses of action: align, gap s and gap t.
            int aln_score = score_mat[i-1][j-1]+blosum62[s_idx][t_idx];
            int gap_t_score = score_mat[i-1][j] - gap_penalty;   // Should be changed to max of vals from 0 up to i-1 minus gap
            int gap_s_score = score_mat[i][j-1] - gap_penalty;  // Should be changed to max of vals from 0 up to j-1  minus gap

            int max_score = std::max(aln_score, std::max(gap_t_score, gap_s_score));

            score_mat[i][j] = max_score;

        };
    };

    print_mat(score_mat);
    std::cout << std::endl;

    std::printf("THE MAX ATTAINABLE SCORE IS {%i}.\n\n", score_mat[n][m]);




    return 0;
}
