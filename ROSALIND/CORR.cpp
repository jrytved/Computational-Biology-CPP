#include "FASTAParser.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

std::string reverse_string(const std::string& s) {
    std::string reversed = s; // Create a copy of the input string
    std::reverse(reversed.begin(), reversed.end()); // Reverse the string in-place
    return reversed; // Return the reversed string
};

char complement_char(char base){

    switch(base){
        case 'A':
            return 'T';
        case 'C':
            return 'G';
        case 'T':
            return 'A';
        case 'G':
            return 'C';
        default:
            std::cerr << "NON CANONICAL BASE FOUND.";
            return 'X';
    }
};

std::string complement_string(const std::string& s){

    std::string complemented = s;
    unsigned n = s.size();

    for(int i=0;i<n;i++){
        complemented[i] = complement_char(s[i]);
    };

    return complemented;
};

std::string rc_string(const std::string& s){
    std::string rc = s;
    rc = reverse_string(s);
    rc = complement_string(rc);
    return rc;
};

int hamming_dist(std::string& s, std::string& t){

    int dist { 0 };

    if(s.size() != t.size()){std::cerr << "The sizes of the strings are unequal.";};

    for(int i=0;i<s.size();i++){
        if(s[i]!=t[i]){
            dist++;
        };
    };

    return dist;
};

void print_2d_mat(std::vector<std::vector<int>> mat){

    for(auto col : mat){
        for(auto val : col){
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};

void print_vector(std::vector<int> vec) {
    for (int val : vec){
        std::cout << val << " ";
    };

    std::cout << std::endl;
};

std::vector<int> count_non_identity_int(std::vector<std::vector<int>>& mat, int n, int val) {
    std::vector<int> result(n);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            // If it's not an identity and the element is equal to val, we increment i in the output vector.
            if((i!=j) && (mat[i][j] == val)){
                result[i]++;
            };
        };
    };

    return result;
};

int main(void) {

    std::vector<std::vector<std::string>> fasta_array;
    fasta_array = parse_FASTA("./CORR_INP.txt");
    std::vector<std::string> seq_array(0);
    std::vector<std::string> rc_seq_array(0);

    for (auto line : fasta_array) {
        seq_array.push_back(line[1]);
    };

    for (auto seq : seq_array) {
        rc_seq_array.push_back(rc_string(seq));
    };

    unsigned n_seqs = seq_array.size();

    std::printf("SEQS AND RC-SEQS\n");

    for(unsigned i = 0; i<n_seqs; i++){
        std::cout << seq_array[i] << "⟺" << rc_seq_array[i] << std::endl;
    };

    std::vector<std::vector<int>> dist_mat(n_seqs, std::vector<int>(n_seqs, 0));
    std::vector<std::vector<int>> rc_dist_mat(n_seqs, std::vector<int>(n_seqs, 0));

    for(int i=0;i<n_seqs;i++){
        for(int j=0;j<n_seqs;j++){
            dist_mat[i][j] = hamming_dist(seq_array[i], seq_array[j]);
            rc_dist_mat[i][j] = hamming_dist(seq_array[i], rc_seq_array[j]);
        };
    };

    std::vector<int> non_identity_zeros = count_non_identity_int(dist_mat, n_seqs, 0);
    std::vector<int> non_identity_zeros_rc = count_non_identity_int(rc_dist_mat, n_seqs, 0);
    std::vector<int> comb_non_identity_zeros(n_seqs);

    for(int i=0;i<n_seqs;i++){
        comb_non_identity_zeros[i] = non_identity_zeros[i] || non_identity_zeros_rc[i];
    };

    
    std::printf("DISTANCE MATRIX\n");
    print_2d_mat(dist_mat);

    std::printf("RC DISTANCE MATRIX\n");
    print_2d_mat(rc_dist_mat);

    std::printf("COMBINED NON-IDENTITY ZERO VECTOR\n");
    print_vector(comb_non_identity_zeros);


    // Now we have distance matrix for both comparing seq[i] to seq[j] and comparing seq[i] to the rc of seq[j].

    // For all sequences
    for(int i=0; i<n_seqs;i++){

        // If that sequence has a zero non-identity zeros, it was only found once and is incorrect.
        if(comb_non_identity_zeros[i] == 0) {

            // We will then have to compare it to all other sequences, that were correctly sequenced.
            for(int j=0; j<n_seqs;j++){

                if((comb_non_identity_zeros[j] > 0) && ((dist_mat[i][j] == 1))) {
                    std::cout << seq_array[i] << "->" << seq_array[j] << std::endl;
                    // If found, we break out of the nested loop
                    goto next_seq;
                };



                if((comb_non_identity_zeros[j] > 0) && ((rc_dist_mat[i][j] == 1))) {
                    std::cout << seq_array[i] << "->" << rc_seq_array[j] << std::endl;
                    // If found, we break out of the nested loop
                    goto next_seq;
                };

            };
        };

        next_seq:;

    };


};