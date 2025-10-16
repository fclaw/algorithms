/*
───────────────────────────────────────────────────────────────
🧳  UVa 10648 Chocolate Box, https://onlinejudge.org/external/106/10648.pdf, rt: s
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
using ld = long double;


// number of ways to place i (distinguishable) chocolates into m boxes such that exactly j boxes are used
mp::cpp_int count_ways_all_full(int n_chocolates, int m_boxes) {    
  vv_bg dp(n_chocolates + 1, v_bg(m_boxes + 1, 0));
 
  // Base Case: There is exactly one way to place 0 chocolates into 0 boxes (by doing nothing).
  // This is the anchor from which all other states are built.
  dp[0][0] = 1;

  for (int i = 1; i <= n_chocolates; ++i) {
    for (int j = 1; j <= m_boxes; ++j) {
      // --- The Recurrence: Where can we place the i-th chocolate? ---        
      // Scenario A: We decide to place the i-th chocolate into a box that is already occupied 
      // => What if the j boxes were already occupied?
      // For this to be our current state (i chocolates, j boxes used),
      // it must be that the first (i-1) chocolates had ALREADY occupied all 'j' of these boxes.
      // The number of ways for that previous state to exist is dp[i-1][j].
      // For each of those ways, we now have 'j' choices of an occupied box to place the new chocolate into.
      mp::cpp_int ways_into_old_box = dp[i - 1][j] * j;
      // Scenario B: We decide to place the i-th chocolate into a completely new, empty box 
      // => What if only j-1 boxes were occupied? 1 box is left to explore
      // For this to be our current state, it must be that the first (i-1) chocolates
      // had occupied exactly 'j-1' boxes, leaving one empty for us to "discover".
      // The number of ways for that previous state to exist is dp[i-1][j-1].
      // There are (m_boxes - (j-1)) empty boxes to choose from. For each of the
      // previous arrangements, we can place our new chocolate in any of these empty boxes.
      mp::cpp_int ways_into_new_box = dp[i - 1][j - 1] * (m_boxes - (j - 1));
      dp[i][j] = ways_into_old_box + ways_into_new_box;
    }
  }
    
  // The final answer is the number of ways to place all 'n' chocolates using all 'm' boxes.
  return dp[n_chocolates][m_boxes];    
}

namespace algorithms::onlinejudge::maths::chocolate_boxes
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

        int t_case = 1, n_chocolates, m_boxes;
        while(scanf("%d %d", &n_chocolates, &m_boxes) == 2) {
        
          if(m_boxes == 0) {
            printf("Case %d: %0.7Lf\n", t_case++, (ld)0);
            continue;
          }

          mp::cpp_int bg_boxes = mp::cpp_int(m_boxes);  
          mp::cpp_int total_outcomes = mp::pow(bg_boxes, n_chocolates);
          mp::cpp_int desired_outcomes = count_ways_all_full(n_chocolates, m_boxes);
          mp::cpp_int gcd = mp::gcd(total_outcomes, desired_outcomes);
          desired_outcomes /= gcd;
          total_outcomes /= gcd;
          // Using long double gives more precision.
          ld desired_outcomes_d = desired_outcomes.convert_to<ld>();
          ld total_outcomes_d = total_outcomes.convert_to<ld>();
          // complementary countring
          ld prob = 1.0 - desired_outcomes_d / total_outcomes_d;
          printf("Case %d: %0.7Lf\n", t_case++, prob);
        }
    }
}