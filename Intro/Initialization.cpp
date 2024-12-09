#include <iostream>

/*
List initialization is the preferred way of declaring and initialing variables.
1) It works in most cases
2) It dissalows narrowing conversions
3) It supports initialization of a list of values.

If a variable is initialized with empty braces, it value-initializes to either zero or null depending on the data type.

It is good practice to use direct-list initialization only if the value will be used, and to use value-initialization otherwise.

*/

int main(void) {

    int i { 4 };
    int j { 2 };
    [[maybe_unused]] int k;         // We can prevent uninitialized variable errors by the attribute

    int arr[2] = {i, j};

    std::cout << arr[0] << std::endl;
    std::cout << arr[1] << std::endl;

    return 0;
}