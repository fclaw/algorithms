/*
───────────────────────────────────────────────────────────────
🧳 UVa 11003 Boxes, rt: s
───────────────────────────────────────────────────────────────

Problem Summary:
You're given 'n' boxes. Each box has:
  - w(i): its weight
  - c(i): the maximum weight it can carry (stacked on top of it)

Goal:
Find the maximum number of boxes you can stack vertically such that
no box is overloaded by the weight of the boxes placed above it.

------------------------------------------------------------
State Definition:
Let f(i, rem_w) be the maximum number of boxes that can be stacked
from index 'i' onwards, where 'rem_w' is the remaining weight capacity 
of the current supporting box (i.e., the box below).

------------------------------------------------------------
Recurrence Relation:

f(i, rem_w) = max(
  f(i + 1, rem_w), // Option 1: skip the i-th box
  (rem_w >= w(i)) ? 1 + f(i + 1, min(rem_w - w(i), c(i))) : -INF
                  // Option 2: use the i-th box if possible
)

Explanation:
- If we skip the i-th box, remaining weight capacity stays the same.
- If we choose the i-th box, we:
   * reduce the capacity of the supporting box by w(i)
   * the new capacity becomes the smaller of:
     - what's left on the supporting box (rem_w - w(i))
     - the max capacity of the current box (c(i))

------------------------------------------------------------
Base Case:
If i == n: return 0
-> No boxes left to consider.

------------------------------------------------------------
Initial Call:
f(0, INF)
-> Start with the first box and unlimited weight allowance.
   A tighter upper bound can be the total weight sum of all boxes.

------------------------------------------------------------
Memoisation:
Use a 2D array:
  vector<vector<int>> memo(n + 1, vector<int>(MAX_WEIGHT + 1, -1))

------------------------------------------------------------
Alternative (Bottom-Up DP):
Let dp[rem_w] represent the maximum number of boxes with remaining
weight capacity rem_w.

Update in reverse:
  for each box (w, c):
    for rem_w from MAX_W down to w:
      dp[min(rem_w - w, c)] = max(dp[min(rem_w - w, c)], 1 + dp[rem_w])

------------------------------------------------------------
*/

#include "../debug.h"
#include "../../aux.h"

#include <optional>
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <cstring>
#include <bitset>
#include <unordered_map>
#include <unordered_set>





struct Box
{
    int weight;
    // maximumload load that a box can carry
    int capacity;
};


std::ostream& operator << 
  (std::ostream& out, const Box& box) 
  { return out << "{" << box.weight << ", " << box.capacity << "}"; }


typedef std::vector<Box> v_box;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


namespace algorithms::onlinejudge::dp::boxes
{
    /** https://onlinejudge.org/external/110/11003.pdf */
    const int MAX_CAP = 6000;
    int n;
    int knapsack(const v_box& boxes, int i, int rem_w, vvi& memo)
    {
        if(i == n) return 0;

        if(~memo[i][rem_w]) return memo[i][rem_w];

        int skip = knapsack(boxes, i + 1, rem_w, memo);
        int add = INT32_MIN;
        if(rem_w >= boxes[i].weight)
          add = 1 + knapsack(boxes, i + 1, std::min(rem_w - boxes[i].weight, boxes[i].capacity), memo);

        return memo[i][rem_w] = std::max(skip, add);
    }
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

        while(while_read(n) && n)
        {
            v_box boxes(n);
            loop(n, [&boxes] (int i) {
                int w, cap;
                while_read(w, cap);
                boxes[i] = {w, cap};
            });

            // f(i, rem_w) = max(f(i + 1, rem_w), (rem_w >= w(i)) ? 1 + f(i + 1, min(rem_w - w(i), c(i))) : -INF)
            vvi memo(n + 1, vi(MAX_CAP + 1, -1));
            std::cout << knapsack(boxes, 0, MAX_CAP, memo) << std::endl;
        }  
    }
}