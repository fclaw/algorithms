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




struct Ans
{
    int diff;
    int counter;
    int sum;
};


bool operator < (const Ans& lhs, const Ans& rhs) 
{ return lhs.diff < rhs.diff || (lhs.diff == rhs.diff && lhs.counter < rhs.counter); }


bool operator != (const Ans& lhs, const Ans& rhs) 
{ return !(lhs.diff == rhs.diff && lhs.counter == rhs.counter && lhs.sum == rhs.sum); }

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<Ans> v_ans;
typedef std::vector<v_ans> vv_ans;


const int max = (int)1e5;
Ans def = {max, 0, 0};

namespace algorithms::onlinejudge::dp::exact_change
{
    /** https://onlinejudge.org/external/115/11517.pdf */
    int tc, price, n;
    vv_ans memo;
    bool is_exact = false;
    Ans coin_change(const vi& coins, int i, int sum)
    {
        if(i == n && sum < price) return def;
        if(sum >= price) {
            Ans res = def;
            res.diff = sum - price;
            return res;
        }
         
        Ans& best = memo[i][sum];
        if(best != def) return best;

        best = def;
        for(int j = i; j < n; ++j) {
          Ans local_ans = coin_change(coins, j + 1, sum + coins[j]);
          local_ans.counter += 1;
          local_ans.sum += coins[j];
          best = std::min(best, local_ans);
        }
        return best;
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
            loop(n, [&coins] (int i) {while_read(coins[i]);});

            int max_sum = std::accumulate(coins.begin(), coins.end(), 0);
            memo.clear();
            memo = vv_ans(n + 1, v_ans(max_sum + 1, def));
            Ans ans = coin_change(coins, 0, 0);
            std::cout << ans.sum << " " << ans.counter << std::endl;
        }  
    }
}