/*
───────────────────────────────────────────────────────────────
🧳 UVa 12955 Factorial, https://onlinejudge.org/external/129/12955.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>



using vi = std::vector<int>;
using vvi = std::vector<vi>;

const int MAX = (int)1e9;
const int M = 9;
const int N = 100;
vi fac(M);

void generate_factorials() {

  // Base case
  fac[0] = 1;  
  // Calculate factorials
  for(int i = 1; i < M; i++) {
    fac[i] = i * fac[i - 1];
  }
}


int cache[M][N];


int get_min_number(int i, int target, int sum) {

   if(i == (int)M || sum > target) {
    return MAX;
   }

   if(target == sum) {
    return (cache[i][sum] = 0);
   }

   if(~cache[i][sum]) {
     return cache[i][sum];
   }

   // taka and stay
   int take_stay = 1 + get_min_number(i, target, sum + fac[i]);
   // take and move
   int take_move = 1 + get_min_number(i + 1, target, sum + fac[i]);
   // skip
   int skip = get_min_number(i + 1, target, sum);

   return (cache[i][sum] = std::min(skip, std::min(take_stay, take_move)));
}


namespace algorithms::onlinejudge::dp::factorial
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
        
        generate_factorials();

        int num;
        while(std::cin >> num) {
          // std::memset(cache, -1, sizeof cache);
          // std::cout << get_min_number(0, num, 0) << std::endl;
          vvi dp(M + 1, vi(num + 1, MAX));
        
          // Base Case: 0 sum requires 0 items
          for (int i = 0; i <= M; ++i) {
            dp[i][0] = 0;
          }

          for(int i = 1; i <= M; ++i) {
            for(int sum = 0; sum <= num; ++sum) {
              // Option 1: Take and Stay (using same row 'i' because we can reuse 'val')
              int take_stay = MAX;
              if(sum >= fac[i]) 
                take_stay = 1 + dp[i][sum - fac[i]];
              // Option 2: Take and Move (using previous row 'i-1')
              int take_move = MAX; 
              if(sum >= fac[i])
                take_move = 1 + dp[i - 1][sum - fac[i]];
              // Option 3: Skip (Inherit best from previous items)
              int skip = dp[i - 1][sum];
              dp[i][sum] = std::min(dp[i][sum], std::min(skip, std::min(take_stay, take_move)));
            }
          }

          std::cout << dp[M][num] << std::endl;
        }
    }
}