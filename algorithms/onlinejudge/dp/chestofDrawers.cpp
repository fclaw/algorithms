/*
───────────────────────────────────────────────────────────────
🧳 UVa 11420, Chest of Drawers, rt: s
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
typedef std::vector<vvl> vvvl;


namespace algorithms::onlinejudge::dp::chest
{
    /** https://onlinejudge.org/external/114/11420.pdf */
    int n, k;
    enum Drawer { Lock, Unlock };
    ll memo[66][2][66];
    ll count_ways(int c_n, Drawer prev_s, int n_l)
    {
        if(!c_n) return n_l == k ? 1 : 0;

        if(~memo[c_n][prev_s][n_l]) 
          return memo[c_n][prev_s][n_l]; 

        int new_n_l = prev_s == Lock ? n_l + 1 : n_l;
        ll lock = count_ways(c_n - 1, Lock, new_n_l);
        ll unlock = count_ways(c_n - 1, Unlock, n_l);
        return memo[c_n][prev_s][n_l] = lock + unlock;
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
        
        while(while_read(n, k) && n > 0 && k >= 0) {
          std::memset(memo, -1, sizeof memo);
          printf("%llu\n", count_ways(n, Lock, 0));
        }
    }
}