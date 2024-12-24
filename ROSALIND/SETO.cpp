/*

Given: A positive integer n (n≤20,000) and two subsets A and Bof {1,2,…,n}.

Return: Six sets:

A∪B, A∩B, A−B, B−A, Ac, and Bc (where set complements are taken with respect to {1,2,…,n}).

*/

#include <set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "RYTVED_UTILS.hpp"
#include <limits>

std::set<int> union_set(std::set<int> a, std::set<int> b){

    std::set<int> set_union = a;

    for(const int &number : b) {
        if(not a.count(number)) {
            set_union.insert(number);
        };
    };
    return set_union;
};

std::set<int> intersect_set(std::set<int> a, std::set<int> b){

    std::set<int> set_intersection = {};

    for(const int &number : b) {

        if(a.count(number)) {
            set_intersection.insert(number);
        };
    };

    return set_intersection;
};

std::set<int> subtract_set(std::set<int> a, std::set<int> b){

    std::set<int> set_subtracted = {};

    std::set<int> intersection = intersect_set(a, b);

    for(const int &number : a) {

        if(not intersection.count(number)) {
            set_subtracted.insert(number);
        };
    };

    return set_subtracted;
};


void print_set(const std::set<int>& a) {
    std::cout << "{";

    // Use an iterator to access the elements of the set
    for (auto it = a.begin(); it != a.end(); ++it) {
        std::cout << *it;
        if (std::next(it) != a.end()) { // Check if this is not the last element
            std::cout << ", ";
        }
    }

    std::cout << "}";
    std::cout << std::endl;
};

void output_set(const std::set<int>& a, std::string path) {

    std::ofstream outfile(path, std::ios::app);

    if(outfile.is_open()) {

            outfile << "{";

            // Use an iterator to access the elements of the set
            for (auto it = a.begin(); it != a.end(); ++it) {
                outfile << *it;
                if (std::next(it) != a.end()) { // Check if this is not the last element
                    outfile << ", ";
                }
            }

            outfile << "}";
            outfile << std::endl;

    } else {
        std::cerr << "Output file couldn't be opened!\n";
    };

};

int main(void){


    // Open the file
    std::ifstream infile("SETO_INP.txt");
    if (!infile) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    // Read the first line as an integer
    int n;
    infile >> n;
    infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line

    // Define sets to store integers
    std::set<int> a, b;

    // Helper function to read a line of integers into a set
    auto readSet = [](std::istream& stream, std::set<int>& s) {
        std::string line;
        if (std::getline(stream, line)) {
            std::stringstream ss(line);
            char ch;
            int num;
            while (ss >> ch >> num) { // Skip non-numeric characters and read numbers
                s.insert(num);
            }
        }
    };

    // Read the next two lines into sets a and b
    readSet(infile, a);
    readSet(infile, b);

    // Close the file
    infile.close();

    std::set<int> u = {};

    for(int i=1; i<=n; i++){
        u.insert(i);
    };

    
    std::printf("RESULTS\n\n\n");

    std::string outpath = "SETO_OUT.txt";

    std::ofstream file(outpath);
    file.close();

    //std::printf("SET UNION\n");
    std::set<int> UNION = union_set(a,b);
    output_set(UNION, outpath);

    //std::printf("SET INTERSECTION\n");
    std::set<int> INTERSECTION = intersect_set(a,b);
    output_set(INTERSECTION, outpath);

    //std::printf("SET (A-B) \n");
    std::set<int> AMINB = subtract_set(a, b);
    output_set(AMINB, outpath);

    //std::printf("SET (B-A) \n");
    std::set<int> BMINA = subtract_set(b, a);
    output_set(BMINA, outpath);

    //std::printf("SET (Ac) \n");
    std::set<int> AC = subtract_set(u, a);
    output_set(AC, outpath);

    //std::printf("SET (Bc) \n");
    std::set<int> BC = subtract_set(u, b);
    output_set(BC, outpath);

};