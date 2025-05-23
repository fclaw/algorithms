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
    int weight;
};


std::ostream& operator << 
(std::ostream& out, const Item& item) 
{ return out << "{" << item.price << ", "  << item.weight << "}"; }

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<Item> v_item;


namespace algorithms::onlinejudge::dp::super_sale
{
    /** https://onlinejudge.org/external/101/10130.pdf */
    int n, m;
    int knapsack(const v_item& items, int max_w)
    {
        // f(i, w) = max(f(i + 1, w), items(i).price + f(i + 1, w - items(i).weight))
        vvi dp(n + 1, vi(max_w + 1));
        for(int i = n - 1; i >= 0; --i)
          for(int w = 0; w <= max_w; ++w) {
            dp[i][w] = dp[i + 1][w]; // skip
            if(items[i].weight <= w)
              dp[i][w] = std::max(dp[i][w], items[i].price + dp[i + 1][w - items[i].weight]); // add
          } 
        return dp[0][max_w];
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
        std::cin >> tc;
        while(tc--)
        {
            std::cin >> n;
            v_item items(n);
            loop(n, [&items] (int i) {
              int p, w;
              while_read(p, w);
              items[i] = {p, w};
            });
            std::cin >> m;
            vi people(m);
            loop(m, [&people] (int i) { std::cin >> people[i]; });

            int total = 0;
            for(int w : people)
              total += knapsack(items, w);
            std::cout << total << std::endl;
        }
    }
}