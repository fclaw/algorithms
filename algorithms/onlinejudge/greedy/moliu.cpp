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
#include <cctype>









namespace algorithms::onlinejudge::greedy::moliu
{
    /** https://onlinejudge.org/external/115/11567.pdf */
    uint32_t backtrack(uint32_t n)
    {
        if(n == 1)
          return 1;
        uint32_t steps = !(n % 2) ? backtrack(n / 2) : std::min(backtrack(n - 1), backtrack(n + 1));
        return 1 + steps;
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
        
        uint32_t n;
        while(while_read(n))
          std::cout << (n == 0 ? 0 : backtrack(n)) << std::endl;
    }
}