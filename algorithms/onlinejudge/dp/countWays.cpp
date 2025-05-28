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




typedef long long ll;
typedef std::vector<ll> vi;

vi coins = {1, 5, 10, 25, 50};


namespace algorithms::onlinejudge::dp::count_ways
{
    /** https://onlinejudge.org/external/3/357.pdf */
    ll coin_change(int coin, int prev)
    {
        if(!coin) return 1;
        ll ways = 0;
        for(int i = prev; i < (int)coins.size(); ++i)
          if(coin >= coins[i])
            ways += coin_change(coin - coins[i], i);
        return ways;    
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
        int coin;  
        while(while_read(coin)) {
          vi dp(coin + 1, 0);
          dp[0] = 1;
          for(int i = 0; i < (int)coins.size(); ++i)
            for(int c = 0; c <= coin; ++c)
              if(c + coins[i] <= coin)
                dp[c + coins[i]] += dp[c];
          if(dp[coin] == 1) printf("There is only 1 way to produce %d cents change.\n", coin);      
          else printf("There are %llu ways to produce %d cents change.\n", dp[coin], coin);      
        }
    }
}