/*

GLOB

Given: Two protein strings s and t in FASTA format (each of length at most 1000 aa).

Return: The maximum alignment score between s and t. Use:

The BLOSUM62 scoring matrix.
Linear gap penalty equal to 5 (i.e., a cost of -5 is assessed for each gap symbol).

Finally, we've reached a task where we have a to implement one of the most famous bioinformatics algorithms using dynamic programming.
The Needleman-Wunsch algorithm!
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

    std::string PATH = "GLOB_INP.txt";
    std::vector<std::vector<std::string>> fasta = parse_FASTA(PATH);

    std::string s = fasta[0][1];
    std::string t = fasta[1][1];
    
    // Parameters
    int gap_penalty { 5 };
    auto [blosum62, residueToIndex] = createBlosum62();

    int n = s.size();
    int m = t.size();

    std::vector<std::vector<int>> score_mat(n+1, std::vector<int>(m+1));

    for(int i = 0; i<n+1; i++){
        score_mat[i][0] = -(i*gap_penalty);
    };

    for(int j = 0; j<m+1; j++){
        score_mat[0][j] = -(j*gap_penalty);
    };

    std::printf("INITIALIZED SCORING MATRIX\n\n");

    print_mat(score_mat);
    std::cout << std::endl;

    std::printf("FILLING SCORING MATRIX\n\n");

    for(int i=1; i<(n+1); i++) {
        for(int j=1; j<(m+1); j++) {

            char s_char = s[i-1];
            char t_char = t[j-1];
            int s_idx = residueToIndex[s_char];
            int t_idx = residueToIndex[t_char];

            // Scores for the three courses of action: align, gap s and gap t.
            int aln_score = score_mat[i-1][j-1]+blosum62[s_idx][t_idx];
            int gap_t_score = score_mat[i-1][j] - gap_penalty;
            int gap_s_score = score_mat[i][j-1] - gap_penalty;

            int max_score = std::max(aln_score, std::max(gap_t_score, gap_s_score));

            score_mat[i][j] = max_score;

        };
    };

    print_mat(score_mat);
    std::cout << std::endl;

    std::printf("THE MAX ATTAINABLE SCORE IS {%i}.\n\n", score_mat[n][m]);


    return 0;
}
