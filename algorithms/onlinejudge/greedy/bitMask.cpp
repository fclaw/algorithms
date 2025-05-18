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
    uint32_t n, l, u;
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
            int msb_n = MBit - __builtin_clz(n);
            int msb_u = MBit - __builtin_clz(u);
            int msb = std::min(MBit, std::max(msb_n, msb_u));
            uint32_t max_comp = 0;
            for(int bit = msb; bit >= 0; --bit)
            {
                // if bit is not set in n, add it
                // The current bit is NOT set in N:
                // → Setting this bit in M may increase (N | M), so we try to include it.
                // → However, we do so only if the resulting M does not exceed the upper bound U.
                if(!(n & (1U << bit))) {
                  if((max_comp | (1U << bit)) <= u) 
                    max_comp |= (1U << bit);
                }
                else // if bit is set try using inclusive-exclusive principle
                {
                    /*
                      In this block, we consider bits that are already set in `n`. 
                      We attempt to set those same bits in our candidate `max_comp` to possibly increase `(n | max_comp)`.
                      However, we're constrained by the need to find the **smallest possible M** such that:
                          - L ≤ M ≤ U
                          - (N | M) is maximised
                      So, once `max_comp` reaches or exceeds the lower bound `L`, 
                      we **must stop adding bits** — because any further increase would make `M` larger than necessary, 
                      violating the minimality requirement.
                      Hence, we skip this bit if adding it results in `add_n > L`.
                    */
                    uint32_t add_n = max_comp | (1U << bit);
                    if(add_n > l) continue;
                    max_comp = add_n;
                }
            }
            std::cout << max_comp << std::endl;
        }
    }
}