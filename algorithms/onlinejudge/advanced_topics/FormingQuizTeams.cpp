/*
───────────────────────────────────────────────────────────────
🧳 UVa 10911 Forming Quiz Teams, https://onlinejudge.org/external/109/10911.pdf,  rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM & APPROACH:
 * ============================================================================
 * This problem asks for a Minimum Weight Perfect Matching on a general 
 * 2D Euclidean graph of 2N vertices, where 1 <= N <= 8 (at most 16 vertices).
 *
 * 1. Symmetry Breaking (The Key Insight):
 *    Instead of exploring all pairs, which leads to an O((2N)!) search space,
 *    we fix the first available person (i) at each step using LSOne(pool).
 *    We then only iterate through every remaining person (j) to form a pair.
 *    Because pairing order does not matter, this reduces the search space from
 *    a full factorial down to the double factorial:
 *        (2N - 1)!! = (2N - 1) * (2N - 3) * ... * 3 * 1
 *    For the worst case (N = 8, 2N = 16):
 *        15!! = 2,027,025 leaves.
 *
 * 2. Why Pure Backtracking beats DP here:
 *    - Memory & Cache: The recursion state is purely CPU-register driven.
 *      The distance matrix is 16x16 (~2 KB), which fits entirely within the 
 *      CPU's L1 cache (~32-48 KB), yielding near-zero cache misses.
 *    - No Reset Overhead: DP requires resetting a 65,536-element table (512 KB)
 *      for every test case. Since many test cases have N <= 6 (<= 10k ops),
 *      the overhead of clearing memory exceeds the search time itself.
 *
 * 3. Optimizations:
 *    - Precomputed Euclidean Distances: Computes sqrt() only (2N)^2 / 2 = 120
 *      times per test case instead of ~2 million times inside the recursion.
 *    - Bitwise Intrinsics: LSOne(S) and __builtin_ctz provide hardware-accelerated
 *      O(1) bit manipulation and index lookup.
 *
 * ============================================================================
 * COMPLEXITY:
 * ============================================================================
 * - Time Complexity:  O((2N)^2) precomputation + O((2N - 1)!!) search
 *                     Worst case (N=8) ~ 2.03 x 10^6 operations (< 0.20s).
 * - Space Complexity: O((2N)^2) auxiliary space for the distance matrix,
 *                     O(N) recursion stack depth. (Effectively O(1) memory).
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



#define LSOne(S) ((S) & (-S))

using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vd = std::vector<double>;
using vvd = std::vector<vd>;


double calc_dist(const ii& fst, const ii& snd) {
  double x = std::abs(fst.first - snd.first);
  double y = std::abs(fst.second - snd.second);
  return std::sqrt(x * x + y * y);
}

// Let x1 be the distance between the houses of group 1, x2 be the distance
// between the houses of group 2 and so on. You have to make sure the summation (x1+x2+x3+. . .+xn) is minimized.
double get_minimal_summation(int pool, const vvd& dist) {

  if(pool == 0) {
    return 0.0;
  }

  int i_bit = LSOne(pool);
  int i = __builtin_ctz(i_bit);
  pool -= i_bit;
  double best = 1e9;
  int tmp = pool;
  while(tmp) {
    int j_bit = LSOne(tmp);
    int j = __builtin_ctz(j_bit);
    best = std::min(best, dist[i][j] + get_minimal_summation(pool - j_bit, dist));
    tmp -= j_bit;
  }

  return best;
}


namespace algorithms::onlinejudge::advanced_topics::forming_quiz_teams
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

        int N, t_case = 1;
        while(std::cin >> N && N) {
          std::string name;
          int x_coord, y_coord;
          vii houses(2 * N);
          for(int i = 0; i < 2 * N; ++i) {
            while_read(name, x_coord, y_coord);
            houses[i] = {x_coord, y_coord};
          }
          vvd dist(2 * N, vd(2 * N, 0.0));
          for(int i = 0; i < 2 * N; ++i) {
            for(int j = i + 1; j < 2 * N; ++j) {
              dist[i][j] = calc_dist(houses[i], houses[j]);
            }
          }

          std::cout << "Case " << t_case++ << ": " << std::fixed << std::setprecision(2) << get_minimal_summation((1 << 2 * N) - 1, dist) << std::endl;
        }
    }
}