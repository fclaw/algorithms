/*
───────────────────────────────────────────────────────────────
🧳 UVa 10911 Forming Quiz Teams, https://onlinejudge.org/external/109/10911.pdf,  rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * ALGORITHM & APPROACH:
 * ============================================================================
 * Minimum Weight Perfect Matching on a general 2D Euclidean graph of 2N 
 * vertices (where 1 <= N <= 8, at most 16 vertices).
 *
 * 1. Symmetry Breaking (Reducing the Search Space):
 *    Arbitrarily fix the first available person (i) using LSOne(mask).
 *    Then, iterate through each remaining person (j) to form a pair (i, j).
 *    This avoids equivalent permutations of pairs and reduces the branching
 *    factor to at most (2N - 1) transitions per state.
 *
 * 2. Precomputed Euclidean Distances:
 *    Avoids calculating std::hypot/sqrt inside the recursive loop. Precomputing
 *    takes O((2N)^2) once per testcase instead of millions of times during DP.
 *
 * ============================================================================
 * CRUCIAL IMPLEMENTATION PITFALL: THE "PARITY TRAP" (Ghost Cache)
 * ============================================================================
 * Why `mask` MUST remain immutable inside the function:
 *
 * 1. Parity Invariant:
 *    All valid matching states consist of an EVEN number of unmatched people 
 *    (bits): 16, 14, 12, ..., 2, 0.
 *
 * 2. The Mutation Bug:
 *    If we mutate the mask directly:
 *        mask -= i_bit;              // mask now has ODD parity!
 *        ...
 *        return cache[mask] = best;  // BUG: stored under an ODD key!
 *
 * 3. The Consequence (0% Cache Hit Rate):
 *    Future calls always query EVEN-parity masks:
 *        if (cache[mask] >= 0) ...   // Always misses!
 *    The cache is populated exclusively with odd-parity entries that no future
 *    recursive step will ever read. The result is pure backtracking with 
 *    2+ million useless memory writes, making the runtime WORSE than no cache!
 *
 * 4. The Fix:
 *    Keep `mask` immutable. Subtract bits only into temporary variables:
 *        int tmp = mask - i_bit;
 *        ...
 *        int new_mask = mask - i_bit - j_bit; // maintains even parity
 *        return cache[mask] = best;           // cached under original even key!
 *
 * ============================================================================
 * COMPLEXITY:
 * ============================================================================
 * - Time Complexity:  O(N * 2^(2N))
 *                     There are only 2^(2N-1) reachable states with even parity.
 *                     For 2N = 16: at most 32,768 states visited.
 * - Space Complexity: O(2^(2N)) for memoization table + O((2N)^2) for dist table.
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

double cache[1 << 16];

// Let x1 be the distance between the houses of group 1, x2 be the distance
// between the houses of group 2 and so on. You have to make sure the summation (x1+x2+x3+. . .+xn) is minimized.
double dp(int mask, const vvd& dist) {

  if(mask == 0) {
    return 0;
  }

  if(cache[mask] >= 0) {
    return cache[mask];
  }

  int i_bit = LSOne(mask);
  int i = __builtin_ctz(i_bit);
  double best = 1e9;
  int tmp = mask - i_bit;
  while(tmp) {
    int j_bit = LSOne(tmp);
    int j = __builtin_ctz(j_bit);
    int new_mask = mask - j_bit - i_bit;
    best = std::min(best, dist[i][j] + dp(new_mask, dist));
    tmp -= j_bit;
  }

  return (cache[mask] = best);
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

          std::memset(cache, -1, sizeof cache);
          std::cout << "Case " << t_case++ << ": " << std::fixed << std::setprecision(2) << dp((1 << 2 * N) - 1, dist) << std::endl;
        }
    }
}