/*
───────────────────────────────────────────────────────────────
🧳 UVa 702 TheVindictive Coach, https://onlinejudge.org/external/7/702.pdf, rt: s
───────────────────────────────────────────────────────────────
*/

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


#define LSOne(S) ((S) & (-S))

enum Dir { UP, DOWN };


ll cache[23][23][23][2];


std::pair<int, int> get_l_h_numbers(int mask, int x) {
  // 1. Create a mask for bits lower than x (bits 0 to x-1)
  // If x is 4, (1 << 4) - 1 creates binary 0000...1111
  int lower_mask = (1 << x) - 1;
    
  // 2. Create a mask for bits higher than x (bits x+1 to 31)
  // We shift left by (x + 1) to clear out everything up to and including x
  int higher_mask = ~((1 << (x + 1)) - 1);
    

  // 3. Isolate the regions using bitwise AND and count the 1s
  int lower_count = __builtin_popcount(mask & lower_mask);
  int higher_count = __builtin_popcount(mask & higher_mask);

  return {lower_count, higher_count};
}

ll dfs(int mask, int last, Dir dir, bool is_1) {

  if(mask == 0) {
    return 1LL;
  }

   std::pair<int, int> nums = get_l_h_numbers(mask, last);

  if(~cache[nums.first][nums.second][last][dir]) {
    return cache[nums.first][nums.second][last][dir];
  }

  ll ways = 0LL;
  if(dir == DOWN) {
    int tmp = mask;
    while(tmp) {
       int t = LSOne(tmp); // the first bit that is on
       int n = __builtin_ctz(t) + 1;
       if(n < last) {
         ways += dfs(mask & ~t, n, UP, is_1);
       }
       tmp -= t;
    }
  }

  if(dir == UP) {
    int tmp = mask;
    while(tmp) {
       int t = LSOne(tmp); // the first bit that is on
       int n = __builtin_ctz(t) + 1;
       if(is_1 &&  // special case for 1 -> 3
          last == 1 &&
          n - last != 2) {
        tmp -= t;
        continue;
       }
       if(n > last) {
         ways += dfs(mask & ~t, n, DOWN, is_1);
       }
       tmp -= t;
    }
  }

  return (cache[nums.first][nums.second][last][dir] = ways);

}


namespace algorithms::onlinejudge::advanced_topics::vindictive_coach
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

        int n, m;
        while(stdin_read(n, m)) {
          if(n <= 2) {
            std::cout << "1\n";
          } else {
            int mask = 0;
            for(int i = 0; i < n; ++i) {
              if(i == m - 1) continue;
              mask |= (1 << i);
            }
            std::memset(cache, -1, sizeof cache);
            std::cout << dfs(mask, m, m == 1 ? UP : DOWN, m == 1) << "\n";
          }
        }
    }
}