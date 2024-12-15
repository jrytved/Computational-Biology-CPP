/*
Given: An RNA string s
 having the same number of occurrences of 'A' as 'U' and the same number of occurrences of 'C' as 'G'. The length of the string is at most 300 bp.

Return: The total number of noncrossing perfect matchings of basepair edges in the bonding graph of s
, modulo 1,000,000.
*/

#include "FASTAParser.hpp"
#include <vector>
#include <string>
#include <iostream>

int main(void){

    std::cout << "INITIALIZING PROGRAM CAT: NUMBER OF NON-CROSSING PERFECT MATCHINGS OF BASEPAIR EDGES" << std::endl;

    std::vector<std::vector<std::string>> fasta = parse_FASTA("./CAT_INP.txt");
    std::vector<std::string> sequences(0);

    for (auto line : fasta) {
        std::string seq = line[1];
        sequences.push_back(seq);
        std::cout << "Loaded sequence: " << seq << std::endl;
    };



};