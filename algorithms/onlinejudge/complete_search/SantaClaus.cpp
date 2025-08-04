

 /*
 ─────────────────────────────────────────────────────────────── 
 🧳 UVa 291 The House Of Santa Claus, Euler tour on a small graph; backtracking is sufficient, rt: s
 ───────────────────────────────────────────────────────────────
 */

#include "../debug.h"
#include "../../aux.h"
#include <bits/stdc++.h>


using vi = std::vector<int>;
using vvi = std::vector<vi>;

vvi house = {{1, 2, 4}, {0, 2, 4}, {0, 1, 3, 4}, {2, 4}, {0, 1, 2, 3}};

// Define how many bits we need per integer
constexpr int MAX_SHIFT = 3;
constexpr int EDGES = 8;

struct Edge
{
    int u;
    int v;
    Edge(int a, int b) : u(std::min(a, b)), v(std::max(a, b)) {}
};

// --- Packing Function ---
int pack_edge(const Edge& edge) {
  // Pack them: (v shifted left by 3 bits) OR (u)
  return (edge.v << MAX_SHIFT) | edge.u;
}


void backtrack(int i, vi curr_path, vvi& paths, int visited)
{
    if(__builtin_popcount(visited) == EDGES) {
        paths.push_back(curr_path);
        return;
    }

    for(int neigh : house[i]) {
      Edge edge(i, neigh);
      int packed = pack_edge(edge);
      if(!(visited & (1 << packed))) {
        curr_path.push_back(neigh + 1);
        backtrack(neigh, curr_path, paths, visited | (1 << packed));
        curr_path.pop_back();
      }
    }
}

namespace algorithms::onlinejudge::complete_search::santa_claus
{
    void submit(std::optional<char*> file, bool debug_mode)
    {
        /** https://onlinejudge.org/external/2/291.pdf */
        if (file.has_value()) {
          // Attempt to reopen stdin with the provided file
          if (std::freopen(file.value(), "r", stdin) == nullptr) {
            // If freopen fails, throw an exception with a more detailed error message
            std::string name = file.value();
            std::string errorMessage = 
              "Failed to open file: " + name +
              " with error: " + std::strerror(errno);
              throw std::ios_base::failure(errorMessage);
          }
        }

        vvi paths;
        backtrack(0, {1}, paths, 0);
        for(const auto& path : paths) {
          std::string path_str;
          for(int p : path) {
            path_str += std::to_string(p);
          }
          std::cout << path_str << std::endl;
        }
    }
}