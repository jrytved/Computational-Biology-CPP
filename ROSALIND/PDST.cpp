/*
EXERCISE ID: PDST
*/

#include "FASTAParser.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

float p_dist(std::string& s, std::string& t, int sz){

    // Returns proportion of differing symbols between s and t when |s|=|t|.

    int dist { 0 };

    for(int i=0; i<sz; i++) {
        (s[i]!=t[i])? dist++ : 0;
    };

    return (float(dist)) / (float(sz));
};

std::vector<std::vector<float>> p_dist_matrix(std::vector<std::string> &sequences) {

    int n = sequences.size();
    int size = sequences[0].size();

    std::vector<std::vector<float>> dist_matrix(n, std::vector<float>(n, 0));

    for(int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            dist_matrix[i][j] = p_dist(sequences[i], sequences[j], size);
        };
    };

    return dist_matrix;

};

int main(void) {

    std::vector<std::vector<std::string>> fasta = parse_FASTA("./PDST_INP.txt");
    std::vector<std::string> sequences(0);

    // Copy sequences to sequences (omits headers)
    for (auto &line : fasta) {
        sequences.push_back(line[1]);
    };

    std::vector<std::vector<float>> dist_matrix = p_dist_matrix(sequences);

    std::string outfile = "./PDST_OUT.txt";

    std::ofstream OutputFile(outfile);

    for (auto col : dist_matrix) {
        for(auto row : col) {
            OutputFile << row << " ";
        };
        OutputFile << std::endl;
    };

    OutputFile.close();

};