/*
ALGORITHM: GENERAL MAXIMUM STRING OVERLAP


two strings s1, s2, in such a way that the number of characters matched is maximal.
This algorithm finds the general maximum overlap between two strings. That is, the algorithm finds the way to align
For example, given s1 = CATG and s2 = ATGCATC, the optimal way to align the two is:

We can solve the problem by two loops. The first compares prefixes of s1 to suffixes of s2, with these being of length
min(s1, s2). The second inverses the operation

*/

#include "FASTAParser.hpp"
#include <iostream>
#include <string>
#include <algorithm>  // For std::min

std::string GENERAL_MAXIMUM_STRING_OVERLAP(const std::string& s1, const std::string& s2) {
    // Get the lengths of both strings
    int l1 = s1.size();
    int l2 = s2.size();

    // We only need to check up to the smallest string length
    int shortest_len = std::min(l1, l2);

    int max = 0;  // Track the maximum overlap length
    std::string overlap;  // Track the resulting overlap string

    // First loop: Compare suffixes of s1 with prefixes of s2
    for (int i = 1; i <= shortest_len; ++i) {
        std::string s1_sub = s1.substr(l1 - i, i);  // Suffix of s1
        std::string s2_sub = s2.substr(0, i);       // Prefix of s2

        if (s1_sub == s2_sub && i > max) {
            max = i;
            overlap = s1 + s2.substr(i);  // Combine the strings by removing the overlap from s2
        }
    }

    // Second loop: Compare suffixes of s2 with prefixes of s1
    for (int i = 1; i <= shortest_len; ++i) {
        std::string s1_sub = s1.substr(0, i);       // Prefix of s1
        std::string s2_sub = s2.substr(l2 - i, i);  // Suffix of s2

        if (s1_sub == s2_sub && i > max) {
            max = i;
            overlap = s2 + s1.substr(i);  // Combine the strings by removing the overlap from s1
        }
    }

    // If no overlap was found, simply return the concatenation of s1 and s2
    if (max == 0) {
        overlap = s1 + s2;
    }

    return overlap;
}
