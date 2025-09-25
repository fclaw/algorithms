/*
───────────────────────────────────────────────────────────────
🧳 UVa 10090 Marbles, use solution for Linear Diophantine Equation, rt: s
───────────────────────────────────────────────────────────────
 * --- The Journey from TLE to an O(1) Solution ---
 *
 * 1. The Initial Problem:
 * The initial, correct solution involved finding the valid range of the parameter 'k'
 * (here aliased as 's'), which we calculated as [low, up]. We then iterated through
 * this entire range to find the optimal solution. This resulted in a Time Limit
 * Exceeded (TLE) because the range (up - low) can be enormous.
 *
 * 2. The Breakthrough Insight:
 * The "cost" for this problem is always constant (the total marbles). The real
 * goal is to minimize the total number of items: (n1 + n2). When we express
 * (n1_k + n2_k) as a function of our parameter 'k', it turns out to be a
 * simple LINEAR FUNCTION (a straight line).
 *
 * 3. The Mathematical Consequence:
 * The minimum value of a linear function over a closed interval [low, up] MUST
 * occur at one of its endpoints: either at k = low or at k = up. There is no
 * possibility of the minimum being somewhere in the middle.
 *
 * 4. This Workaround:
 * This code implements a pragmatic O(1) fix based on that insight. Instead of
 * looping through millions of values, we only check a small, constant set of
 * points at the boundaries: {low, low + 1, up - 1, up}. This is guaranteed
 * to include the true endpoints (low, up) where the optimal solution must lie.
 * This was a successful "hack" to pass the time limit before the formal proof
 * was derived. It works because the answer is always in this tiny list.
*/

#include "../debug.h"
#include "../../aux.h"
#include "utility/arithmetics.cpp"
#include <bits/stdc++.h>



namespace arith = algorithms::onlinejudge::maths::utility::arithmetics;


using ll = long long;


namespace algorithms::onlinejudge::maths::marbles
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

       ll marbles, box1_cost, box2_cost, box1_cap, box2_cap;
       while(scanf("%lld", &marbles) == 1 && marbles) {
         scanf("%lld %lld", &box1_cost, &box1_cap);
         scanf("%lld %lld", &box2_cost, &box2_cap);
         arith::Diophantine<> sol = arith::diophantine_equation<>(box1_cap, box2_cap, marbles);
         if(!sol.exists) {
          printf("failed\n");
          continue;
         }

         ll low = std::ceil((-sol.x * sol.gcd) / box2_cap);
         ll up = std::floor((sol.y * sol.gcd) / box1_cap);

          // If the valid range for k is empty, no solution with non-negative counts exists.
         if(low > up) {
             printf("failed\n");
             continue;
         }

         // a naive loop from 'low' to 'up' would cause a Time Limit Exceeded (TLE).
         // The function we are minimizing, (n1+n2), is linear with respect to the
         // loop parameter 's'. The minimum of a linear function over an interval
         // must occur at one of the endpoints. This vector is an O(1) workaround
         // to check only the boundaries, which is guaranteed to contain the optimal solution.
         // O(1) TLE Fix: The function to optimize is linear, so the minimum is at an endpoint.
         // We only need to check the boundaries of the [low, up] range.
         std::vector<ll> range = {low, low + 1, up -1, up};

         ll box1_cnt = 0, box2_cnt = 0, min_cost = INT64_MAX;
         for(ll s : range) {
           ll curr_box1_cnt = sol.x + (s * box2_cap) / sol.gcd;
           ll curr_box2_cnt = sol.y - (s * box1_cap) / sol.gcd;
           if(curr_box1_cnt < 0 || 
              curr_box2_cnt < 0) 
             continue;
           ll curr_min = box1_cost * curr_box1_cnt + box2_cost * curr_box2_cnt;
           if(min_cost > curr_min) {
              min_cost = curr_min;
              box1_cnt = curr_box1_cnt;
              box2_cnt = curr_box2_cnt;
           } else if(min_cost == curr_min) {
             // The cost is the same, so we minimize the total number of items
             if(curr_box1_cnt + curr_box2_cnt <=
                box1_cnt + box2_cnt) {
                // This new solution has fewer items, so it's better.
                box1_cnt = curr_box1_cnt;
                box2_cnt = curr_box2_cnt;
             }
           }
         }
         if(box1_cnt == 0 && box2_cnt == 0) printf("failed\n");
         else printf("%lld %lld\n", box1_cnt, box2_cnt);
       }
    }
}