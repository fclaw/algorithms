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
#include <limits>




namespace algorithms::onlinejudge::greedy::bit_mask
{
    /** https://onlinejudge.org/external/107/10718.pdf */
    const int MBit = 31;
    const uint32_t MAX = std::numeric_limits<uint32_t>::max();
    uint32_t n, l, u;
    std::pair<uint32_t, uint32_t> backtrack(int bit, uint32_t curr_v) 
    {
        if(curr_v > u) return {0, MAX};  // Prune invalid branches
        if(bit < 0) {
          if(curr_v >= l)
            return {curr_v | n, curr_v};
          else return {0, MAX};
        }

        std::pair<uint32_t, uint32_t> res;

        // Try not setting bit
        std::pair<uint32_t, uint32_t> skip = backtrack(bit - 1, curr_v);
        // Try setting bit
        std::pair<uint32_t, uint32_t> add = backtrack(bit - 1, curr_v | (1U << bit));

        if(skip.first > add.first) res = skip;
        else if(skip.first < add.first) res = add;
        else res = { skip.first, std::min(skip.second, add.second) };
        return res;
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

        while(while_read(n, l, u))
        {
            uint32_t max_comp = 0;
            for(int bit = MBit; bit >= 0; --bit)
            {
                // if bit is not set in n, add it
                if(!(n & (1U << bit)))
                {
                    uint32_t tmp_n = max_comp | (1U << bit);
                    if(tmp_n <= u) max_comp = tmp_n;
                }
                else // if bit is set try using inclusive-exclusive principle
                {
                    uint32_t add_n = max_comp | (1U << bit);
                    if(add_n > l) continue; // if added bit leads to passing over l go on to next
                    max_comp = add_n;
                }
            }
            std::cout << max_comp << std::endl;
        }
    }
}