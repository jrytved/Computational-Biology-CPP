#include <string>
#include <vector>
#include "FASTAParser.hpp"
#include <iostream>
#include <algorithm>

void print_2d_mat_w_annot(const std::vector<std::vector<int>> &mat, const std::string &s, const std::string &t) {
    int n = s.size();
    int m = t.size();

    std::printf("    ");
    for (char c : t) std::printf(" %c", c);
    std::printf("\n");

    for (int i = 0; i <= n; ++i) {
        if (i > 0) std::printf("%c ", s[i - 1]);
        else std::printf("  ");
        for (int j = 0; j <= m; ++j) {
            std::printf("%2d", mat[i][j]);
        }
        std::printf("\n");
    }
    std::printf("\n");
}

int main(void) {
    std::string path = "./LCSQ_INP.txt";
    std::vector<std::vector<std::string>> fastas = parse_FASTA(path);

    std::vector<std::string> seqs;
    for (const auto &line : fastas) seqs.push_back(line[1]);

    std::string s = seqs[0], t = seqs[1];
    std::string LCS = "";

    int n = s.size(), m = t.size();
    std::vector<std::vector<int>> score_matrix(n + 1, std::vector<int>(m + 1, 0));
    std::vector<std::vector<char>> backtrack_matrix(n + 1, std::vector<char>(m + 1, 0));

    // Fill scoring and backtracking matrices
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (s[i - 1] == t[j - 1]) {
                score_matrix[i][j] = score_matrix[i - 1][j - 1] + 1;
                backtrack_matrix[i][j] = 'D'; // Diagonal
            } else if (score_matrix[i - 1][j] >= score_matrix[i][j - 1]) {
                score_matrix[i][j] = score_matrix[i - 1][j];
                backtrack_matrix[i][j] = 'U'; // Up
            } else {
                score_matrix[i][j] = score_matrix[i][j - 1];
                backtrack_matrix[i][j] = 'L'; // Left
            }
        }
    }

    std::printf("COMPUTED SCORING MATRIX\n");
    print_2d_mat_w_annot(score_matrix, s, t);

    // Backtrack to construct LCS
    int i = n, j = m;
    while (i > 0 && j > 0) {
        switch (backtrack_matrix[i][j]) {
            case 'D': // Diagonal
                LCS += s[i - 1];
                --i;
                --j;
                break;
            case 'U': // Up
                --i;
                break;
            case 'L': // Left
                --j;
                break;
        }
    }

    std::reverse(LCS.begin(), LCS.end());
    std::printf("THE LONGEST COMMON SUBSEQUENCE IS: %s\n", LCS.c_str());

    return 0;
}
