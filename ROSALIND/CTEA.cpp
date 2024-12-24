#include <vector>
#include <string>
#include "FASTAParser.hpp"
#include <iostream>
#include <algorithm>
#include <climits>

const int MOD = 134217727;  // Modulo value for the result

int count_optimal_alignments(const std::string& s, const std::string& t) {
    int m = s.size();
    int n = t.size();

    // Create the DP score matrix and alignment count matrix
    std::vector<std::vector<int>> score_mat(m + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> alignments_mat(m + 1, std::vector<int>(n + 1, 0));

    // Initialize the first row and column
    for (int i = 0; i <= m; ++i) {
        score_mat[i][0] = i;  // Deletion cost
        alignments_mat[i][0] = 1;  // There's only one way to delete all characters
    }
    for (int j = 0; j <= n; ++j) {
        score_mat[0][j] = j;  // Insertion cost
        alignments_mat[0][j] = 1;  // There's only one way to insert all characters
    }

    // Fill the DP score matrix and count alignments
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int diag = score_mat[i-1][j-1] + (s[i-1] != t[j-1]);
            int left = score_mat[i][j-1] + 1;
            int up = score_mat[i-1][j] + 1;

            // Find the minimum score for the current cell
            score_mat[i][j] = std::min({diag, left, up});

            // Count the number of ways to reach the current cell
            if (score_mat[i][j] == diag) {
                alignments_mat[i][j] = (alignments_mat[i][j] + alignments_mat[i-1][j-1]) % MOD;
            }
            if (score_mat[i][j] == left) {
                alignments_mat[i][j] = (alignments_mat[i][j] + alignments_mat[i][j-1]) % MOD;
            }
            if (score_mat[i][j] == up) {
                alignments_mat[i][j] = (alignments_mat[i][j] + alignments_mat[i-1][j]) % MOD;
            }
        }
    }

    // The number of optimal alignments is the value in the bottom-right cell of the alignment matrix
    return alignments_mat[m][n];
}

int main(void){
    std::string path = "./CTEA_INP.txt";
    std::vector<std::vector<std::string>> fasta = parse_FASTA(path);

    // Load two first sequences into own vars.
    std::string s = fasta[0][1];
    std::string t = fasta[1][1];

    // Get the number of optimal alignments and apply modulo
    int num_alignments = count_optimal_alignments(s, t);
    std::cout << "Number of optimal alignments: " << (num_alignments % MOD) << std::endl;
};
