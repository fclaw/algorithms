/*
───────────────────────────────────────────────────────────────
🧳 UVa 10721 BarCodes, rt: s
───────────────────────────────────────────────────────────────
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



typedef long long ll;
typedef std::vector<ll> vl;
typedef std::vector<vl> vvl;


namespace algorithms::onlinejudge::dp::bar_codes
{
    /** https://onlinejudge.org/external/107/10721.pdf */
    int n, k, m;
    ll memo[51][51];
    ll count_bars(int units, int bars)
    {          
        if(units == n && 
           bars == k) 
          return 1; 

        ll& cnt = memo[units][bars];
        if(~cnt) return cnt;

        cnt = 0;
        for(int u = 1; u <= std::min(n - units, m); ++u)
          cnt += count_bars(units + u, bars + 1);
        return cnt;
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
        
        while(while_read(n, k, m)) {
          std::memset(memo, -1, sizeof memo);
          printf("%llu\n", count_bars(0, 0));
        }
    }
}