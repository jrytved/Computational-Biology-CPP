/*
CONV

Given: Two multisets of positive real numbers S1 and S2. The size of each multiset is at most 200.

Return: The largest multiplicity of S1⊖S2, as well as the absolute value of the number x maximizing (S1⊖S2)(x) (you may return any such value if multiple solutions exist).
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "RYTVED_UTILS.hpp"
#include <unordered_map>
#include <cmath>

double roundToPrecision(double value, int precision) {
    double factor = std::pow(10.0, precision);
    return std::round(value * factor) / factor;
};


int main(void){


    // Loading Data From File

    std::string path = "./CONV_INP.txt";
    std::ifstream file(path);

    std::vector<std::vector<double>> data;

    if(file.is_open()) {

        std::string line;

        while(std::getline(file, line)) {

            if (line.empty()) continue;

            std::vector<double> dataline(0);
            double num;

            std::istringstream iss(line);

            while(iss >> num) {
                dataline.push_back(num);
            };

            data.push_back(dataline);

        };

    } else {

        std::cerr << "File couldn't be opened!\n";
        return 0;
    };  

    // Outputting data

    int dataline_counter { 0 };

    for(auto dataline : data) {
        std::printf("CONTENTS OF DATALINE %i\n", dataline_counter);

        for(double val : dataline) {
            std::printf("%f ", val);
        };

        std::printf("\n");

        dataline_counter++;
    };

    // Initializing Matrix Of Doubles For Minkowski Sum

    int n = data[0].size();
    int m = data[1].size();

    std::vector<std::vector<double>> minkowski_matrix(n, std::vector<double>(m));

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) {
            minkowski_matrix[i][j] = data[0][i] - data[1][j];
        };
    };

    std::cout << std::endl;

    print_mat(minkowski_matrix, 6);

    std::unordered_map<double, int> frequency_map;

    for(auto row : minkowski_matrix) {
        for(double val : row) {
            double rounded_val = roundToPrecision(val, 5);
            frequency_map[rounded_val]++;
        };
    };

        // Find the number with the maximum frequency
    double most_frequent { 0 };
    int max_count = 0;

    for (const auto& [num, count] : frequency_map) {
        if (count > max_count) {
            max_count = count;
            most_frequent = num;
        }
    }

    std::printf("%.5f occurs %i times.\n", most_frequent, max_count);

    std::printf("FORMATTED OUTPUT:\n\n%i\n%.5f\n",max_count,most_frequent);

    return 0;




};