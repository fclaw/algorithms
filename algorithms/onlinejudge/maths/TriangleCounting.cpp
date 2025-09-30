/*
───────────────────────────────────────────────────────────────
🧳 UVa 11401 Triangle Counting, https://onlinejudge.org/external/114/11401.pdf, https://oeis.org/A173196, Partial sums of A002620 rt: s
───────────────────────────────────────────────────────────────
0
1
3
7
13
22
34
50
70
95
125
161
203
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using ll = long long;
using vll = std::vector<ll>;


bool is_triangle(const vll& rods_lengths) {
  return rods_lengths[0] + rods_lengths[1] > rods_lengths[2] && 
         rods_lengths[0] + rods_lengths[2] > rods_lengths[1] && 
        rods_lengths[1] + rods_lengths[2] > rods_lengths[0];
}


ll backtrack(int pos, int rods_n, const vll& rods_lengths, vll& setup) {

  if(pos > (int)rods_lengths.size()) return 0;

  if(rods_n == 3) {
    return is_triangle(setup) ? 1 : 0;
  }

  ll ways = 0;
  // take rods
  setup.push_back(rods_lengths[pos]);
  ways += backtrack(pos + 1, rods_n + 1, rods_lengths, setup);
  setup.pop_back();
  // skip rods
  ways += backtrack(pos + 1, rods_n, rods_lengths, setup);
  return ways;
}


namespace algorithms::onlinejudge::maths::triangle_counting
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

        vll dp(1000001);
        dp[3] = 0;
        for(int i = 4; i <= 1000000; i++) {
          ll term1 = (i - 1) / 2;
          ll term2 = (i - 2) / 2;
          dp[i] = dp[i - 1] + term1 * term2;
        }

        int n;
        while(scanf("%d", &n) == 1 && n > 2) {
        //   vll setup;
        //   vll rods_lengths(n);
        //   std::iota(rods_lengths.begin(), rods_lengths.end(), 1);
        //   printf("%lld\n", backtrack(0, 0, rods_lengths, setup));
          printf("%lld\n", dp[n]);
        } 
    }
}