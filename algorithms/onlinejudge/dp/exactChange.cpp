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


namespace algorithms::onlinejudge::dp::exact_change
{
    /** https://onlinejudge.org/external/115/11517.pdf */
    int tc, price, n;
    const int max = (int)1e5;
    Ans def = {max, 0, 0};
    vv_ans memo;
    Ans coin_change(const vi& coins, int i, int sum)
    {
        if(i == n && sum > 0) return def;
        if(sum <= 0) return {price - sum, 0, 0};
         
        Ans& best = memo[i][sum];
        if(best != def) return best;

        best = def;
        for(int j = i; j < n; ++j) {
          Ans local_ans = coin_change(coins, j + 1, sum - coins[j]);
          local_ans.counter += 1;
          local_ans.sum += coins[j];
          if(local_ans < best) best = local_ans;
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
            loop(n, [&coins] (int i) {
              while_read(coins[i]);
            });

            std::sort(coins.begin(), coins.end(), std::greater<int>());
            memo.clear();
            memo = vv_ans(n + 1, v_ans(price + 1, def));
            Ans ans = coin_change(coins, 0, price);
            std::cout << ans.sum << " " << ans.counter << std::endl;
        }  
    }
}