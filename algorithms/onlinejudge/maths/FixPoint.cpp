/*
───────────────────────────────────────────────────────────────
🧳 UVa 11226 Reaching the fix-point, https://onlinejudge.org/external/112/11226.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/primes.cpp"
#include <bits/stdc++.h>



namespace primes = algorithms::onlinejudge::maths::utility::primes;

constexpr ll MAX = 100000;

using map_ll_i = std::unordered_map<ll, int>;

int lsopf(ll num, map_ll_i& memo) {
  ll sum = primes::sumPF(num);
  if(sum == num) return 1;
  if(memo.count(sum)) return memo[sum];
  return memo[sum] = 1 + lsopf(sum, memo);
}


namespace algorithms::onlinejudge::maths::fix_point
{

    void submit(std::optional<char*> file, bool debug_mode)
    {
        primes::sieve(MAX);

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

        int t_cases, t_case = 1;
        scanf("%d", &t_cases);
        map_ll_i memo;
        while(t_cases--) {
          ll l, u;
          scanf("%lld %lld", &l, &u);
          int max_length = INT32_MIN;
          ll start = std::min(l, u);
          ll end = std::max(l, u);
          for(ll n = start; n <= end; ++n)
            max_length = std::max(max_length, lsopf(n, memo));
          printf("Case #%d:\n%d\n", t_case++, max_length);
        }
    }
}