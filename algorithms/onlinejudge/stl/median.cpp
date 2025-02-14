#include <cassert>
#include <optional>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <algorithm>


typedef std::vector<int> vi;

namespace algorithms::onlinejudge::stl::median
{
    // https://onlinejudge.org/external/101/10107.pdf,
    // find median of a growing/dynamic list of integers; 
    // still solvable with multiple calls of nth element in algorithm
    const int N = 10000;

    std::string trim(const std::string& str) 
    {
        auto start = 
          std::find_if(
            str.begin(), 
            str.end(), 
            [](unsigned char ch) 
            { return !std::isspace(ch); });
    
        auto end = 
          std::find_if(
            str.rbegin(), 
            str.rend(), 
            [](unsigned char ch) {
            return !std::isspace(ch); }).base();
    
        return (start < end) ? std::string(start, end) : "";
    }
    void submit(std::optional<char*> file)
    {
        if(file.has_value()) 
          assert(std::freopen(file.value(), "r", stdin) != nullptr);
        
        vi numbers;
        numbers.reserve(N);
        std::string s;
        int idx = 0;
        while(std::cin >> s)
        {
            int n = std::stoi(trim(s));
            numbers.push_back(n);

            auto m = numbers.begin() + numbers.size() / 2;
            std::nth_element(numbers.begin(), m, numbers.end());
            int first = numbers[numbers.size() / 2];

            if(!(++idx % 2)) // even 
            {
                int second = *std::max_element(numbers.begin(), m);
                std::cout << (first + second) / 2 << std::endl;
            }
            else std::cout << first << std::endl;
        }
    }
}