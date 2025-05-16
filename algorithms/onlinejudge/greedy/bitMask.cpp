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







namespace algorithms::onlinejudge::greedy::bit_mask
{
    /** https://onlinejudge.org/external/107/10718.pdf */
    const uint32_t M = 32;
    const uint32_t MAX = std::numeric_limits<uint32_t>::max();
    uint32_t n, l, u;
    void backtrack(int bit, uint32_t curr_v, uint32_t& max_or, uint32_t& comp) 
    {
        if(curr_v > u) return;  // Prune invalid branches
        if(bit < 0) {
          if(curr_v >= l) {
            uint32_t curr_or = curr_v | n;
            if(curr_or > max_or) {
               max_or = curr_or;
               comp = curr_v;
             } else if (curr_or == max_or)
                 comp = std::min(comp, curr_v);  // Keep min comp for tie
          }
          return;
        }

      // Try not setting bit
      backtrack(bit - 1, curr_v, max_or, comp);
      // Try setting bit
      backtrack(bit - 1, curr_v | (1U << bit), max_or, comp);
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
            uint32_t max_or = 0;
            uint32_t comp = 0;
            backtrack(msb, 0, max_or, comp);
            std::cout << comp << std::endl;
        }
    }
}