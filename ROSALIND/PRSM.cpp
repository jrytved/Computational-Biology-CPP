/*
Given: A positive integer n followed by a collection of n protein strings s1, s2, ..., sn and a multiset R
of positive numbers (corresponding to the complete spectrum of some unknown protein string).

Return: The maximum multiplicity of R⊖S[sk] taken over all strings sk, followed by the string sk
for which this maximum multiplicity occurs (you may output any such value if multiple solutions exist).

*/

#include <fstream>
#include <sstream>

#include <iostream>
#include <vector>
#include <string>

#include <unordered_map>

#include <cmath>

std::unordered_map<char, double> aa_masses = {
        {'A', 71.03711},
        {'C', 103.00919},
        {'D', 115.02694},
        {'E', 129.04259},
        {'F', 147.06841},
        {'G', 57.02146},
        {'H', 137.05891},
        {'I', 113.08406},
        {'K', 128.09496},
        {'L', 113.08406},
        {'M', 131.04049},
        {'N', 114.04293},
        {'P', 97.05276},
        {'Q', 128.05858},
        {'R', 156.10111},
        {'S', 87.03203},
        {'T', 101.04768},
        {'V', 99.06841},
        {'W', 186.07931},
        {'Y', 163.06333}
};


double round_to_five_places(double value) {
    const double factor = 1e5; // 10^5 for 5 decimal places
    return std::round(value * factor) / factor;
};

std::vector<double> gen_prefixes(std::string s, std::unordered_map<std::string, double> &memo){

    // Returns a Vector Of Doubles Of Fragment Weights Of All Prefixes of (and including) s.

    //std::printf("Generated Prefix: %s\n", s.c_str());

    std::vector<double> weights;

    double current_frag_weight {0};

    if(s.size()==1){
        return {aa_masses[s[0]]};
    };

    // If we can't find the fragment in the memo:
    if(memo.find(s) == memo.end()) {


        for(char res : s) {
            current_frag_weight += aa_masses[res];
        };

        memo[s] = current_frag_weight;

    } else {
        current_frag_weight = memo[s];
    };

    weights = {current_frag_weight};

    std::string pfx = s.substr(0, s.size()-1);

    for(double prev_frags : gen_prefixes(pfx, memo)) {
        weights.push_back(prev_frags);
    };

    return weights;

};


std::vector<double> gen_suffixes(std::string s, std::unordered_map<std::string, double> &memo){

    // Returns a Vector Of Doubles Of Fragment Weights Of All Suffixes of (and including) s.

    std::vector<double> weights;

    double current_frag_weight {0};

    if(s.size()==1){
        return {aa_masses[s[0]]};
    };

    // If we can't find the fragment in the memo:
    if(memo.find(s) == memo.end()) {


        for(char res : s) {
            current_frag_weight += aa_masses[res];
        };

        memo[s] = current_frag_weight;

    } else {
        current_frag_weight = memo[s];
    };

    weights = {current_frag_weight};

    std::string pfx = s.substr(1, s.size());

    for(double prev_frags : gen_suffixes(pfx, memo)) {
        weights.push_back(prev_frags);
    };

    return weights;

};

void gen_complete_spectrum(std::vector<double> R, std::vector<std::string> seqs, std::unordered_map<std::string, double> memo) {

    // Generates the complete spectrum (weights of all prefixes and suffixes) of all sequences in the string vector seq.
    // Appends all weights to the same output vector (out_vector)
    // Uses an unordered map for memoization of fragments

    std::vector<double> spectrum(0);

    std::string highest_multiplicity_string = "";

    int highest_multiplicity { 0 };

    for(std::string seq : seqs) {

        std::unordered_map<double, int> multiplicity_counts(0);

        std::vector<double> pfxs = gen_prefixes(seq, memo);
        std::vector<double> sfxs = gen_suffixes(seq, memo);

        // Concat Prefixes And Suffixes Into One Vector
        std::vector<double> complete = pfxs; 
        complete.insert(complete.end(), sfxs.begin(), sfxs.end());

        // Calculate Multiplicity

        for(int i=0; i<R.size(); i++){
            for(int j=0; j<complete.size(); j++){

                double rounded_val = round_to_five_places(R[i]-complete[j]);

                int multiplicity = multiplicity_counts[rounded_val] += 1;

                if(multiplicity >= highest_multiplicity) {
                    highest_multiplicity = multiplicity;
                    highest_multiplicity_string = seq;
                };

            };
        };
    };

    std::printf("HIGHEST MULTIPLICITY: %i\n", highest_multiplicity);
    std::printf("HIGHEST MULTIPLICITY STRING: %s\n", highest_multiplicity_string.c_str());

};


int main(void){

    std::string path = "./PRSM_INP.txt";

    std::ifstream file(path);
    
    int n {};
    std::vector<std::string> seqs(0);
    std::vector<double> masses(0);

    if(file.is_open()) {

        std::string line {};

        std::getline(file, line);
        std::istringstream iss(line);

        iss >> n;

        int counter {0};

        while(counter < n){

            std::getline(file, line);
            seqs.push_back(line);
            counter++;
        };

        while(std::getline(file, line)){
            double val;
            std::istringstream iss(line);
            iss >> val;
            masses.push_back(val);
        };



    } else {
        std::cerr << "Problem opening file!\n";
    };

    std::printf("Number of protein strings: %i\n", n);

    for(auto seq : seqs){
        std::printf("String: %s\n", seq.c_str());
    };

    for(auto mass : masses){
        std::printf("Mass: %f\n", mass);
    }; 

    std::string test_str = "KEKPKEKPKEKP";

    std::unordered_map<std::string, double> fragment_memo;

    std::vector<double> pfxes = gen_prefixes(test_str, fragment_memo);
    std::vector<double> sfxes = gen_suffixes(test_str, fragment_memo);

    std::printf("Generated %li prefixes and %li suffixes\n", pfxes.size(), sfxes.size());

    gen_complete_spectrum(masses, seqs, fragment_memo);


};