#include <string>
#include <vector>
#include <iostream>
#include "FASTAParser.hpp"

/*
Given: Two DNA strings s and t (each of length at most 1 kbp) in FASTA format.

Return: One collection of indices of s in which the symbols of t appear as a subsequence of s.
If multiple solutions exist, you may return any one.
*/

int main(void) {

    std::vector<std::vector<std::string>> sequences;

    sequences = parse_FASTA("SSEQ_INP.txt");

    std::string s = sequences[0][1];
    std::string t = sequences[1][1];
    int size_s = s.size();
    int size_t = t.size();
    std::vector<std::vector<int>> result(0);
    std::vector<int> indices(0);

    std::cout << "The sequences are: " << s << " and " << t << std::endl;

    // We iterate over all letters in s.

    for (int i = 0; i<size_s; i++) {

        char s_letter = s[i];
        int t_idx { 0 };
        indices.clear();

        // Any position in s containing t[0] is a possible starting point for a subsequences.

        if (s_letter == t[t_idx]) {

            indices.push_back(i+1);

            t_idx++;

            for(int j = i; j<size_s; j++){

                s_letter = s[j];

                if (s_letter == t[t_idx]) {
                    std::cout << s_letter << " EQUALS " << t[t_idx] << std::endl;
                    indices.push_back(j+1);
                    t_idx++;
                };
            };
        };

        if (indices.size() == size_t) {
            result.push_back(indices);
        };
    };

    for (auto &indices : result) {

        for (int index : indices) {
            std::cout << index << " ";
        };

        std::cout << std::endl<<std::endl;

    }


}