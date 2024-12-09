#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

int LIS_RECUR(const std::vector<int>& seq, int k, std::vector<int>& memo, std::vector<int>& backtrack, bool DEC) {
    if (memo[k] != -1) return memo[k];

    int max_len = 1;
    int best_idx = -1;

    for (int j = 0; j < k; ++j) {

        if ((DEC && seq[j] > seq[k]) || (!DEC && seq[j] < seq[k])) {
            int len = LIS_RECUR(seq, j, memo, backtrack, DEC) + 1;

            if (len > max_len) {
                
                max_len = len;
                best_idx = j;
            }
        }
    }

    memo[k] = max_len;
    backtrack[k] = best_idx;
    return max_len;
}

std::vector<int> LIS_DRIVER(const std::vector<int>& seq, bool DEC) {
    int n = seq.size();
    std::vector<int> memo(n, -1);
    std::vector<int> backtrack(n, -1);

    int max_len = 0, max_idx = 0;
    for (int k = 0; k < n; ++k) {
        int len = LIS_RECUR(seq, k, memo, backtrack, DEC);
        if (len > max_len) {
            max_len = len;
            max_idx = k;
        }
    }

    // Reconstruct the subsequence
    std::vector<int> result;
    for (int idx = max_idx; idx != -1; idx = backtrack[idx]) {
        result.push_back(seq[idx]);
    }

    if (DEC) std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    std::ifstream inputFile("LGIS_INP.txt");
    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    int n;
    inputFile >> n;
    std::vector<int> seq(n);
    
    for (int i = 0; i < n; ++i) {
        inputFile >> seq[i];
    }

    auto LIS = LIS_DRIVER(seq, false);
    auto LDS = LIS_DRIVER(seq, true);

    std::reverse(LIS.begin(), LIS.end());       // We have to reverse the LIS, because ROSALIND wants it in increasing order.

    std::cout << "Longest Increasing Subsequence:\n";
    for (int num : LIS) std::cout << num << " ";
    std::cout << "\n";

    std::cout << "Longest Decreasing Subsequence:\n";
    for (int num : LDS) std::cout << num << " ";
    std::cout << "\n";

    return 0;
}
