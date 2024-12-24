#ifndef RYTVED_UTILS_HPP
#define RYTVED_UTILS_HPP

#include <vector>
#include <iomanip>
#include <iostream>
#include <type_traits> // For std::is_same

template <typename T>
void print_mat(const std::vector<std::vector<T>> &mat, int w) {
    for (const auto &row : mat) {
        for (const auto &val : row) {
            // Adjust formatting based on type
            if constexpr (std::is_same<T, char>::value) {
                std::cout << std::setw(w) << val << ' '; // Align characters
            } else {
                std::cout << std::setw(w) << val << ' '; // Align numbers
            }
        }
        std::cout << std::endl;
    }
}

#endif // RYTVED_UTILS_HPP
