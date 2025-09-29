/*
───────────────────────────────────────────────────────────────
🧳 UVa 10450 World Cup Noise, combinatorics, the pattern ≈ Fibonacci, https://onlinejudge.org/external/104/10450.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using ull = unsigned long long;
using vll = std::vector<ull>;



// https://oeis.org/A000045
ull backtrack(int bits_left, bool is_adjacent, int last_bit) { 
  // base case: no bits are left
  if(bits_left == 0) {
    return is_adjacent ? 0 : 1;
  }

  ull total_ways = 0;
  // place 0
  total_ways += backtrack(bits_left - 1, is_adjacent, 0);
  // place 1
  total_ways += backtrack(bits_left - 1, is_adjacent || (last_bit == 1), 1);

  return total_ways;
}



namespace algorithms::onlinejudge::maths::world_cup_noise
{
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        vll fibs(51);
        fibs[0] = 1;
        fibs[1] = 2;
        for(int i = 2; i <= 51; i++) {
          fibs[i] = fibs[i - 1] + fibs[i - 2];
        }

        int t_cases, t_case = 1;
        scanf("%d", &t_cases);
        while(t_cases--) {
          int n_bits;
          scanf("%d", &n_bits);
        //   printf("Scenario #%d:\n%llu\n\n", t_case++, backtrack(n_bits, false, 0));
          printf("Scenario #%d:\n%llu\n\n", t_case++, fibs[n_bits]);
        }
    }
}