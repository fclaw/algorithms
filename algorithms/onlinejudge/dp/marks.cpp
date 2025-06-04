#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>




typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


namespace algorithms::onlinejudge::dp::marks
{
    /** https://onlinejudge.org/external/109/10910.pdf */
    int n, t, p, t_cases;
    int memo[71][5000];
    int get_ways(int subject, int total_marks)
    {
        if(total_marks > t) return 0;
        if(total_marks == t && 
           subject == n) return 1;

        int& ways = memo[subject][total_marks];
        if(~ways) return ways;

        ways = 0;
        for(int m = p; m <= t; ++m) {
           ways += get_ways(subject + 1, total_marks + m);
        }
        return ways;
    }
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage =
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        
        while_read(t_cases);
        while(t_cases--)
        {
            while_read(n, t, p);
            std::memset(memo, -1, sizeof memo);
            std::cout << get_ways(0, 0) << std::endl;
        }
    }
}