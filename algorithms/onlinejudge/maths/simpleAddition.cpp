/*
───────────────────────────────────────────────────────────────
🧳 UVa 10994 Simple Addition, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;

constexpr ll SUM_OF_1_TO_9 = 45;
constexpr ll BASE = 10;


ll get_sum(ll num) {
  if(num <= 0) return 0;
  ll chunks_of_9 = num / BASE;
  ll remainder_of_9 = num % BASE;
  return chunks_of_9 * SUM_OF_1_TO_9 + (remainder_of_9 * (remainder_of_9 + 1)) / 2 + get_sum(num / BASE);
}


namespace algorithms::onlinejudge::maths::simple_addition
{
    /** https://onlinejudge.org/external/109/10994.pdf */
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
        
        int left, right;
        while(scanf("%d %d", &left, &right) == 2 && left >= 0 && right >= 0) {
          ll sum = get_sum(right) - get_sum(left - 1);
          printf("%lld\n", sum);
        }  
    }
}