#include <vector>
#include <string>
#include "FASTAParser.hpp"
#include <iostream>
#include <fstream>

/*
EXERCISE KMP. The Failure Array Or Longest Prefix Suffix Array.

A prefix of a string (char array) s of length n is a substring [1:j] and a suffix is a substring [k:n].

The failure array (or LPS array) is an array P of length n, for which P[k] is the longest substring terminating at k, s[j:k]
that is equal to some prefix s[1:k-j+1]. j cannot equal 1, as p[k] would then always equal k (if we allow substrings of length k beginning at 1, then that would always equal
to a prefix of length k.). By convention, P[1] = 0;

General Idea:

For any k, we begin iterating over the string starting from [k:j] from the back (for the suffix) and from [0:k-j+1] for the prefix

E.g. for k=6

<-j--k Suffix 
CAGCATGGTATCACAGCAGAG
0-j>

It seems like we can optimize the construction in terms of how many comparison operations we need
to perform, by considering the parity of k.

Case 1: k is uneven:

k//2 = 3

We need to check for matches between subsequnces of increasing length terminating at
all indices in [0:j-1] and [j+1:k] respectively. Considering the last character is
superfluous.

oooXooo
ABCDEFG

case 2: k is even
m = k/2 = 3

We need to check for matches between subsequences of increasing length terminating at
all indices in [0:m-1] and [m:k] respectively. 

oooooo
ABCDEF

*/


std::vector<int> generate_lps_array_slow(std::string& seq) {

    
    // This was my initial idea for a possible algorithm. Even though the approach is simple, it is not optimized and runs in O(n^2) time.

    unsigned seqlen = seq.size();
    std::vector<int> lps_array(seqlen, 0);
    lps_array[0] = 0;
    unsigned count { 0 };

    for(int k=2; k<=seqlen; k++){

        std::printf("%i out of %i\n", k, seqlen);

        // Zero-based index.
        //std::cout << "String up to " << k << " is: " << seq.substr(0,k) << std::endl;

        for(int j=0; j<(k/2); j++) {

            std::string pfx = seq.substr(0, j+1);
            std::string sfx = seq.substr(k-(j+1), (j+1));

            if (pfx == sfx) {
                count = (j+1);
            } 
        };
        // Add the max. LPS to the lps_array and reset the counter for the next k.
        lps_array[k-1] = count;
        //std::cout << "Longest LPS (prefix-suffix) is : " << seq.substr(0, count) << " - " << seq.substr(k-count, count) << std::endl << std::endl;
        count = 0;

    };

    return lps_array;

}

std::vector<int> generate_lps_array_fast(std::string seq) {

    // This is a much faster approach without a nested-loop.
    // This implementation uses the fact that 

    int n = seq.size();
    std::vector<int> lps(n, 0); // Initialize LPS array with 0
    int length = 0; // Length of the previous longest prefix suffix

    for (int i = 1; i < n; ++i) {
        // Match the current character with the character at `length`
        while (length > 0 && seq[i] != seq[length]) {
            length = lps[length - 1]; // Backtrack to the previous LPS value
        }

        // If there's a match, extend the prefix length
        if (seq[i] == seq[length]) {
            ++length;
        }

        lps[i] = length; // Assign the value to the LPS array
    }

    return lps;

};

int main(void){

    std::vector<std::vector<std::string>> fasta = parse_FASTA("./KMP_INP.txt");
    std::vector<std::string> sequences(0);

    for(std::vector<std::string> line : fasta) {
        sequences.push_back(line[1]);
    };

    std::string seq = sequences[0];

    std::cout << "Constructing LPS-array for sequence" << std::endl;

    // CALCULATING THE LPS-ARRAY

    

    // OUTPUT THE LPS-ARRAY

    std::vector<int> lps_array = generate_lps_array_fast(seq);

    std::string outfile = "./KMP_OUT.txt";
    
    std::ofstream OutputFile(outfile);

    for(int val : lps_array) {
        OutputFile << val << " ";
    };

    OutputFile.close();

    std::cout << "Program terminated. File output to : " << outfile << std::endl;
};