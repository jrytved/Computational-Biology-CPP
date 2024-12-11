#include "FASTAParser.hpp"
#include <string>
#include <iostream>
#include <vector>

/*

SOLUTION ID: TRAN

*/

bool is_pyrimidine(char base) {

    // Checks if a base (character) is a pyrimidine. It is a pyrimidine if base ∈ {C, T}

    switch(base) {
        case 'C':
            return true;
            break;

        case 'T':
            return true;
            break;

        case 'A':
            return false;
            break;

        case 'G':
            return false;
            break;

        default:
            std::cerr << "Non-standard base encountered: " << base << std::endl;
            return false;
            break;
        
    }

};

bool is_purine(char base) {

    // Checks if a base (character) is a purine. It is a purine if base ∈ {A, G}

    switch(base) {
        case 'C':
            return false;
            break;

        case 'T':
            return false;
            break;

        case 'A':
            return true;
            break;

        case 'G':
            return true;
            break;

        default:
            std::cerr << "Non-standard base encountered: " << base << std::endl;
            return false;
            break;
        
    }

};

bool is_transition(char base1, char base2) {

    // It is only a transition, if both bases are purines or both bases are pyrimidines. It's a transition otherwise.

    return ((is_purine(base1) && is_purine(base2)) || (is_pyrimidine(base1) && is_pyrimidine(base2)))? true : false;
};



std::vector<int> count_transitions_transversions(std::string s1, std::string s2) {

    std::vector<int> out;

    int n_transitions { 0 };
    int n_transversions { 0 };
    int size = s1.size();

    if (!(s1.size() == s2.size())) {

        std::cerr << "The strings are not of same size.";

    };

    for (int i = 0; i<size; i++) {

        char char1 = s1[i];
        char char2 = s2[i];

        if (char1 == char2) {
                continue;
            } else {
                is_transition(char1, char2) ? n_transitions++: n_transversions++;
            };

        };


    return std::vector<int> {n_transitions, n_transversions};



};


int main(void) {

    auto sequences = parse_FASTA("TRAN_INP.txt");

    int n_transitions { 0 };
    int n_transversions { 0 };

    std::string s1 = sequences[0][1];
    std::string s2 = sequences[1][1];

    std::cout << "Beginning program TRAN. Counting the transition to transversion ratio" << std::endl;
    std::cout << "Sequence 1 is: " << s1 << std::endl;
    std::cout << "Sequence 2 is: " << s2 << std::endl;
    std::cout << "The length of the strings is: " << s1.size() << std::endl;

    std::vector<int> transversion_transition_vec = count_transitions_transversions(s1, s2);

    n_transitions = transversion_transition_vec[0];
    n_transversions = transversion_transition_vec[1];

    std::printf("There are %i transitions and %i transversions.\n", n_transitions, n_transversions);

    float transition_transversion_ratio = float(n_transitions)/float(n_transversions);

    std::printf("The transition to transversion ratio is %f\n", transition_transversion_ratio);

    return 0;
};

