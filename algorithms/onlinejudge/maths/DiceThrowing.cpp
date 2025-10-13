/*
───────────────────────────────────────────────────────────────
🧳  UVa 10759 Dice Throwing, https://onlinejudge.org/external/107/10759.pdf, similar to  UVa 10238 with the number of faces fixed at 6, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>
#include <boost/math/common_factor.hpp> // For boost::math::gcd and lcm
#include <boost/multiprecision/cpp_int.hpp> // The header for the bigint class



namespace mp = boost::multiprecision;

constexpr int FACES = 6;

using v_bg = std::vector<mp::cpp_int>;
using vv_bg = std::vector<v_bg>;



namespace algorithms::onlinejudge::maths::dice_throwing
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

        int n_dice, target;
        while(scanf("%d %d", &n_dice, &target) == 2 && n_dice && target) {
          mp::cpp_int bg_faces = mp::cpp_int(FACES);  
          mp::cpp_int total_outcomes = mp::pow(bg_faces, n_dice); // perfectly corresponds to the total number of leaves in the decision tree
          vv_bg dp(FACES * n_dice + 1, v_bg(n_dice + 1, 0));
          for(int i = 1; i <= FACES; ++i) dp[i][1] = 1; // base case
          // general case
          for(int d = 2; d <= n_dice; ++d) {
            for(int s = 1; s <= FACES * d; ++s) { // all possible targets from 1 to faces * t
              for(int i = 1; i <= std::min(s, FACES); ++i) { // faces
                dp[s][d] += dp[s - i][d - 1];
              }
            }
          }

          mp::cpp_int desired_outcomes = 0;
          int max_sum = FACES * n_dice;
          // Sum up all possibilities from the target 'x' to the maximum possible sum
          for (int s = target; s <= max_sum; ++s)
            desired_outcomes += dp[s][n_dice];

          mp::cpp_int gcd = mp::gcd(total_outcomes, desired_outcomes);
          desired_outcomes /= gcd;
          total_outcomes /= gcd;
          if(total_outcomes == 1) printf("%s\n", desired_outcomes.str().c_str());
          else printf("%s/%s\n", desired_outcomes.str().c_str(), total_outcomes.str().c_str());
        }
    }
}