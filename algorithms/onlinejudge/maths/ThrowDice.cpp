/*
───────────────────────────────────────────────────────────────
🧳  UVa 10238 Throw the Dice!, https://onlinejudge.org/external/102/10238.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>
#include <boost/math/common_factor.hpp> // For boost::math::gcd and lcm
#include <boost/multiprecision/cpp_int.hpp> // The header for the bigint class



namespace mp = boost::multiprecision;

using v_bg = std::vector<mp::cpp_int>;
using vv_bg = std::vector<v_bg>;


mp::cpp_int count_desirable_outcomes(int curr_sum, int throws, int target, int faces, vv_bg& memo) {
  if(throws == 0) {
    if(curr_sum == target) return 1;
    else return 0;
  }

  if(~memo[curr_sum][throws]) 
    return memo[curr_sum][throws];

  mp::cpp_int ans = 0;
  for(int i = 1; i <= faces; ++i)
    ans += count_desirable_outcomes(curr_sum + i, throws - 1, target, faces, memo);
  return memo[curr_sum][throws] = ans;
}


namespace algorithms::onlinejudge::maths::throw_dice
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

        int faces, throws, target;
        while(scanf("%d %d %d", &faces, &throws, &target) == 3) {
          mp::cpp_int bg_faces = mp::cpp_int(faces);  
          mp::cpp_int total_outcomes = mp::pow(bg_faces, throws); // perfectly corresponds to the total number of leaves in the decision tree

          vv_bg dp(faces * throws + 1, v_bg(throws + 1, 0));
          for(int i = 1; i <= faces; ++i) dp[i][1] = 1; // base case
          // general case
          for(int t = 2; t <= throws; ++t) {
            for(int s = 1; s <= faces * t; ++s) { // all possible targets from 1 to faces * t
              for(int i = 1; i <= std::min(s, faces); ++i) { // faces
                dp[s][t] += dp[s - i][t - 1];
              }
            }
          }
          mp::cpp_int desirable_outcome = faces * throws < target ? 0 : dp[target][throws];
          printf("%s/%s\n", desirable_outcome.str().c_str(), total_outcomes.str().c_str());
        }
    }
}