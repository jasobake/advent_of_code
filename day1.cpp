#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <cmath>
#include <unordered_map>

int main() {
    std::ifstream input_file("day1_input.txt");

    if (!input_file) {
        std::cerr << "Error opening file" << std::endl;
        return EXIT_FAILURE;
    }

    std::string line{};

    // refactored from a vector since we know the size
    std::array<int, 1000> column1{};
    std::array<int, 1000> column2{};

    int first{0};
    int col1_val{0};
    int col2_val{0};

    // part 2
    std::unordered_map<int, int> count_hash;

    size_t counter{0};
    while (std::getline(input_file, line)) {
        //part 1 calc
        first = line.find(' ');
        col1_val = std::stoi(line.substr(0, first));
        col2_val = std::stoi(line.substr(first + 1, line.length() - first - 1));
        column1[counter] = col1_val;
        column2[counter] = col2_val;
        ++counter;

        //part 2 calc
        count_hash[col2_val]++;
    }

    // this brings overall time complexity to O(n log n)
    std::sort(column1.begin(), column1.end());
    std::sort(column2.begin(), column2.end());

    int result_part1{0};
    int result_part2{0};

    // because I'm trying to learn more about C++23 ranges
    for (const auto& [ c1, c2 ] : std::ranges::views::zip(column1, column2)) {
        //part 1 calc
        result_part1 += std::abs(c2 - c1);

        // part 2 calc
        result_part2 += count_hash[c1] * c1;
    }

    input_file.close();

    std::cout << "result 1: " << result_part1 << std::endl;
    std::cout << "result 2: " << result_part2 << std::endl;

    return EXIT_SUCCESS;
}
