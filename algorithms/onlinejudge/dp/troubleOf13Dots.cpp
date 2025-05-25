/*
───────────────────────────────────────────────────────────────
🧳 UVa 10819 Trouble of 13-Dots, rt: 0.530s
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




struct Item
{
    int price;
    int favour_index;
};


std::ostream& operator << 
  (std::ostream& out, const Item& item) 
  { return out << "{" << item.price << ", "  << item.favour_index << "}"; }

bool operator < (const Item& li, const Item& ri) { return li.price < ri.price; }


typedef std::vector<Item> v_item;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;



namespace algorithms::onlinejudge::dp::troubleOf13Dots
{
    /** https://onlinejudge.org/external/108/10819.pdf */
    const int THRESHOLD = 2000;
    const int extra = 200;
    int budget, n; 
    int knapsack(const v_item& items, int i, int spend, vvi& memo)
    {
        if(i == n) return 0;

        if(~memo[i][spend]) return memo[i][spend];

        int best = knapsack(items, i + 1, spend, memo);
        
        if((spend + items[i].price <= budget) ||
            (spend + items[i].price > THRESHOLD && 
             spend + items[i].price <= budget + extra))
          best = std::max(best, items[i].favour_index + knapsack(items, i + 1, spend + items[i].price, memo));  
        return memo[i][spend] = best;
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
        
        while(while_read(budget, n))
        {
            int p, f;
            v_item items(n); 
            loop(n, [&items, &p, &f](int i){
               while_read(p, f);
               items[i] = {p, f};
            });

            std::sort(items.begin(), items.end());

            int max_spend = std::max(budget, THRESHOLD) + extra;
            vvi memo(n + 1, vi(max_spend + 1, -1));
            std::cout << knapsack(items, 0, 0, memo) << std::endl;
        }
    }
}