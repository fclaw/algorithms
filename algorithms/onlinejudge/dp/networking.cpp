/*
───────────────────────────────────────────────────────────────
🧳 UVa 216 Getting in Line, rt: s
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




struct Comp
{
    int x;
    int y;
};


double euclidean_distance(const Comp& a, const Comp& b) 
{
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

typedef std::vector<Comp> v_comp;

struct Cable
{
    double cable;
    v_comp path;
};

typedef std::vector<Cable> v_cable;
typedef std::vector<v_cable> vv_cable;

const double MAX = 1e5;
const double extra = 16;

Cable def = {0, {}};

bool operator < (const Cable& lhs, const Cable& rhs) 
{ return lhs.cable < rhs.cable || (lhs.cable == rhs.cable && lhs.path.size() < rhs.path.size()); }


bool operator != (const Cable& lhs, const Cable& rhs) 
{ return !(lhs.cable == rhs.cable && lhs.path.size() == rhs.path.size()); }


namespace algorithms::onlinejudge::dp::networking
{
    /** https://onlinejudge.org/external/2/216.pdf */
    int n, c = 1;
    std::string comp_to_str(const Comp& c) { return "(" + std::to_string(c.x) + "," + std::to_string(c.y) + ")"; }
    Cable tcp(const v_comp& comps, int prev, int used, vv_cable& memo) 
    {
        if(__builtin_popcount(used) == n)
          return {0, {}};

        Cable& best = memo[prev][used];
        if(best != def) return best;

        best = {MAX, {}};  
        for(int i = 0; i < n; ++i)
          if(!(used & (1 << i))) {
            Cable local = tcp(comps, i, used | (1 << i), memo);
            double dist = euclidean_distance(comps[prev], comps[i]);
            local.cable += (dist + extra);
            local.path.push_back(comps[i]);
            best = std::min(best, local);
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
        
        while(while_read(n) && n)
        {
            v_comp comps(n);
            loop(n, [&comps](int i){
              int x, y;
              while_read(x, y);
              comps[i] = {x, y};
            });

            Cable ans = {MAX, {}};
            for(int i = 0; i < n; ++i) {
                vv_cable memo(n + 1, v_cable(1 << n, def));
                Cable res = tcp(comps, i, 0 | (1 << i), memo);
                std::reverse(res.path.begin(), res.path.end());
                res.path.emplace(res.path.begin(), comps[i]);
                ans = std::min(ans, res);
            }
            printf("**********************************************************\n");
            printf("Network #%d\n", c++);
            for(int i = 1; i < (int)ans.path.size(); ++i) {  
              Comp from = ans.path[i - 1];
              Comp to = ans.path[i];
              double d = euclidean_distance(from, to);
              printf("Cable requirement to connect %s to %s is %0.2f feet.\n", comp_to_str(from).c_str(), comp_to_str(to).c_str(), d + extra); 
            }
            printf("Number of feet of cable required is %6.2f.\n", ans.cable);

        }
    }
}