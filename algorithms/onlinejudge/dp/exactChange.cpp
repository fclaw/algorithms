/*
───────────────────────────────────────────────────────────────
🧳 UVa 11517 exact change, rt: s
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







typedef std::vector<int> vi;
typedef std::pair<int, vi> pivi;
typedef std::vector<pivi> vp;
typedef std::vector<vp> vvp;

bool better(const pivi& a, const pivi& b) 
{
    if(a.first != b.first)
      return a.first < b.first;
    return a.second.size() < b.second.size();
}

namespace algorithms::onlinejudge::dp::exact_change
{
    /** https://onlinejudge.org/external/115/11517.pdf */
    int tc, price, n;
    const int max = (int)1e5;
    pivi def = {max, {}};
    pivi memo[101][10001];
    pivi coin_change(const vi& coins, int i, int sum) 
    {
        if(i == n && sum > 0) return def;
        if(sum <= 0) return {price - sum, {}};
         
        pivi& best = memo[i][sum];
        if(best != def) return best;

        pivi skip = coin_change(coins, i + 1, sum);
        pivi add = coin_change(coins, i + 1, sum - coins[i]);
        add.second.push_back(i);
        return best = better(skip, add) ? skip : add;
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
        
        while_read(tc);
        while(tc--)
        {
            while_read(price);
            while_read(n);
            vi coins(n);
            loop(n, [&coins] (int i) {
              while_read(coins[i]);
            });

            for(int i = 0; i <= 100; ++i)
              for(int j = 0; j <= 10000; ++j)
                memo[i][j] = def; // or any other sentinel values
            vi xs = coin_change(coins, 0, price).second;
            int sum = 0;
            for(int x : xs) sum += coins[x];
            std::cout << sum << " " << xs.size() << std::endl;
        }  
    }
}