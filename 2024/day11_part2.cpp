#include <iostream>
#include <unordered_map>
#include <tuple>
#include "data/day11.h"

const size_t iterations = 75;

bool is_even(uint64_t n) {
    return ((int)log10(n) + 1) % 2 == 0;
}

void split(uint64_t n, uint64_t& a, uint64_t& b) {
    int divisor = (int)pow(10, ((int)log10(n) + 1) / 2);

    a = n / divisor;
    b = n % divisor;
}

struct TupleHash {
    std::size_t operator()(const std::tuple<uint64_t, size_t>& t) const {
        const uint64_t& a = std::get<0>(t);
        const size_t& b = std::get<1>(t);

        // Combine the hash of both elements
        std::size_t seed = std::hash<uint64_t>{}(a);
        seed ^= std::hash<size_t>{}(b) + 0x9e3779b9 + (seed << 6) + (seed >> 2);

        return seed;
    }
};

std::unordered_map<std::tuple<uint64_t, size_t>, size_t, TupleHash> memo;

uint64_t check(uint64_t n, size_t iteration) {
    std::tuple t = std::make_tuple(n, iteration);
    if (memo[t]) return memo[t];

    uint64_t a, b, c;
    size_t ret = 0;
    if (iteration == iterations) {
        ret = 1;
    } else if (n == 0) {
        ret = check(1, iteration + 1);
    } else if (is_even(n)) {
        split(n, a, b);
        ret = check(a, iteration + 1) + check(b, iteration + 1);
    } else {
        ret = check(n * 2024, iteration + 1);
    }
    
    memo[t] = ret;

    return ret;
}

int main() {
    size_t result = 0;
    std::unordered_map<uint64_t, size_t> stone_counts;

    for (u_int64_t n : data) {
        //stone_counts[]
        result += check(n, 0);
    }

    std::cout << result << std::endl;
    
}