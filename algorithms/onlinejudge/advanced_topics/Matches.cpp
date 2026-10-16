/*
───────────────────────────────────────────────────────────────
🧳 UVa 11375 Matches, https://onlinejudge.org/external/113/11375.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "../maths/utility/fast_bigint.cpp"
#include "../maths/utility/arithmetics.cpp"
#include <bits/stdc++.h>




namespace bi = algorithms::onlinejudge::maths::utility::fast_bigint;
namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;

// how many matches are needed for a number to form
std::array<int, 10> numbers = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};


std::unordered_map<ii, ll> cache;

ll powers[11][16];

void precompute_powers() {
 
  for(int n = 0; n <= 10; ++n) {
    for(int p = 0; p <= 15; ++p) {
      powers[n][p] = arith::power(n, p);
    }
  }
}


// cache is no need for DAG nature
ll count_numbers(int curr_num, int matches) {


  if(matches == 0 || 
     curr_num == 0) {
    return 0LL;
  }

  ii key = std::make_pair(curr_num, matches);
  if(auto it = cache.find(key); it != cache.end()) {
    return it->second;
  }

  int digits = curr_num != -1 ? (int)std::log10(curr_num) + 1 : 0;
  int add = curr_num;
  if(add == -1) {
    add = 0;
  }
  ll count = 0LL;
  for(int n = 0; n <= 9; ++n) {
    int matches_needed = numbers[n];
    if(matches_needed <= matches) {
      int next_num = add + powers[n][digits + 1];
      count += 1 + count_numbers(next_num, matches - matches_needed);
    }
  }
  return (cache[key] = count);
}


namespace algorithms::onlinejudge::advanced_topics::matches
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

        precompute_powers();
        int matches;
        while(stdin_read(matches)) {
          std::cout << count_numbers(-1, matches) << "\n";
        }
    }
}