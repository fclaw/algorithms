/*
───────────────────────────────────────────────────────────────
🧳 UVa 147 Dollars, rt: s
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





struct Currency
{
    int notes;
    // maximumload load that a box can carry
    int coins;
};


std::ostream& operator <<
  (std::ostream& out, const Currency& currency) 
  { return out << "{" << currency.notes << "." << currency.coins << "}"; }


Currency operator - (const Currency& lc, const Currency& rc) 
{ 
    Currency new_curr;
    if(lc.coins >= rc.coins)
      new_curr = { lc.notes - rc.notes, lc.coins - rc.coins };
    else new_curr = { lc.notes - rc.notes - 1, 100 - (rc.coins - lc.coins) };
    return new_curr;
}
bool operator < (const Currency& lc, const Currency& rc) 
{ return lc.notes < rc.notes || (lc.notes == rc.notes && lc.coins < rc.coins); }
bool operator >= (const Currency& lhs, const Currency& rhs) { return !(lhs < rhs); }
bool operator == (const Currency& lc, const Currency& rc) 
{ return lc.notes == rc.notes && lc.coins == rc.coins; }


typedef long long ll;
typedef std::vector<ll> vi;
typedef std::vector<vi> vvi;
typedef std::vector<vvi> vvvi;
typedef std::vector<Currency> v_curr;


v_curr currencies = {{100, 0}, {50, 0}, {20, 0}, {10, 0}, {5, 0}, {2, 0}, {1, 0}, {0, 50}, {0, 20}, {0, 10}, {0, 5}};


namespace algorithms::onlinejudge::dp::dollars
{
    /** https://onlinejudge.org/external/1/147.pdf */
    Currency target;
    const Currency def = {0, 0};
    const int S = 11;
    const int MAX_NOTES = 300;
    const int MAX_COINS = 99; // if coins range from 0 to 99
    ll memo[S + 1][MAX_NOTES + 1][MAX_COINS + 1];
    double to_double(const Currency& c) { return c.notes + c.coins / 100.0; }
    ll coin_change(Currency c, int prev)
    {
        if(c == def) return 1;
        ll& ways = memo[prev][c.notes][c.coins];
        if(~ways) return ways;
        ways = 0;
        for(int i = prev; i < S; ++i)
          if(c >= currencies[i])
            ways += coin_change(c - currencies[i], i);
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
        
        std::string in;
        while(while_read(in))
        {
            size_t dot = in.find('.');
            int notes = std::atoi(in.substr(0, dot).c_str());
            int coins = std::atoi(in.substr(dot + 1, in.size()).c_str());
            if(!notes && !coins) break;
            memset(memo, -1, sizeof memo);
            printf("%6.2f%17llu\n", to_double({notes, coins}), coin_change({notes, coins}, 0));
        }  
    }
}