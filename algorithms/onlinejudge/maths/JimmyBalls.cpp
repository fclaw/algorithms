/*
───────────────────────────────────────────────────────────────
🧳 UVa 11480 Jimmy’s Balls, https://onlinejudge.org/external/114/11480.pdf, try all r, but simpler formula exists, rt: s
   https://oeis.org/A001399, a(n) is the number of partitions of n into at most 3 parts; also partitions of n+3 in which the greatest part is 3; 
   also number of unlabeled multigraphs with 3 nodes and n edges.
   a(n) = 1 + a(n-2) + a(n-3) - a(n-5) for all n in Z
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



constexpr int MAX_BALLS = 1000010;


using ull = unsigned long long;
using arr = std::array<int, 3>;
using vll = std::vector<ull>;


bool check_bag(const arr& bag, int limit) {
  bool is_valid = true;
  int sum = bag[0];
  for(int i = 1; i < (int)bag.size(); i++) {
    sum += bag[i];
    is_valid &= (bag[i] > bag[i - 1]);
  }
  return is_valid && (sum == limit);
}

ull backtrack(int curr_colour, int start_balls, int limit, arr& bag) {
  if(curr_colour == 3) {
     if(check_bag(bag, limit)) {
       return 1;
     } else return 0;
  }

  ull ways = 0;
  for(int ball = start_balls; ball <= limit; ball++) {
    int prev_balls = bag[curr_colour];
    bag[curr_colour] = ball;
    ways += backtrack(curr_colour + 1, ball, limit, bag);
    bag[curr_colour] = prev_balls;
  }

  return ways;
}



namespace algorithms::onlinejudge::maths::Jimmy_balls
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


        vll dp(MAX_BALLS + 1);
        for(int balls = 6; balls <= 10; ++balls) {
          arr bag = {0, 0, 0};
          dp[balls] = backtrack(0, 1, balls, bag);
        }

        for(int balls = 11; balls <= MAX_BALLS; ++balls) {
            dp[balls] = 1 + dp[balls - 2] + dp[balls - 3] - dp[balls - 5];
        }


        int balls, t_case = 1;
        while (scanf("%d", &balls) == 1 && balls) {
        //   arr bag = {0, 0, 0};
        //   ull ways = backtrack(0, 1, balls, bag);
          printf("Case %d: %llu\n", t_case++, dp[balls]);
        }
    }
}