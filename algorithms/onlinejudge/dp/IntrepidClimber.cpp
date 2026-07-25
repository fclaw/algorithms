/*
───────────────────────────────────────────────────────────────
🧳 UVa 12862 Intrepid climber, https://onlinejudge.org/external/128/12862.pdf, rt: s
───────────────────────────────────────────────────────────────
 * Solves UVa 12862 (Intrepid Climber) using a Dual-Branching Tree DP.
 *
 * Mathematical Model:
 *   We want to visit a set of "friend" landmarks starting from the root (summit).
 *   Since descending is free and only climbing costs energy, the optimal strategy
 *   is to find a path from the root to some friend, which we will use as our final 
 *   descent path (meaning we never climb back up from the last friend we visit).
 *   
 *   For any node 'idx', we must decide where this final descent path ends:
 *     Option 1: The path ends locally at 'idx' itself (if 'idx' is a friend).
 *     Option 2: The path ends deeper within the subtree of one of 'idx's children.
 *
 * Core Principles & Branching Completeness:
 * 
 * 1. Branching Completeness (The Vital Logic):
 *    A naive transition only considers ending the journey in one of the child subtrees.
 *    However, if 'idx' is a friend, we can choose to stop right there. 
 *    To ensure mathematical completeness, we must branch on both possibilities:
 *      
 *      - Local Base Case (End Here):
 *        If landmarks[idx] is true, we can end our journey at 'idx'. The cost is 
 *        the sum of fully ascending all of 'idx's active children:
 *           cost = Sum_{all children} (child.dist + total_ascension_cost(child.idx))
 *
 *      - Recursive Case (End in Child Subtree):
 *        We choose one child 'point' to contain the final descent path, meaning we 
 *        recursively call find_optimal_cost(point.idx). For all other sibling children 
 *        'other', we must fully ascend them using total_ascension_cost(other.idx).
 *
 *    Evaluating the minimum over all these choices guarantees we find the true global optimum.
 *
 * 2. Active Subtree Filtering (Pruning via MAX):
 *    Branches containing 0 friends must be ignored. If a subtree contains no friends, 
 *    both functions return 'MAX' (infinity). We safely propagate this up and ignore 
 *    any 'MAX' returns, preventing empty subtrees from corrupting the edge cost sum.
 *
 * 3. Memoization:
 *    Since total_ascension_cost is called multiple times for sibling calculations, 
 *    caching its result in a 1D 'cache' array reduces its retrieval time to O(1).
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>




using vb = std::vector<bool>;

const int MAX = (int)1e9;

const int MAX_V = 100000;

struct Point
{
    int idx;
    int dist;
};

using v_point = std::vector<Point>;
using vv_point = std::vector<v_point>;


int cache[MAX_V + 1];

// Calculates the total cost to visit all friends in the subtree of 'idx' 
// and climb all the way back up to 'idx' (no free descent path).
int total_ascension_cost(int idx, const vv_point& mountain, const vb& landmarks) {
  // Leaf base case
  if (mountain[idx].empty()) {
    return (cache[idx] = landmarks[idx] ? 0 : MAX);
  }

  if(~cache[idx]) {
    return cache[idx];
  }

  int cost = 0;
  bool has_friend = landmarks[idx]; // True if current node is a landmark

  for(const auto& point : mountain[idx]) {
    int point_cost = total_ascension_cost(point.idx, mountain, landmarks);
    if (point_cost != MAX) {
      has_friend = true; // A friend exists somewhere in this sub-branch
      cost += point_cost + point.dist;
    }
  }

  // If no friends were found in this entire subtree, return MAX
  if (!has_friend) {
    return (cache[idx] = MAX);
  }

  return (cache[idx] = cost);
}

// Calculates the optimal cost to visit all friends in the subtree of 'idx'
// assuming the final descent path (no climb back) ends somewhere in this subtree.
int find_optimal_cost(int idx, const vv_point& mountain, const vb& landmarks) {
  // Leaf base case
  if (mountain[idx].empty()) {
    return landmarks[idx] ? 0 : MAX;
  }

  auto adj = mountain[idx];
  int best_cost = MAX;

  // 1. If the current node itself is a friend, we can choose to end our journey here.
  // The cost of doing so is climbing up all of its active child branches.
  if(landmarks[idx]) {
    int cost_if_end_here = 0;
    for (const auto& other : adj) {
      int other_cost = total_ascension_cost(other.idx, mountain, landmarks);
      if (other_cost != MAX) {
        cost_if_end_here += other.dist + other_cost;
      }
    }
    best_cost = cost_if_end_here; // Initialize best_cost with this valid option
  }


  // 2. Alternatively, try ending the journey in one of the child subtrees
  for (const auto& point : adj) {
    int cost = find_optimal_cost(point.idx, mountain, landmarks);
        
    // If the chosen 'point' subtree contains no friends, 
    // we cannot use it as our final descension path.
    if (cost == MAX) {
      continue;
    }

    for (const auto& other : adj) {
      if (point.idx != other.idx) {
        int other_cost = total_ascension_cost(other.idx, mountain, landmarks);
        if (other_cost != MAX) {
          cost += other.dist + other_cost;
        }
      }
    }
    best_cost = std::min(best_cost, cost);
  }

  return best_cost;
}


namespace algorithms::onlinejudge::dp::intrepid_climber
{
    void submit(std::optional<char*> file, bool debug_mode)
    {
        if (file.has_value())
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
            throw std::ios_base::failure(errorMessage);
          }

        int V, S;
        while(std::cin >> V >> S) {
          int from, to, dist;
          vv_point mountain(V);
          for(int p = 0; p < V - 1; ++p) {
            std::cin >> from >> to >> dist;
            --from; --to;
            mountain[from].push_back({to, dist});
          }

          int p;
          vb landmarks(V, false);
          for(int l = 0; l < S; ++l) {
            std::cin >> p;
            landmarks[--p] = true;
          }

          std::memset(cache, -1, sizeof cache);
          std::cout << find_optimal_cost(0, mountain, landmarks) << std::endl;
        }
    }
}