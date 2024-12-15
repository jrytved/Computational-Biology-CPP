/*
EXERCISE ID: SPEC
*/

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>

// MAP OF MONOISOTOPIC VALUES OF A.A. WEIGHTS

std::map<char, double> aminoAcidMasses = {
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

std::vector<char> amino_acids = {'A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'Y'};


bool within_tolerance(double a, double b, double tolerance){

    if (fabs(a-b) < tolerance) {
        return true;
    };

    return false;
}

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

void print_2d_mat(std::vector<std::vector<double>> mat) {

    for (std::vector<double> col : mat) {
        for (double val : col) {
            std::printf("%09.5f", val);
            std::cout << " ";
        };

        std::cout << std::endl;
    };

    return void();
}


int main(void){

    std::vector<double> data(0);
    std::string fname = "./SPEC_INP.txt";
    read_data(fname, data);

    int n = data.size();

    std::vector<double> aa_mass_vec(0);
    std::vector<char> seq(0);

    for(int i=0; i<(n-1); i++) {
        double diff = data[i+1]-data[i];

        for (char aa : amino_acids) {
            double mass = aminoAcidMasses[aa];

            if(within_tolerance(diff, mass, 0.005)) {
                seq.push_back(aa);
                break;
            };
        };
    };

    for (char aa : seq) {
        printf("%c", aa);
    };

    std::cout << std::endl;

};