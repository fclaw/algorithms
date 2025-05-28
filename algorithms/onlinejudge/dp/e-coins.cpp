/*
───────────────────────────────────────────────────────────────
🧳 UVa 10306 E-coins, rt: s
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
#include <cmath>




struct ECoin
{
    int real;
    int digit;
};


std::ostream& operator << 
  (std::ostream& out, const ECoin& ecoin) 
  { return out << "{" << ecoin.real << ", " << ecoin.digit << "}"; }

ECoin operator + (const ECoin& lhs, const ECoin& rhs) 
{ return { lhs.real + rhs.real, lhs.digit + rhs.digit }; }


typedef std::vector<ECoin> v_ecoin;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


namespace algorithms::onlinejudge::dp::e_coins
{
    /** https://onlinejudge.org/external/103/10306.pdf */
    int to_emod(const ECoin& ecoin) { return ecoin.real * ecoin.real + ecoin.digit * ecoin.digit; }
    const int limit = (int)1e5;
    int coin_change(const v_ecoin& coins, ECoin coin, int emod, vvi& memo)
    {
        // base cases
        if(to_emod(coin) == emod * emod) return 0;
        int& amount = memo[coin.real][coin.digit];
        if(~amount) return amount;
        amount = limit;
        for(auto& c : coins)
          if(to_emod(coin + c) <= emod * emod)
            amount = std::min(amount, 1 + coin_change(coins, coin + c, emod, memo));
        return amount;
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
        int tc;
        while_read(tc);
        while(tc--)
        {
            int n, emod;
            while_read(n, emod);
            v_ecoin coins(n);
            loop(n, [&coins] (int i) {
                int r, d;
                while_read(r, d);
                coins[i] = {r, d};
            });

            vvi memo(1000, vi(1000, -1));
            int amount = coin_change(coins, {0, 0}, emod, memo);
            std::cout << (amount != limit ? std::to_string(amount) : "not possible") << std::endl;
        }  
    }
}