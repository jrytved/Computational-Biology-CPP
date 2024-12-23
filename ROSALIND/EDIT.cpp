/*
EDIT

Given: Two protein strings s and t in FASTA format (each of length at most 1000 aa).
Return: The edit distance dE(s,t).

Operations are deletions, substitutions or insertions. 

*/

#include <vector>
#include <string>
#include "FASTAParser.hpp"
#include <iostream>
#include <algorithm>


int main(void){
    std::string path = "./EDIT_INP.txt";
    std::vector<std::vector<std::string>> fasta = parse_FASTA(path);

    // Load two first sequences into own vars.
    std::string s = fasta[0][1];
    std::string t = fasta[1][1];

    int n = s.size();
    int m = t.size();

    std::vector<std::vector<int>> score_mat(n+1, std::vector<int>(m+1));

    // Initialize Boundary Conditions (Deletions of i or j characters from one or the other string)

    for(int i=0; i<n+1; i++) {
        score_mat[i][0] = i;
    };

    for(int j=0; j<m+1; j++) {
        score_mat[0][j] = j;
    };

    // Printing formatted Scoring Matrix

    std::printf("CALCULATING EDIT DISTANCE BETWEEN {%s} and {%s}\n\n", s.c_str(), t.c_str());

    for(int i=1;i<(n+1); i++){
        for(int j=1;j<(m+1);j++){

            score_mat[i][j] = (s[i-1]==t[j-1])? score_mat[i-1][j-1] :
            1 + std::min(score_mat[i-1][j-1], std::min(score_mat[i-1][j], score_mat[i][j-1]));

        };
    };


    for (auto col : score_mat) {
        for(auto val : col) {
            std::printf("%3d", val);
        };
        std::cout << std::endl;
    };

    std::cout << "----------------------------" << std::endl;
    std::printf("Minimum Edit Distance is %i\n", score_mat[n][m]);
    std::cout << "----------------------------" << std::endl << std::endl;

    



}