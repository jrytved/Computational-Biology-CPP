#include "FASTAParser.hpp"
#include <iostream>
#include <fstream>

// Function implementation
std::vector<std::vector<std::string>> parse_FASTA(const std::string& file_name) {
    std::vector<std::vector<std::string>> string_arr;
    std::ifstream inputFile(file_name);

    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return string_arr;
    }

    std::string line;
    std::string header;
    std::string sequence;

    while (std::getline(inputFile, line)) {
        if (line.empty()) {
            continue; // Skip empty lines
        }
        if (line[0] == '>') {
            if (!header.empty() && !sequence.empty()) {
                string_arr.push_back({header, sequence});
                sequence.clear();
            }
            header = line.substr(1); // Store header without '>'
        } else {
            sequence += line; // Append sequence
        }
    }

    if (!header.empty() && !sequence.empty()) {
        string_arr.push_back({header, sequence});
    }

    return string_arr;
}
