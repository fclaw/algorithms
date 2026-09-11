/*
───────────────────────────────────────────────────────────────
🧳 11555 Aspen Avenue, https://onlinejudge.org/external/115/11555.pdf, rt: s
───────────────────────────────────────────────────────────────
 * ============================================================================
 * 🧠 THEORETICAL & ARCHITECTURAL FOUNDATION: Aspen Avenue (UVa 11555)
 * ============================================================================
 * 
 * 1. THE GREEDY TRAIT: Triangle Inequality & The Monge Property
 * ------------------------------------------------------------
 * In general matching, pairing N trees to N slots requires searching N! 
 * permutations (or the O(N^3) Hungarian Algorithm, which would TLE for N=2000).
 * 
 * WHY IS SORTING UPFRONT MATHEMATICALLY OPTIMAL?
 * By the Euclidean Triangle Inequality (the Monge / Uncrossing Property):
 *     cost(A -> X1) + cost(B -> X2)  <  cost(A -> X2) + cost(B -> X1)
 *     (for any initial positions A < B and target slots X1 < X2)
 * 
 * Crossing paths in Euclidean space is strictly suboptimal compared to 
 * parallel paths. Therefore:
 *   • Trees on the same bank will NEVER cross each other's paths!
 *   • The Triangle Inequality acts as a "Greedy Trait" that fixes the optimal 
 *     assignment order: we can strictly process trees from left to right:
 *         p_0 <= p_1 <= p_2 <= ... <= p_{N-1}
 *   • We never need to permute, reorder, or backtrack!
 * 
 * 2. THE DIVISION OF LABOR: Greedy Ordering + DP Partitioning
 * -----------------------------------------------------------
 * • Greedy Part : Sort trees initially. Fixes the monotonic left-to-right flow.
 * • DP Part     : For the current tree in that sorted sequence, decide which 
 *                 side to plant it on (Next available Left vs. Right slot).
 * 
 * 3. STATE-SPACE DIMENSION REDUCTION (3D -> 2D):
 * ----------------------------------------------
 * An intuitive model tracks three variables: dp(tree_idx, l_planted, r_planted).
 * For N = 2000 (N/2 = 1000 per side):
 *     2000 * 1000 * 1000 * 8 bytes ≈ 16 GIGABYTES of RAM! (Instant MLE!)
 * 
 * THE CONSERVATION INVARIANT:
 * Because trees are assigned one by one from the sorted array, the total 
 * number of trees placed is strictly conserved:
 * 
 *         current_tree_index = l + r
 * 
 * This eliminates the 3rd degree of freedom completely!
 * 
 * 4. THE 2D RECURRENCE:
 * ---------------------
 * State: dp(l, r) = min distance when 'l' left slots and 'r' right slots are filled.
 * 
 *     dp(l, r) = min(
 *         dp(l + 1, r) + |p_{l+r} - x_l|,                         // Plant on Left
 *         dp(l, r + 1) + sqrt((p_{l+r} - x_r)^2 + W^2)           // Plant on Right
 *     )
 * 
 * Where:
 *     gap = L / (N / 2 - 1)
 *     x_k = k * gap
 * 
 * COMPLEXITY:
 * -----------
 * • State Space : (N/2 + 1) * (N/2 + 1) = 1001 * 1001 ≈ 1,000,000 states.
 * • Memory      : ~8 MEGABYTES (100% safe within contest RAM limits).
 * • Time        : O((N/2)^2) ≈ 10^6 operations (Runs in < 0.04 seconds!).
 * ============================================================================
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vd = std::vector<double>;
using vvd = std::vector<vd>;

constexpr double INF = std::numeric_limits<double>::max();
constexpr int MAX = 1000;

int N;


double get_min_move_distance(int left_cnt, int right_cnt, double length, double width, double gap, const vd& trees, vvd& cache) {
        
  // Base Case: All N/2 left and N/2 right trees are planted!  
  if(left_cnt == N /2 && 
     right_cnt == N / 2) {
    return (cache[left_cnt][right_cnt] = 0.0);
  }

  if(cache[left_cnt][right_cnt] >= 0) {
    return cache[left_cnt][right_cnt];
  }

  double best = INF;
  int curr_tree_idx = left_cnt + right_cnt;
  double curr_left_dist = trees[curr_tree_idx];
  // ==========================================
  // 1. Plant the current tree on the LEFT side
  // ==========================================
  if(left_cnt < N / 2) { // ✅ Check slot capacity
    double left_dist = left_cnt * gap;
    double left_euclidean_dist = std::abs(left_dist - curr_left_dist);
    double left_min_move = left_euclidean_dist + get_min_move_distance(left_cnt + 1, right_cnt, length, width, gap, trees, cache);
    best = std::min(best, left_min_move);
  }

  // ==========================================
  // 2. Plant the current tree on the RIGHT side
  // ==========================================
  if(right_cnt < N / 2) { // ✅ Check slot capacity
    double right_left_side = std::abs(right_cnt * gap - curr_left_dist);
    double right_euclidean_dist = std::sqrt(right_left_side * right_left_side + width * width);
    double right_min_move = right_euclidean_dist + get_min_move_distance(left_cnt, right_cnt + 1, length, width, gap, trees, cache);
    best = std::min(best, right_min_move);
  }

  return (cache[left_cnt][right_cnt] = best);
}


namespace algorithms::onlinejudge::advanced_topics::aspen_avenue
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

        while(std::cin >> N) {
          vd trees(N);
          double length, width;
          std::cin >> length >> width;
          for(int i = 0; i < N; ++i) {
            std::cin >> trees[i];
          }
          std::sort(trees.begin(), trees.end());
          double gap = static_cast<double>(length) / ((N / 2) - 1);
          vvd cache(N / 2 + 1, vd(N / 2 + 1, -1.0));
          std::cout << std::fixed << std::setprecision(10) << get_min_move_distance(0, 0, length, width, gap, trees, cache) << std::endl;
        }
    }
}
