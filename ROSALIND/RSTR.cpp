/*
RSTR

Given: A positive integer N≤100000, a number x between 0 and 1, and a DNA string s of length at most 10 bp.

Return: The probability that if N random DNA strings having the same length as s are constructed with GC-content x
(see “Introduction to Random Strings”), then at least one of the strings equals s.

We allow for the same random string to be created more than once.

*/

#include <vector>
#include <string>
#include <iostream>
#include <cmath>


int main(void) {

    int n = 82669;
    double gcc_raw = 0.557077;
    double gcc = gcc_raw / 2;
    double atc = (1-gcc_raw) / 2;
    std::string s = "CGAGGGTTA";

    int len = s.size();

    // We know that the GC-content is equal to 0.6. That means - on average - 60% of the nucleotides in a randomly constructed string
    // of the genome will be G or C.
    // On the contrary, we can say that the 40% - on average- should be A or T.

    int n_gc { 0 };
    int n_at { 0 };

    for(char base : s) {

        if((base == 'A') || (base == 'T')) {
            n_at++;
            continue;
        };

        if((base == 'G') || (base == 'C')) {
            n_gc++;
            continue;
        };

    };

    std::printf("What is the probability of constructing the string %s at least once, for %i randomly generated strings with GC-content %f and AC-content %f?\n", s.c_str(), n, gcc, atc);

    std::printf("There are %i G's or C's and %i A's or T's", n_gc, n_at);

    // The probability of randomly constructing the string
    double prob_str = std::pow(gcc, n_gc)*std::pow(atc, n_at);
    double prob_not_str = 1-prob_str;

    std::printf("Probability of string: %f\n", prob_str);
    std::printf("Probability of !string: %f\n", prob_not_str);

    // Use that logm^n=n*logm

    double log_prob_not_string_n_trials = std::log(prob_not_str)*n;

    double result = 1-std::exp(log_prob_not_string_n_trials);

    std::printf("Result: %.3f", result);


}

