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





typedef std::vector<int> vi;
typedef std::vector<vi> vvi;


namespace algorithms::onlinejudge::dp::shopping_trip
{
    /** https://onlinejudge.org/external/112/11284.pdf */
    int v, e, n, tc;
    vvi fw_sp;
    vi disks;
    const int MAX = (int)1e5;
    // int memo[1 << ]
    int tcp(int prev, int visited, int expense, vvi& memo)
    {
        if(expense < 0) return INT32_MIN;
        if(__builtin_popcountll(visited) == v + 1) {
          int cost = expense - fw_sp[prev][0];
          if(cost < 0) cost = INT32_MIN;
          return cost;
        }

        int& best = memo[prev][visited];
        if(~best) return best;

        best = INT32_MIN;
        int go_home = expense - fw_sp[prev][0]; // go home
        if(go_home > 0) best = std::max(best, go_home);
        for(int i = 1; i <= v; ++i)
          if(!(visited & (1 << i))) {
            int new_exp = expense - fw_sp[prev][i] + disks[i];
            int go_ahead = tcp(i, visited | (1 << i), new_exp, memo);
            best = std::max(best, go_ahead);
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
            disks.clear();
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
            disks.resize(v + 1);
            loop(n, [](int _) {
              int i;
              double p;
              while_read(i, p);
              disks[i] += (int)std::round(p * 100);
            });

            // Floyd Warshall’s
            for(int k = 0; k <= v; ++k)
              for(int i = 0; i <= v; ++i)
                for(int j = 0; j <= v; ++j)
                  if(i != j) fw_sp[i][j] = std::min(fw_sp[i][j], fw_sp[i][k] + fw_sp[k][j]);    
    
            int max_saving = INT32_MIN;
            for(int i = 1; i <= v; ++i) {
              vvi memo(v + 1, vi(1 << (n + 1), -1));
              max_saving = std::max(max_saving, tcp(i, 0 | (1 << i), disks[i] - fw_sp[0][i], memo));
            }
            max_saving != INT32_MIN ? printf("Daniel can save $%0.2f\n", (double)max_saving / 100) : printf("Don't leave the house\n");
        }
    }
}