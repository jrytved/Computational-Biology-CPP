#include <iostream>
#include <string>
/*

iostream is the input/output library of the C++-standard library.


*/

int main(void) {

    int i, j, k, m {};

    int x{ 4 };
    int y{ 12 };

    std::string test_str { "HELLO, WORLD!" };

    j = 2;
    i = 5;

    std::cout << x << std::endl << y << std::endl;

    std::cout << (i+j) << std::endl;

    std::cout << test_str << std::endl;
    std::cout << test_str << '\n';

    std::cout << "Now taking some input into k..." << '\n';
    std::cin >> k;

    std::cout << "Now taking some input into m..." << '\n';
    std::cin >> m;

    std::cout << "k equals " << k << " and m equals " << m << '\n';

    std::cout << "Now taking input into both k and m at the same time.." << '\n';
    std::cin >> k >> m;
    std::cout << "k equals " << k << " and m equals " << m << '\n';

    return 0;
}