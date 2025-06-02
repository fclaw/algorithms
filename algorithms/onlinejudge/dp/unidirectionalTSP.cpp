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
#include <sstream>


struct Dir
{
    int r_shift;
    int c_shift;
};

typedef std::pair<int, int> pii;
typedef std::vector<Dir> v_dir;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

const v_dir dirs = {{1, 1}, {0, 1}, {-1, 1}};

struct Ans
{
    int weight;
    vi path;
};


Ans def = {0, {}};

bool operator < (const Ans& lhs, const Ans& rhs) 
{
  return lhs.weight < rhs.weight || 
          (lhs.weight == rhs.weight && 
           std::lexicographical_compare(
             lhs.path.rbegin(), lhs.path.rend(),
             rhs.path.rbegin(), rhs.path.rend()));
}

bool operator == (const Ans& lhs, const Ans& rhs) 
{ return lhs.weight == rhs.weight && lhs.path == rhs.path; }

std::ostream& operator << (std::ostream& out, const Ans& ans) 
{
    std::stringstream ss;
    for(int i : ans.path) ss << i << ", ";
    std::string s = ss.str();
    s.insert(s.begin(), '{');
    s.pop_back();
    s.pop_back();
    s.push_back('}');
    return out << "{" << ans.weight << ", " << s << "}"; 
}

typedef std::vector<Ans> v_ans;
typedef std::vector<v_ans> vv_ans;


namespace algorithms::onlinejudge::dp::unidirectional_tsp
{
    /** https://onlinejudge.org/external/1/116.pdf */
    int n, m;
    const int MAX = (int)1e5;
    std::optional<pii> make_move(int r, int c, const Dir& d)
    {
        int new_r = (r + d.r_shift + n) % n; // handles wrapping
        int new_c = c + d.c_shift;
        if(new_c >= m) return std::nullopt;
        return {{new_r, new_c}};
    }
    Ans get_min_weigh(const vvi& grid, int r, int c, vv_ans& memo)
    {
        if(c == m - 1) return {grid[r][c], {r + 1}};

        if(memo[r][c] != def) return memo[r][c];

        Ans best = {MAX, {}};
        for(auto& d : dirs) {
          auto pos = make_move(r, c, d);
          if(pos.has_value()) {
            int new_r = pos.value().first;
            int new_c = pos.value().second;
            Ans ans = get_min_weigh(grid, new_r, new_c, memo);
            ans.weight += grid[r][c];
            ans.path.push_back(r + 1);
            best = std::min(best, ans);
          }
        }
        return memo[r][c] = best;
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

        while(while_read(n, m))
        {
            vvi grid(n, vi(m));
            loop(n, [&grid](int i) {
              loop(m, [&grid, i](int j) {
                while_read(grid[i][j]);
              });
            });

            Ans best = {MAX, {}};
            for(int i = 0; i < n; ++i) {
              vv_ans memo(n + 1, v_ans(m + 1, def));
              Ans ans = get_min_weigh(grid, i, 0, memo);
              best = std::min(best, ans);
            }

           std::string path;
           for(auto it = best.path.rbegin(); it != best.path.rend(); ++it) 
             path += std::to_string(*it) + " ";
           path.pop_back();
           std::cout << path << std::endl << best.weight << std::endl;  
        }
    }
}