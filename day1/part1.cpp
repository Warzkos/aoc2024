#include <iostream>
#include <set>
#include <fstream>
#include <cmath>
#include <numeric>
// #include <ranges>

int main() {
    std::multiset<int, std::less<int>> list1;
    std::multiset<int, std::less<int>> list2;

    std::ifstream file("input.txt");

    int val1, val2;
    while (file >> val1 >> val2)
    {
        list1.insert(val1);
        list2.insert(val2);
    }

    // auto acc = 0;
    // for( auto [a, b] : std::ranges::views::zip(list1, list2) )
    // {
    //     acc += std::abs( a - b );
    // }

    auto acc = std::transform_reduce(list1.begin(), list1.end(), list2.begin(), 0, std::plus<>(), [](auto a, auto b) { return std::abs(a - b); });

    std::cout << acc << std::endl;

    return 0;
}