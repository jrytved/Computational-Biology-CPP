/*
PROBLEM ID: FULL
*/

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include <deque>
#include <algorithm>
#include <cmath>

double round_to_decimal_places(double value, int decimalPlaces) {
    double scale = std::pow(10, decimalPlaces);
    return std::round(value * scale) / scale;
}

// MAP OF MONOISOTOPIC VALUES OF A.A. WEIGHTS

std::map<double, char> aa_masses = {
    {71.03711, 'A'},
    {103.00919, 'C'},
    {115.02694, 'D'},
    {129.04259, 'E'},
    {147.06841, 'F'},
    {57.02146, 'G'},
    {137.05891, 'H'},
    {113.08406, 'L'}, // Note: 'I' and 'L' have the same mass; 'L' is retained.
    {128.09496, 'K'},
    {131.04049, 'M'},
    {114.04293, 'N'},
    {97.05276, 'P'},
    {128.05858, 'Q'},
    {156.10111, 'R'},
    {87.03203, 'S'},
    {101.04768, 'T'},
    {99.06841, 'V'},
    {186.07931, 'W'},
    {163.06333, 'Y'}
};



int read_data(std::string& fname, std::vector<double>& data) {

    std::ifstream inputFile(fname);

    if (!inputFile) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // Read values from the file
    double value;

    while (inputFile >> value) {
        data.push_back(value); // Add the value to the vector
    }

    inputFile.close(); // Close the file

    return 1;

};

std::vector<std::string> asm_peptide(double parent, std::vector<double> children, std::vector<std::string> peptide, int n){

    // If the peptide has grown to the target size, return it.

    std::printf("PEPSIZE IS: %li AND N IS: %i\n", peptide[0].size(), n);

    if(peptide[0].size() == n) {
        return peptide;
    };

    int n_children = children.size();
    std::vector<std::vector<int>> BY_IONS(0, std::vector<int>(0));
    std::vector<char> CANDIDATES(0);
    
    // Pick all children masses from (i=0 : n_children-1) and subtract all children masses from (j=i+1 : n_children). 
    // If the difference between these two numbers maps to a known amino acid mass, we push [i, j] to BY_IONS and the matching aa (char) to CANDIDATES.

    for(int i=0; i<(n_children-1); i++){

        for(int j=i+1; j<n_children; j++) {

            std::printf("Comparing idx. %i to idx. %i\n", i, j);

            double mass_diff = children[j] - children[i];
            double mass_diff_rounded = round_to_decimal_places(mass_diff, 5);

            bool matches_aa_mass = (aa_masses.find(mass_diff_rounded) == aa_masses.end())? false : true;

            if(matches_aa_mass) {
                
                std::printf("Mass %f corresponds to aa %c\n", mass_diff_rounded, aa_masses[mass_diff_rounded]);

                BY_IONS.push_back({i, j});
                CANDIDATES.push_back(aa_masses[mass_diff_rounded]);
            };

        };

    };

    // We now have two arrays in play. BY_IONS contains all [i, j] for those matches for which the difference is the match of an amino acid.
    // We also have CANDIDATES, which contains all the chars (amino acids) corresponding to these mass differences.

    // If we have found any candidate amino acids, then BY_IONS will contain at least one element.

    if (BY_IONS.size() > 0) {

        // We then take the index of the first mass that gave us an amino acid when subtracted from some i.

        int new_j = BY_IONS[0][1];

        // And subset the old children vector, to only include elements [j:]
        std::vector<double> new_children(children.begin()+new_j, children.end());

        // The corresponding amino acid of that mass difference is copied into char :: new_aa.
        char new_aa = CANDIDATES[0];

        std::printf("New AA to be added: %c\n", new_aa);

        // We then copy the existing peptide into variable new peptide.
        std::vector<std::string> new_peptide = peptide;

        // And concat the found aa into all elements of the existing peptide.

        for(std::string &pep : new_peptide) {
            pep += new_aa;
            std::cout << "ADDED NEW AA TO PEP" << std::endl;
        };

        for(std::string pep : new_peptide) {
            std::printf("New pepseq: %s\n", pep.c_str());
        };

        // Now we recursively call the function again, to further assemble the peptide, using new_children as the children and new_peptide as the peptide.
        peptide = asm_peptide(parent, new_children, new_peptide, n);

    };

    return peptide;

};

int main(void) {

    std::vector<double> data(0);
    
    std::string fname = "./FULL_INP.txt";
    read_data(fname, data);

    double parent_mass = data[0];   // Copy the parent mass into another
    data.erase(data.begin());       // Remove the parent mass from the data.

    int n = data.size();

    std::vector<double> children = data;

    std::printf("Printing Dataset:\n");

    for(double val : data) {
        std::cout << val << " | ";
    };

    std::cout << std::endl;
    std::printf("ASSEMBLING PEPTIDE FROM DATA\n");

    std::vector<std::string> start_pep(0);
    start_pep.push_back("");

    int target_n = (children.size()-2) / 2;

    std::vector<std::string> peptide = asm_peptide(parent_mass, children, start_pep, target_n);

    for(std::string pepseq : peptide) {
        std::printf("Possible peptide sequence: %s\n", pepseq.c_str());
    };
    

};