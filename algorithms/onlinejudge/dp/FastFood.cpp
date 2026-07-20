/*
───────────────────────────────────────────────────────────────
🧳 UVa 662 Fast Food, https://onlinejudge.org/external/6/662.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



const int MAX = (int)1e9;

int N, K;

using vi = std::vector<int>;

struct Depot
{
    int idx;
    int restaurant_id;
    int from;
    int to;
};

using v_depots = std::vector<Depot>;

struct Ans
{
    int dist;
    bool operator < (const Ans& other) const {
      return dist < other.dist;
    }

     // In-place addition
    Ans& operator += (const Ans& other) {
      this->dist += other.dist;
      return *this;
    }

    // Binary addition defined in terms of operator+=
    // Passing the first argument by value allows the compiler to optimize copies
    friend Ans operator + (Ans lhs, const Ans& rhs) { lhs += rhs; return lhs; }
};


Ans cache[201][201][31];

/**
 * Minimizes the sum of distances from restaurants to their nearest depots using 
 * an optimized interval partition Dynamic Programming (DP) approach.
 *
 * Core Principles & Optimizations:
 * 
 * 1. The "Pressed Left Boundary" Principle (Search Space Reduction):
 *    In a naive 2D interval DP, one would try to find a sub-segment [l, r] within 
 *    [left, right] to place a depot. However, because the previous recursive call 
 *    finishes processing at index 'i', the next recursive subproblem must start 
 *    exactly at 'i + 1'. Therefore, the left boundary of the current subproblem 
 *    is always fixed to 'left'. We only need to choose:
 *      a) Where the current depot 'candidate' is placed (left <= candidate < right).
 *      b) Where the current depot's coverage ends at index 'i' (candidate <= i < right).
 *    This completely eliminates the need to loop over different left boundaries 'l'.
 *
 * 2. 2D State Space Reduction:
 *    Since 'right' is always passed as N (the total number of restaurants) and 
 *    never decreases in any recursive call, 'right' remains constant. Consequently, 
 *    although the cache is defined as cache[left][right][depots_left], the state 
 *    space is effectively 2D: cache[left][N][depots_left], leading to minimal memory 
 *    overhead and O(N * K) states.
 *
 * 3. Sequential Cost Accumulation:
 *    Instead of computing the cost of the segment [left, i] with a nested loop in 
 *    each transition, the code:
 *      a) Pre-calculates 'left_sum' (distance from elements [left, candidate - 1] to candidate).
 *      b) Incrementally accumulates 'right_sum' (distance from elements [candidate, i] to candidate) 
 *         inside the 'i' loop.
 *    This allows the transition cost to be evaluated incrementally in O(1) per step.
 *
 * State Definition:
 *   minimize_sum(left, right, depots_left) returns the optimal Ans struct for 
 *   partitioning the range [left, right) using up to 'depots_left' depots.
 *
 * @param restaurants Sorted list of restaurant coordinates along a 1D line.
 * @param left        The inclusive starting index of the current unserved range.
 * @param right       The exclusive ending index of the current unserved range.
 * @param depots_left The remaining number of depots available to place.
 * @return            Ans struct containing the minimum distance and the placement details.
 */
Ans minimize_sum(const vi& restaurants, int left, int right, int depots_left) {

  // Base Case: No restaurants left to cover. 
  // If we have unused depots, the cost is 0. If we are out of depots but have no 
  // restaurants left, it is also a valid state with cost 0.
 if(left >= right) {
   return (cache[left][right][depots_left] = {depots_left == 0 ? 0 : MAX});
  }

  if(~cache[left][right][depots_left].dist) {
    return cache[left][right][depots_left];
  }

  Ans best = {MAX};
  for(int candidate = left; candidate < right; ++candidate) {
    int left_sum = 0;
    int d = restaurants[candidate];
    for(int i = left; i < candidate; ++i) {
      left_sum += std::abs(restaurants[i] - d);
    }

    Ans left_ans = {left_sum};    
    int right_sum = 0;
    for(int i = candidate; i < right; ++i) {
      right_sum += std::abs(restaurants[i] - restaurants[candidate]);
      Ans right_ans = {right_sum};
      Ans local_best = left_ans + right_ans;
      best = std::min(best, local_best + minimize_sum(restaurants, i + 1, right, depots_left - 1));
    }
  }
   return (cache[left][right][depots_left] = best);

}

void reconstruct_path(const vi& restaurants, int left, int right, int depots_left, v_depots& out_depots) {
  if (left >= right) {
    return;
  }

  int best_dist = cache[left][right][depots_left].dist;
  for(int candidate = left; candidate < right; ++candidate) {
    int left_sum = 0;
    int d = restaurants[candidate];
    for(int i = left; i < candidate; ++i) {
      left_sum += std::abs(restaurants[i] - d);
    }

    int left_ans = left_sum;    
    int right_sum = 0;
    for(int i = candidate; i < right; ++i) {
      right_sum += std::abs(restaurants[i] - restaurants[candidate]);
      int right_ans = cache[i + 1][right][depots_left - 1].dist;
      int local_best = left_ans + right_sum + right_ans;
      if(local_best == best_dist) {
        out_depots.push_back({K - depots_left, candidate, left, i});
        reconstruct_path(restaurants, i + 1, right, depots_left - 1, out_depots);
        return;
      }
    }
  }
}


namespace algorithms::onlinejudge::dp::fast_food
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

        int t_cases = 1;
        while(std::cin >> N >> K && N && K) {
          vi restaurants(N);
          for(int i = 0; i < N; ++i) {
            scanf("%d", &restaurants[i]);
          }

          for(int i = 0; i <= 200; ++i) {
            for(int j = 0; j <= 200; ++j) {
              for(int k = 0; k <= 30; ++k) {
                cache[i][j][k] = {-1};
              }
            }
          }

          Ans ans = minimize_sum(restaurants, 0, N, K);
          v_depots depots;
          reconstruct_path(restaurants, 0, N, K, depots);
          printf("Chain %d\n", t_cases++);
          for(auto& depot : depots) {
            int idx = depot.idx + 1;
            int r = depot.restaurant_id + 1;
            int from = depot.from + 1;
            int to = depot.to + 1;
            std::string served = 
              "restaurant " + 
              std::to_string(from);
            if(from < to) {
              served = 
                "restaurants " + 
                std::to_string(from) + 
                " to " + 
                std::to_string(to);
            }
            printf("Depot %d at restaurant %d serves %s\n", idx, r, served.c_str());
          }
          printf("Total distance sum = %d\n\n", ans.dist);
        }
    }
}