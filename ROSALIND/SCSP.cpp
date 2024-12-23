#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main() {

    std::string path = "SCSP_INP.txt";
    std::ifstream file(path);

    std::vector<std::string> stringarr;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line))
            stringarr.push_back(line);
    } else {
        std::cerr << "Unable to open file!\n";
        return 1;
    }

    std::string s = stringarr[0];
    std::string t = stringarr[1];

    std::printf("Finding shortest common supersequence of %s and %s.\n", s.c_str(), t.c_str());

    // Find the Longest Common Subsequence (LCS)
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

    // Construct the Shortest Common Supersequence (SCS)
    std::string SCS = "";
    i = 0; // Pointer for string s
    j = 0; // Pointer for string t
    
    int k = 0; // Pointer for LCS

    while (k < LCS.size()) {
        while (i < s.size() && s[i] != LCS[k]) {
            SCS += s[i++];
        }
        while (j < t.size() && t[j] != LCS[k]) {
            SCS += t[j++];
        }
        // Add LCS character and move pointers
        SCS += LCS[k++];
        ++i;
        ++j;
    }

    // Append remaining characters from s and t
    while (i < s.size()) {
        SCS += s[i++];
    }
    while (j < t.size()) {
        SCS += t[j++];
    }

    std::printf("THE SHORTEST COMMON SUPERSEQUENCE IS: %s\n", SCS.c_str());

    return 0;
}
