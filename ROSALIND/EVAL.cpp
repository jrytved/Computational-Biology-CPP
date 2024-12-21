#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

int main(void) {
    std::string path = "./EVAL_INP.txt";

    std::ifstream file(path);

    if (!file) {
        std::cerr << "Unable to load file!\n";
        return 0;
    };

    int n;
    std::string s;
    std::vector<float> gc_contents;

    // Read the first line as an integer
    file >> n;

    // Read the second line as a string
    file >> s;

    // Read the remaining lines as floats
    float value;
    while (file >> value) {
        gc_contents.push_back(value);
    }

    file.close();

    if (s.size() > n) {
        std::cerr << "Error: Length of substring s is greater than n.\n";
        return 0;
    }

    int valid_positions = n - s.size() + 1;

    int ngc = 0, nat = 0;

    for (char base : s) {
        if ((base == 'G') || (base == 'C')) {
            ngc++;
        } else if ((base == 'A') || (base == 'T')) {
            nat++;
        }
    }

    std::vector<double> result;

    for (auto gc_content : gc_contents) {
        double prob_gc = gc_content / 2;
        double prob_at = (1 - gc_content) / 2;

        // Use logarithms for better numerical stability
        double log_prob_motif = ngc * std::log(prob_gc) + nat * std::log(prob_at);
        double prob_motif = std::exp(log_prob_motif);

        result.push_back(prob_motif * valid_positions);
    }

    for (const auto& res : result) {
        std::printf("%.3f ", res);
    }

    return 0;
}
