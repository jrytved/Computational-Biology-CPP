/*
ID: REAR

Given: A collection of at most 5 pairs of permutations, all of which have length 10.
Return: The reversal distance between each permutation pair.

Intuition for solution

An initial idea for this problem is to:

1) Generate possible reversal until a solution is encountered. Increment i for each reversal.
2) Return i when a solution is encountered.

However, the time complexity of such an algorithm would be enormous. We can make a much faster solution by using two tricks:

1) Use a hash-table to check for already visited permutations.
2) Use an A* star search, by which we can trade the time complexity of for a greater memory complexity.
   Specifically, we can guide the search by a heuristic, in which we start by further reversing the strings
   with the fewest out of place elements. This search heuristic *massively* decreases the time complexity!
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <queue>
#include <unordered_set>
#include <algorithm>

// Hash Function For Vectors

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        size_t hash = 0;
        for (int x : v) {
            hash = hash * 31 + std::hash<int>()(x);  // Combine hashes
        }
        return hash;
    }
};


void printvec(const std::vector<int> &vec) {
    std::cout << "|";
    for(const auto val : vec) {
        std::cout << val;
        std::cout << "|";
    };
    std::cout << std::endl;
};

std::vector<int> reverse_segment(const std::vector<int>& perm, int i, int j) {

    // Reverses the subsequence [i:j] of the vector. Leaves the remaining el. of the vector as-is.

    std::vector<int> result = perm;
    std::reverse(result.begin() + i, result.begin() + j + 1);
    return result;
};

struct AStarNode {
    std::vector<int> permutation;
    int g_cost;  // Cost to reach this state
    int h_cost;  // Heuristic estimate to the target

    int f_cost() const {
        return g_cost + h_cost;  // Total cost estimate (g + h)
    }
};

struct CompareNode {
    bool operator()(const AStarNode& a, const AStarNode& b) {
        return a.f_cost() > b.f_cost();
    }
};

int heuristic(const std::vector<int>& current, const std::vector<int>& target) {
    int misplaced = 0;
    for (int i = 0; i < current.size(); ++i) {
        if (current[i] != target[i]) {
            ++misplaced;
        }
    }
    return misplaced;  // Number of misplaced elements
}

int find_rev_dist_a_star(std::vector<int> a, std::vector<int> b) {
    int n = a.size();
    std::unordered_set<std::vector<int>, VectorHash> visited;
    std::priority_queue<AStarNode, std::vector<AStarNode>, CompareNode> pq;

    // Start with the initial permutation, g_cost = 0, and heuristic estimate
    pq.push({a, 0, heuristic(a, b)});
    visited.insert(a);

    while (!pq.empty()) {
        auto [current, g_cost, h_cost] = pq.top();
        pq.pop();

        // Check if we've reached the target
        if (current == b) {
            std::cout << "SOLUTION FOUND!\n";
            printvec(current);
            printvec(b);
            return g_cost;
        }

        // Generate all possible new states by reversing segments
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                // Reverse the segment [i, j]
                std::vector<int> neighbor = reverse_segment(current, i, j);
                
                // If we haven't visited this state, add it to the queue and mark it as visited
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    pq.push({neighbor, g_cost + 1, heuristic(neighbor, b)});
                }
            }
        }
    }

    return -1;  // This should not be reached if there's always a solution
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

    // Print Data

    for (const auto &row : data) {
        printvec(row);
        std::cout << std::endl;
    }

    const int n_pairs = data.size() / 2;
    std::printf("There are %i pairs of sequences to be processed\n", n_pairs);

    for (int i = 0; i < data.size(); i += 2) {
        std::printf("--------------------------------------------\n");

        const std::vector<int> seq1 = data[i];
        const std::vector<int> seq2 = data[i + 1];

        printvec(seq1);
        printvec(seq2);

         std::cout << find_rev_dist_a_star(seq1, seq2);

        std::printf("--------------------------------------------\n");
    };

};