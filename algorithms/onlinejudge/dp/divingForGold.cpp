/*
    Recurrence relation for Diving for Gold (UVa 990):

    Let:
    - f(i, air): maximum gold collectible starting from chest i with 'air' units of time remaining.
    - g_i: gold in chest i
    - d_i: depth of chest i
    - cost_i = 3 * w * d_i: time (air) required to retrieve chest i
    - n: total number of chests

    Recurrence:
    f(i, air) = 
        0                                                  if i == n
        f(i + 1, air)                                       if cost_i > air
        max(f(i + 1, air), g_i + f(i + 1, air - cost_i))    otherwise

    Base case:
    f(n, air) = 0   for all air

    Constraints:
    0 ≤ i ≤ n
    0 ≤ air ≤ t    (t = total available air)
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





struct Chest
{
    int depth;
    int gold;
};


std::ostream& operator << 
(std::ostream& out, const Chest& chest) 
{ return out << "{" << chest.depth << ", "  << chest.gold << "}"; }

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<Chest> v_chest;
typedef std::vector<std::pair<int, vi>> vpivi;
typedef std::vector<vpivi> vvpivi;

namespace algorithms::onlinejudge::dp::diving_for_gold
{
    /** https://onlinejudge.org/external/9/990.pdf */
    int air, constant, n, tc = 1;
    std::pair<int, vi> def = {0, {}};
    std::pair<int, vi> rec(const v_chest& chests, int i, int air, vvpivi& memo)
    {
        if(i == n || !air) return def;

        if(memo[i][air] != def) return memo[i][air];

        std::pair<int, vi> skip = rec(chests, i + 1, air, memo);
        std::pair<int, vi> add = def;
        if(air >= 3 * constant * chests[i].depth) { 
          add = rec(chests, i + 1, air - 3 * constant * chests[i].depth, memo);
          add.first += chests[i].gold;
          add.second.push_back(i);
        }
        return memo[i][air] = skip.first >= add.first ? skip : add;
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

        while(while_read(air, constant))
        {
            if(tc++ > 1) std::cout << std::endl;

            std::cin >> n;
            v_chest chests(n);
            loop(n, [&chests](int i) {
              int d, g;
              while_read(d, g);
              chests[i] = {d, g};
            });

            vvpivi memo = vvpivi(n + 1, vpivi(air + 1, def));
            std::pair<int, vi> gold = rec(chests, 0, air, memo);
            std::cout << gold.first << std::endl;
            std::cout << gold.second.size() << std::endl;
            for(int i = 0; i < n; ++i)
              for(int j : gold.second) 
                if(i == j) {
                  int d = chests[i].depth;
                  int g = chests[i].gold;   
                  printf("%d %d\n", d, g);
                }
        }
    }
}