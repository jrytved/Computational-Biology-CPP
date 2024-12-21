/*
ID: REAR

Given: A collection of at most 5 pairs of permutations, all of which have length 10.
Return: The reversal distance between each permutation pair.

Intuition for solution

1) Generate possible reversal until a solution is encountered. Increment i for each reversal.
2) Return i when a solution is encountered.

*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <queue>
#include <set>
#include <algorithm>


void printvec(const std::vector<int> &vec) {
    for(const auto val : vec) {
        std::cout << val;
    };
    std::cout << std::endl;
};
  
int main(void) {
    std::vector<std::vector<int>> data(0, std::vector<int>(0));

    // Load data
    const std::string path = "./REAR_INP.txt";
    std::ifstream infile(path);

    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream lineStream(line);
            std::vector<int> row;
            int val;

            while (lineStream >> val) {
                row.push_back(val);
            }

            if (!row.empty()) {
                data.push_back(row);
            }
        }
    } else {
        std::cerr << "Couldn't open file!";
    }

    std::printf("SUCCESSFULLY LOADED DATA\n\n");

    for (const auto &row : data) {
        for (const auto &val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    const int n_pairs = data.size() / 2;
    std::printf("There are %i pairs of sequences to be compared\n", n_pairs);

    for (int i = 0; i < data.size(); i += 2) {
        std::printf("--------------------------------------------\n");

        const std::vector<int> seq1 = data[i];
        const std::vector<int> seq2 = data[i + 1];

        printvec(seq1);
        printvec(seq2);

        std::printf("--------------------------------------------\n");
    }
};