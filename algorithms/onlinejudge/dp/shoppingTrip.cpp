/*
───────────────────────────────────────────────────────────────
🧳 UVa 11284 Shopping Trip, rt: s
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




struct Shop
{
    int id;
    int discount;
};

std::ostream& operator << 
  (std::ostream& out, const Shop& shop) 
  { return out << "{" << shop.id << ", " << shop.discount << "}"; }


typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<Shop> v_shop;


namespace algorithms::onlinejudge::dp::shopping_trip
{
    /** https://onlinejudge.org/external/112/11284.pdf */
    int v, e, n, tc, k;
    vvi fw_sp;
    v_shop shops;
    const int MAX = (int)1e5;
    int tcp(int prev, int visited, vvi& memo)
    {
        if(__builtin_popcount(visited) == k)
          return -fw_sp[shops[prev].id][0];

       int& best = memo[prev][visited];
       if(~best) return best;

        best = -fw_sp[shops[prev].id][0]; // go home
        for(int i = 0; i < k; ++i)
          if(!(visited & (1 << i))) {
            int go_ahead = shops[i].discount - fw_sp[shops[prev].id][shops[i].id] + tcp(i, visited | (1 << i), memo);
            best = std::max(best, go_ahead);
          }
        return  best;
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
            shops.clear();
            fw_sp.clear();
            while_read(v, e);
            fw_sp.resize(v + 1, vi(v + 1, MAX));
            loop(e, [] (int _) {
              int from, to;
              double cost;
              while_read(from, to, cost);
              fw_sp[to][from] = 
                fw_sp[from][to] = 
                  std::min(fw_sp[from][to], (int)std::round(cost * 100));

            });

            while_read(n);
            std::unordered_map<int, int> tmp;
            loop(n, [&tmp](int i) {
              int id;
              double p;
              while_read(id, p);
              tmp[id] += (int)std::round(p * 100);
            });

            for(auto p : tmp) 
              shops.push_back({p.first, p.second});
            k = (int)shops.size();

            // Floyd Warshall's
            for(int k = 0; k <= v; ++k)
              for(int i = 0; i <= v; ++i)
                for(int j = 0; j <= v; ++j)
                  if(i != j) fw_sp[i][j] = std::min(fw_sp[i][j], fw_sp[i][k] + fw_sp[k][j]);    

            int max_saving = INT32_MIN;
            for(int i = 0; i < k; ++i) {
              vvi memo(k + 1, vi(1 << (k + 1), -1));
              max_saving = std::max(max_saving, shops[i].discount - fw_sp[0][shops[i].id] + tcp(i, 0 | (1 << i), memo));
            }
            max_saving > 0 ? printf("Daniel can save $%0.2f\n", (double)max_saving / 100) : printf("Don't leave the house\n");
        }
    }
}