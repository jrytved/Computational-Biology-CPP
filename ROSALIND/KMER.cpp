/*
ID: KMER

Given: A DNA string s in FASTA format (having length at most 100 kbp).

Return: The 4-mer composition of s

This problem is easily solved by sliding a size 4 window over the entire sequence (thus generating all possible 4-mers). We then retrieve the
positiion in the size 4^4=256 lexicographically sorted array by computation, rather by looping and comparison.

*/

#include "FASTAParser.hpp"
#include <string>
#include <vector>
#include <iostream>
#include<cmath>

std::vector<std::string> generate_n_mers(std::string& s, int kmer_size) {
    unsigned sz = s.size();
    std::vector<std::string> output_arr(0);

    for(int i=0; i<=(sz-kmer_size); i++){
        output_arr.push_back(s.substr(i, kmer_size));
    };

    return output_arr;

};

int get_index(char c) {

    switch(c) {
        case 'A':
            return 0;
        case 'C':
            return 1;
        case 'G':
            return 2;
        case 'T':
            return 3;
        default:
            return 9;
    };

};

int lexicographical_position(std::string& s) {

    // For a string of length k=4 composed of letters of the sorted alphabet {A, C, G, T} returns it's lexicographical position in a sorted array of all k(4)-mers.

    int result { 0 };

    for(int i=0; i<(4);i++){
        
        char current_char = s[i];
        int current_idx = get_index(current_char);

        result += current_idx*(pow(4, (4-1-i)));
    }

    return result;

};

int main(void) {

    int n_k_mers = 256; // We can make 4*4*4*4 = 256 k-mers from the four letter (DNA) alphabet.

    std::vector<std::vector<std::string>> fasta = parse_FASTA("./KMER_INP.txt");
    std::vector<std::string> sequences(0);
    std::vector<std::string> kmer_array(0);
 
    for (auto line : fasta) {
        std::string seq = line[1];
        sequences.push_back(seq);
        std::cout << "Loaded sequence: " << seq << std::endl;
    };

    kmer_array = generate_n_mers(sequences[0], 4);

    std::vector<int> comp_arr(0);

    unsigned counter { 0 };
    std::string prev = kmer_array[0];
    std::vector<int> composition(n_k_mers);

    for(const std::string kmer : kmer_array) {
        std::cout << kmer << std::endl;
    };  

    for(std::string& kmer : kmer_array) {

        int pos = lexicographical_position(kmer);
        composition[pos]++;
    };


    for(int c : composition) {
        std::cout << c << " ";
    };

    std::cout << std::endl;

};
