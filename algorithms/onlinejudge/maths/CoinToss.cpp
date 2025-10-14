/*
───────────────────────────────────────────────────────────────
🧳  UVa 10328 Coin Toss, https://onlinejudge.org/external/103/p10328.pdf, rt: s
───────────────────────────────────────────────────────────────
 * =====================================================================================
 * STRATEGIC GUIDE: SOLVING UVa 10328 - Coin Toss
 * =====================================================================================
 *
 * This problem asks for the number of sequences of N coin tosses that contain at least
 * one consecutive run of K heads.
 *
 * -------------------------------------------------------------------------------------
 * The Core Insight: Complementary Counting
 * -------------------------------------------------------------------------------------
 *
 * Trying to count the "good" sequences (those with AT LEAST one run of K heads) directly
 * is extremely difficult due to the problem of over-counting. For example, the sequence
 * HHHHHH contains a run of 3 heads starting at index 1, index 2, index 3, and index 4.
 * A direct counting method would need to use the complex Principle of Inclusion-Exclusion
 * to handle these overlapping cases.
 *
 * A far more elegant and simpler approach is COMPLEMENTARY COUNTING. The logic is:
 *   [Total Good Sequences] = [Total Possible Sequences] - [Total "Bad" Sequences]
 *
 * 1.  Total Possible Sequences: For N tosses, each with 2 outcomes, the total number
 *     of unique sequences is simply 2^N. This is easy to calculate.
 *
 * 2.  Total "Bad" Sequences: A "bad" sequence is one that has NO consecutive run of
 *     K heads or more. This property is much easier to count because it never involves
 *     over-counting. We can count this using Dynamic Programming.
 *
 * -------------------------------------------------------------------------------------
 * The Dynamic Programming Solution for Counting "Bad" Sequences
 * -------------------------------------------------------------------------------------
 *
 * We define a recursive function (with memoization) to count the bad sequences:
 *   countBad(tosses_left, current_run) = The number of "bad" sequences of length
 *                                        'tosses_left' that can be formed, given
 *                                        that we are already on a 'current_run' of
 *                                        consecutive heads.
 *
 * - THE DP STATE:
 *   The state must capture all necessary information to make a decision. Here, we need:
 *   1. `tosses_left`: How many more coins we need to toss.
 *   2. `current_run`: The length of the current consecutive run of heads.
 *
 * - THE RECURRENCE RELATION:
 *   From any state `(tosses_left, current_run)`, we consider the next toss:
 *
 *   a) If we toss a TAIL: The run of heads is broken and resets to 0. We then need to
 *      form a valid "bad" sequence of length `tosses_left - 1` starting with a run of 0.
 *      This contributes `countBad(tosses_left - 1, 0)` to the total.
 *
 *   b) If we toss a HEAD: The run of heads increases by 1. We then need to form a valid
 *      "bad" sequence of length `tosses_left - 1` starting with a run of `current_run + 1`.
 *      This contributes `countBad(tosses_left - 1, current_run + 1)` to the total.
 *
 *   The total number of ways is the sum of these two mutually exclusive possibilities.
 *
 * - BASE CASES:
 *   1. `if (current_run >= K)`: We have just formed a run of K heads. This is NOT a "bad"
 *      sequence, so this path is invalid and contributes 0 to the count.
 *   2. `if (tosses_left == 0)`: We have successfully formed a full sequence without ever
 *      violating the rule. This is one valid "bad" sequence, so it contributes 1 to the count.
 *
 * By starting with `countBad(N, 0)`, the DP explores the entire valid decision tree,
 * pruning branches that would form a run of K heads, and correctly sums up the leaves
 * of the remaining tree.
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>
#include <boost/math/common_factor.hpp> // For boost::math::gcd and lcm
#include <boost/multiprecision/cpp_int.hpp> // The header for the bigint class



namespace mp = boost::multiprecision;

using v_bg = std::vector<mp::cpp_int>;
using vv_bg = std::vector<v_bg>;


mp::cpp_int count_bad_seq(int tosses_left, int heads, int max_length, vv_bg& memo) {
  
  if(heads >= max_length) return 0;
  if(tosses_left == 0) return 1;

  if(~memo[heads][tosses_left]) 
    return memo[heads][tosses_left];

  mp::cpp_int bad_seq = 0;
  bad_seq += count_bad_seq(tosses_left - 1, heads + 1, max_length, memo);
  bad_seq += count_bad_seq(tosses_left - 1, 0, max_length, memo);
  return memo[heads][tosses_left] = bad_seq;
}


namespace algorithms::onlinejudge::maths::coin_toss
{
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }
        }

        int tosses, min_length;
        while(scanf("%d %d", &tosses, &min_length) == 2) {
          mp::cpp_int faces = mp::cpp_int(2);
          mp::cpp_int total_seq = mp::pow(faces, tosses);
          vv_bg memo(tosses + 1, v_bg(tosses + 1, -1));
          mp::cpp_int bad_seq = count_bad_seq(tosses, 0, min_length, memo);
          mp::cpp_int good_seq = total_seq - bad_seq;
          printf("%s\n", good_seq.str().c_str());
        }
    }
}