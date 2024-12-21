#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>


void gen_lexv(const std::vector<char> &alphabet, int n, std::string current, std::vector<std::string> &result) {

    if(current.size() > n){return;};

    if(current.size() > 0){
        result.push_back(current);
    };

    for (char letter : alphabet) {
        gen_lexv(alphabet, n, current+letter, result);
    };

};

int main() {

    std::string path = "LEXV_INP.txt";
    std::ifstream file(path);
    std::vector<char> alphabet; // Declare alphabet vector
    int sz = 0;                 // Declare size variable

    // Parsing the file
    if (file.is_open()) {
        // Read letters
        char letter;
        while (file >> letter) {
            if (std::isalpha(letter)) { // Only add alphabetic characters
                alphabet.push_back(letter);
            } else {
                // If it's not a letter, break and assume it's the number
                file.unget(); // Put the non-letter character back for next read
                break;
            }
        }

        // Read the number
        file >> sz;

        file.close();
    } else {
        std::cerr << "Failed to open file.\n";
        return 1;
    }

    // Output parsed data
    std::printf("Generating lex. sorted permutations of length %i from the following alphabet:\n", sz);

    for (char letter : alphabet) {
        std::printf("%c ", letter);
    }
    std::cout << std::endl;

    std::vector<std::string> result(0);

    std::string initial = "";

    gen_lexv(alphabet, sz, initial, result);

    std::ofstream outfile;

    outfile.open("LEXV_OUT.txt");

    for(std::string perm : result) {
        outfile << perm << std::endl;
    };

    outfile.close();

    return 0;
}
