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
#include <limits>
#include <cmath>





typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;


namespace algorithms::onlinejudge::dp::groupSums
{
    /** https://onlinejudge.org/external/106/10616.pdf  */
    int n, q, tc = 1;
    ll knapsack(const vi& nums, int i, int rem, int mod, int d, vvvi& memo)
    {
        if(rem == 0)
          return mod == 0 ? 1 : 0; // Only valid if the accumulated sum is divisible by d
        if (i == n)
          return 0;        // No more items to choose from

        if(~memo[i][rem][mod]) return memo[i][rem][mod];
           
         ll skip = knapsack(nums, i + 1, rem, mod, d, memo);
         int new_mod = (mod + nums[i]) % d;
         if(new_mod < 0) new_mod += d;
         ll add = knapsack(nums, i + 1, rem - 1, new_mod, d, memo);
         return memo[i][rem][mod] = skip + add;
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

        while(while_read(n, q) && n && q)
        {
             vi nums(n);
             loop(n, [&nums](int i){ while_read(nums[i]);});
             printf("SET %d:\n", tc++);
             int qi = 1;
             while(q--)
             {
                 int d, m;
                 while_read(d, m);
                 vvvi memo(n + 1, vvi(m + 10, vi(d + 10, -1)));
                 printf("QUERY %d: %llu\n", qi++, knapsack(nums, 0, m, 0, d, memo));
             }
        }
    }
}