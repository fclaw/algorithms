/*
───────────────────────────────────────────────────────────────
🧳 UVa 11081 Strings, https://onlinejudge.org/external/110/11081.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;
using vvi = std::vector<vi>;


std::string first, second, source;

int MOD = 10007;

// Memo table sizes: [first.size() + 1][second.size() + 1][source.size() + 1]
// We use +1 to handle the '-1' initial state safely!
int memo[65][65][65]; 

int count_ways(int f_last_idx, int s_last_idx, int k) {

   if(k == (int)source.size()) {
     return 1;
   }

    if (~memo[f_last_idx][s_last_idx][k]) {
      return memo[f_last_idx][s_last_idx][k];
    }

   char target = source[k];
   int ways = 0;
   for(int i = f_last_idx; i < (int)first.size(); ++i) {
     if(first[i] == target) {
       ways += count_ways(i + 1, s_last_idx, k + 1);
     }
   }

   for(int j = s_last_idx; j < (int)second.size(); ++j) {
     if(second[j] == target) {
       ways += count_ways(f_last_idx, j + 1, k + 1);
     }
   }

   return memo[f_last_idx][s_last_idx][k] = ways % MOD;
}


namespace algorithms::onlinejudge::strings::interleaved_subsequences
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

        int t_cases;
        std::cin >> t_cases;
        std::cin.ignore();
        while(t_cases--) {
          std::cin >> first >> second >> source;
          std::memset(memo, -1, sizeof(memo));
          std::cout << count_ways(0, 0, 0) << std::endl;
        }
    }
}