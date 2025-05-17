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
    const uint32_t M = 31;
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
            // Calculate the most significant bit for n and u
            uint32_t msb_n = M - __builtin_clz(n);
            uint32_t msb_u = M - __builtin_clz(u);
            int msb = std::min(M, std::max(msb_n, msb_u));

            uint32_t curr_n = 0;
            uint32_t max_or = 0;
            uint32_t max_comp = MAX;
            for(int bit = msb; bit >= 0; --bit)
            {
                uint32_t tmp_n = curr_n | (1U << bit);
                if(tmp_n > u) continue; // exced the upper bound, skip this bit
                // below the lower bound, add the bit
                if(tmp_n < l) 
                { curr_n = tmp_n; continue; }

                // if bit is not set in n, add it
                if(!(n & (1U << bit)))
                {
                    curr_n = tmp_n;
                    max_comp = curr_n;
                    max_or = (curr_n | n);
                }
                else 
                {
                    // the options arise: either bit is set or not
                    // which one should be assigned to curr_n to go on??
                    // we can exploit the backtracking approach
                    uint32_t skip = curr_n;
                    uint32_t add = tmp_n;
                    if((skip | n) > (add | n)); // do nothing
                    else if((skip | n) < (add | n))
                    {
                        curr_n = add;
                        max_comp = add;
                        max_or = (add | n);
                    } max_comp = std::min(max_comp, std::min(skip, add));
                }
            }
            std::cout << max_comp << std::endl;
        }
    }
}