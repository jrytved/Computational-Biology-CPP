#include <iostream>
#include <vector>
#include "FASTAParser.hpp"
#include "GENERAL_MAXIMUM_STRING_OVERLAP.hpp"

int main() {
    auto FASTA = parse_FASTA("LONG_INP.txt");
    std::vector<std::string> sequences;

    std::cout << "INITIATING PROGRAM: LONG.CPP";

    // Copy sequences into the vector
    for (const auto& inner_vec : FASTA) {
        sequences.push_back(inner_vec[1]);
        std::cout << "Copying sequence: " << inner_vec[1] << " to auxiliary array." << std::endl;
    }

    std::cout << "Beginning to determine the best overlapping pairs of strings..." << std::endl;

    int max_score, best_i, best_j;
    std::string best_string;

    // Continue until only two sequences remain
    while (sequences.size() > 1) {
        max_score = 0;  // Reset maximum score

        for (int i = 0; i < sequences.size(); ++i) {
            for (int j = 0; j < sequences.size(); ++j) {
                if (i == j) continue;  // Skip comparing the same string

                // Get the merged string from GENERAL_MAXIMUM_STRING_OVERLAP
                std::string merged = GENERAL_MAXIMUM_STRING_OVERLAP(sequences[i], sequences[j]);
                int score = sequences[i].size() + sequences[j].size() - merged.size(); // Calculate overlap length

                // Update the best pair if this is the largest overlap
                if (score > max_score) {
                    max_score = score;
                    best_i = i;
                    best_j = j;
                    best_string = merged;
                }
            }
        }

        // Output the merging result
        std::cout << "The best two strings are: " << sequences[best_i] << " and " << sequences[best_j]
                  << ". They merge to: " << best_string << std::endl;

        // Remove the strings from the vector (delete the largest index first)
        if (best_i > best_j) {
            sequences.erase(sequences.begin() + best_i);
            sequences.erase(sequences.begin() + best_j);
        } else {
            sequences.erase(sequences.begin() + best_j);
            sequences.erase(sequences.begin() + best_i);
        }

        // Add the merged string to the vector
        sequences.push_back(best_string);
    }

    // Output the final string
    std::cout << "The final string is: " << sequences[0] << std::endl;

    return 0;
}
